#include "EventLoop.h"
#include "Channel.h"
#include "Epoll.h"
#include <bits/types/struct_itimerspec.h>
#include <bits/types/struct_timeval.h>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <functional>
#include <mutex>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <sys/timerfd.h>
#include <unistd.h>
#include <vector>

int createtimerfd(int sec = 30)
{
    int tfd = timerfd_create(CLOCK_MONOTONIC, TFD_CLOEXEC|TFD_NONBLOCK); //����timerfd
    struct itimerspec timeout; //����ʱ������ݽṹ
    memset(&timeout, 0, sizeof(struct itimerspec));
    timeout.it_value.tv_sec = sec; //��ʱʱ�� �̶�Ϊ5
    timeout.it_value.tv_nsec = 0;
    timerfd_settime(tfd, 0, &timeout, 0);
    return tfd;
}

//�ڹ��캯���д���Epoll����ep_
EventLoop::EventLoop(bool mainloop,int timetvl,int timeout):ep_(new Epoll),mainloop_(mainloop),
           timetvl_(timetvl),timeout_(timeout),stop_(false),wakeupfd_(eventfd(0, EFD_NONBLOCK)),
           wakechannel_(new Channel(this,wakeupfd_)),timerfd_(createtimerfd(timeout_)),
           timerchannel_(new Channel(this,timerfd_))
{
    wakechannel_->setreadcallback(std::bind(&EventLoop::handlewakeup,this));
    wakechannel_->enablereading();
    timerchannel_->setreadcallback(std::bind(&EventLoop::handletimer,this));
    timerchannel_->enablereading();
}   

EventLoop::~EventLoop()
{
    
}

void EventLoop::run() //�����¼�ѭ��
{
    threadid_ = syscall(SYS_gettid); //��ȡʱ��ѭ�������̵߳�id
    while(stop_ == false)  //�¼�ѭ��
    {
        std::vector<Channel *> channels = ep_->loop(10*1000); //�ȴ����ӵ�fd���¼�����
        //���channelsΪ�� ��ʾ��ʱ �ص�TcpServer::epolltimeout()
        if(channels.size() == 0)
        {
            epolltimeoutcallback_(this);
        }
        else
        {
            for(auto &ch:channels)
            {
                ch->handleevent();  //����epoll_wait()���ص��¼�
            }
        }
    }    
}


void EventLoop::stop() //ֹͣ�¼�ѭ��
{
    stop_ = true;
    wakeup();  //�����¼�ѭ�� ���û�����д��� �¼�ѭ�������´�������ʱ����epoll_wait()��ʱʱ�Ż�ͣ����    
}

void EventLoop::updatechannel(Channel *ch) //��channel��ӵ�������� channel����fd Ҳ����Ҫ���ӵ��¼�
{
    ep_->updatechannel(ch);
}

void EventLoop::removechannel(Channel *ch) //�Ӻ������ɾ��channel
{
    ep_->removechannel(ch);
}

void EventLoop::setepolltimeoutcallback(std::function<void(EventLoop*)> fn)  //����epoll_wait()��ʱ�Ļص�����
{
    epolltimeoutcallback_ = fn;
}

bool EventLoop::isinloopthread() //�жϵ�ǰ�߳��Ƿ�Ϊ�¼�ѭ���߳�
{
    return threadid_ == syscall(SYS_gettid);
}

void EventLoop::queueinloop(std::function<void()> fn) //��������ӵ�������
{
    {
    std::lock_guard<std::mutex> gd(mutex_); //��������м���
    taskqueue_.push(fn); //�������
    }
    wakeup();  //�����¼�ѭ��
}

void EventLoop::wakeup() //��eventfd�����¼�ѭ���߳�
{
    uint64_t val = 1;
    write(wakeupfd_,&val,sizeof(val));
}

void EventLoop::handlewakeup() //�¼�ѭ���̱߳�eventfd���Ѻ�ִ�еĺ���
{
    uint64_t val;
    read(wakeupfd_,&val,sizeof(val)); //��eventfd�ж�ȡ���� �������ȡ eventfd�Ķ��¼���һֱ����
    std::function<void()> fn;
    std::lock_guard<std::mutex> gd(mutex_); //��������м���
    //ִ�ж�����ȫ���ķ�������
    while(taskqueue_.size() > 0)
    {
        fn = std::move(taskqueue_.front()); //����һ��Ԫ��
        taskqueue_.pop();
        fn(); //ִ������
    }
}

void EventLoop::handletimer() //������ʱ�¼��ĺ���
{
    //���¼�ʱ
    struct itimerspec timeout; //��ʱʱ������ݽṹ
    memset(&timeout, 0, sizeof(struct itimerspec));
    timeout.it_value.tv_sec = timetvl_; //��ʱʱ��
    timeout.it_value.tv_nsec = 0;
    timerfd_settime(timerfd_, 0, &timeout, 0);
    if(mainloop_)
    {
        printf("���¼�ѭ�������ӵ���");
    }
    else
    {
        printf("���¼�ѭ�������ӵ���");
        time_t now = time(0); //��ȡ��ǰʱ��
        for(auto aa:conns_)
        {
            if(aa.second->timeout(now,timeout_))
            {
                {
                    std::lock_guard<std::mutex> gd(mmutex_);
                    conns_.erase(aa.first);  //��Eventloop��map��ɾ����ʱ��conn
                }
                timercallback_(aa.first);  //��TcpServer��map��ɾ����ʱ��conn
            }
        }
    }    
}

void EventLoop::newconnection(spConnection conn) //��Connection���󱣴���conns_��
{
    std::lock_guard<std::mutex> gd(mmutex_); 
    conns_[conn->fd()] = conn;
}

void EventLoop::settimercallback(std::function<void(int)> fn) //��������ΪTcpServer::removeconn()
{
    timercallback_ = fn;
}