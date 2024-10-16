#include "Channel.h"
#include <sys/epoll.h>

Channel::Channel(EventLoop* loop,int fd):loop_(loop),fd_(fd) //���캯�� Channel��Acceptor��Connnection���²���
{

}

Channel::~Channel()   //��������
{
    //������������ ��Ҫ����loop_ Ҳ���ܹر�fd_ ��Ϊ����������������Channel�� Channel��ֻ����Ҫ���� ʹ�����Ƕ���
}

int Channel::fd()  //����fd_��Ա
{
    return fd_;
}

void Channel::useet()  //���ñ�Ե����
{
    events_ = events_|EPOLLET;
}

void Channel::enablereading()  //��epoll_wait()����fd_�Ķ��¼� ע����¼�
{
    events_|=EPOLLIN;
    loop_->updatechannel(this);
}

void Channel::disablereading()  //ȡ�����¼�
{
    events_&=~EPOLLIN;
}

void Channel::enablewriting()  //ע��д�¼�
{
    events_ |= EPOLLOUT;
}

void Channel::disablewriting() //ȡ��д�¼�
{
    events_ &= ~EPOLLOUT;
    loop_->updatechannel(this);
}

void Channel::disableall()  //ȡ��ȫ���¼�
{
    events_ = 0;
    loop_->updatechannel(this);
}

void Channel::remove()   //���¼�ѭ����ɾ��Channel
{
    disableall(); //��ȡ��ȫ���¼�
    loop_->removechannel(this); //�Ӻ������ɾ��fd
}

void Channel::setinepoll(bool inepoll) //����inepoll_��Ա��ֵ
{
    inepoll_ = inepoll;
}

void Channel::setrevents(uint32_t ev) //����revents_��Ա��ֵΪ����ev
{
    revents_ = ev;
}

bool Channel::inpoll()  //����inepoll_��Ա��ֵ
{
    return inepoll_;
}

uint32_t Channel::events() //����events_��Ա��ֵ
{
    return events_;
}

uint32_t Channel::revents() //����revents_��Ա��ֵ
{
    return revents_;
}

void Channel::handleevent() //�¼������� epoll_wait()���ص�ʱ�� ִ����
{
    if(revents_&EPOLLRDHUP) //�Է��ѹر� ��Щϵͳ��ⲻ�� ����ʹ��EPOLLIN recv()����0
    {
        closecallback_();  //�ص�Connnection::closecallback();
    }
    else if(revents_&(EPOLLIN|EPOLLPRI)) //���ջ������������ݿ��Զ�
    {
        //fd_���¼��Ļص����� �����acceptchannel ���ص�Acceptor::newconnection() 
        //�����clientchannel ���ص�Connection::onmessage()
        readcallback_();
    }
    else if(revents_ &EPOLLOUT) //��������Ҫд
    { 
        writecallback_(); //�ص�Connnection::writecallback()
    }
    else // �����¼� ����Ϊ����
    {
        errorcallback_(); //�ص�Connenction::errorcallback()
    }
}

void Channel::setreadcallback(std::function<void()> fn)  //����fd_���¼��Ļص�����
{
    readcallback_ = fn;
}

void Channel::setwritecallback(std::function<void()> fn) //����fd_д�¼��Ļص�����
{
    writecallback_ = fn;
}

void Channel::setclosecallback(std::function<void()> fn) //���ùر�fd_�¼��Ļص�����
{
    closecallback_ = fn;
}

void Channel::seterrorcallback(std::function<void()> fn) //����fd_�����˴���Ļص�����
{
    errorcallback_ = fn;
}