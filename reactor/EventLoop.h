#pragma once 
#include <functional>
#include "Channel.h"
#include "Epoll.h"
#include <memory>
#include <sys/types.h>
#include <unistd.h>
#include <queue>
#include <mutex>
#include <map>
#include <atomic>
#include <sys/eventfd.h>
#include <sys/syscall.h>
#include <sys/timerfd.h>  //��ʱ����Ҫ�������ͷ�ļ�
#include "Connection.h"

class Channel;
class Epoll;
class Connection;
using spConnection = std::shared_ptr<Connection>;

//�¼�ѭ����
class EventLoop
{
private:
    int timetvl_; //����ʱ���� ��λ��
    int timeout_; //Connection����ʱʱ�� ��λ��
    std::unique_ptr<Epoll> ep_;  //ÿ���¼�ѭ��ֻ��һ��Epoll
    std::function<void(EventLoop*)> epolltimeoutcallback_; //epoll_wait()��ʱ�Ļص�����
    pid_t threadid_; //�¼�ѭ�������̵߳�id
    std::queue<std::function<void()>> taskqueue_; //�¼�ѭ���̱߳�eventfd���Ѻ�ִ�е��������
    std::mutex mutex_; //�������ͬ���Ļ�����
    int wakeupfd_; //���ڻ����¼�ѭ���̵߳�eventfd
    std::unique_ptr<Channel> wakechannel_; //eventfd��Channel
    int timerfd_; //��ʱ����fd
    std::unique_ptr<Channel> timerchannel_; //��ʱ����channel
    bool mainloop_; //true-��ʾ���¼�ѭ�� false-��ʾ���¼�ѭ��
    std::mutex mmutex_; //����conns_�Ļ�����
    std::map<int,spConnection> conns_; //��������ڸ��¼�ѭ����ȫ����Connenction����
    std::function<void(int)> timercallback_; //ɾ��TcpServer�г�ʱ��Connection���� ��������ΪTcpServer::removeconn()
    std::atomic_bool stop_; //��ʼֵΪfalse �������Ϊtrue ��ʾֹͣ�¼�ѭ��

public:
    EventLoop(bool mainloop_,int timetvl_=30,int timeout_ = 80); //�ڹ��캯���д���Epoll����ep_
    ~EventLoop();
    void run(); //�����¼�ѭ��
    void stop(); //ֹͣ�¼�ѭ��
    void updatechannel(Channel *ch); //��channel��ӵ�������� channel����fd Ҳ����Ҫ���ӵ��¼�
    void removechannel(Channel *ch); //�Ӻ������ɾ��channel
    void setepolltimeoutcallback(std::function<void(EventLoop*)> fn);  //����epoll_wait()��ʱ�Ļص�����
    bool isinloopthread(); //�жϵ�ǰ�߳��Ƿ�Ϊ�¼�ѭ���߳�
    void queueinloop(std::function<void()> fn); //��������ӵ�������
    void wakeup(); //��eventfd�����¼�ѭ���߳�
    void handlewakeup(); //�¼�ѭ���̱߳�eventfd���Ѻ�ִ�еĺ���
    void handletimer(); //������ʱ�¼��ĺ���
    void newconnection(spConnection conn); //��Connection���󱣴���conns_��
    void settimercallback(std::function<void(int)> fn); //��������ΪTcpServer::removeconn()
};