#pragma once
#include <cstdint>
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include "Epoll.h"
#include "EventLoop.h"
#include "InetAddress.h"
#include "Socket.h"

class EventLoop;
class Channel
{
private:
    int fd_ = -1;  //Channelӵ�е�fd Channel��fd��һ��һ��ϵ
    EventLoop *loop_;  //Channel��Ӧ���¼�ѭ�� Channel��EventLoop�Ƕ��һ��ϵ һ��Channelֻ��Ӧһ��EventLoop
    bool inepoll_ = false; //Channel�Ƿ��Ѿ���ӵ�epoll���� ���δ��� ����epoll_ctl()��ʱ����EPOLL_CTL_ADD ������EPOLL_CTL_MOD
    uint32_t events_ = 0;  //fd_��Ҫ���ӵ��¼� listenfd��clientfd��Ҫ����EPOLLIN clientfd��������Ҫ����EPOLLOUT
    uint32_t revents_ = 0;  //fd_�ѷ������¼�
    
    //fd_���¼��Ļص����� �����acceptchannel ���ص�Acceptor::newconnection() 
    //�����clientchannel ���ص�Connection::onmessage()
    std::function<void()> readcallback_;  
    std::function<void()> closecallback_;  //�ر�fd_�Ļص����� ���ص�Connection::closecallback()
    std::function<void()> errorcallback_; //fd_�����˴���Ļص����� ���ص�Connnect::errorcallback()
    std::function<void()> writecallback_; //fd_д�¼��Ļص����� ���ص�Connenct::writecallback()

public:
    Channel(EventLoop* loop,int fd); //���캯�� Channel��Acceptor��Connnection���²���
    ~Channel();   //��������
    int fd();  //����fd_��Ա
    void useet();  //���ñ�Ե����
    void enablereading();  //��epoll_wait()����fd_�Ķ��¼� ע����¼�
    void disablereading();  //ȡ�����¼�
    void enablewriting();  //ע��д�¼�
    void disablewriting(); //ȡ��д�¼�
    void disableall();  //ȡ��ȫ���¼�
    void remove();   //���¼�ѭ����ɾ��Channel
    void setinepoll(bool inepoll); //����inepoll_��Ա��ֵ
    void setrevents(uint32_t ev); //����revents_��Ա��ֵΪ����ev
    bool inpoll();  //����inepoll_��Ա��ֵ
    uint32_t events(); //����events_��Ա��ֵ
    uint32_t revents(); //����revents_��Ա��ֵ
    void handleevent(); //�¼������� epoll_wait()���ص�ʱ�� ִ����
    void setreadcallback(std::function<void()> fn);  //����fd_���¼��Ļص�����
    void setwritecallback(std::function<void()> fn); //����fd_д�¼��Ļص�����
    void setclosecallback(std::function<void()> fn); //���ùر�fd_�¼��Ļص�����
    void seterrorcallback(std::function<void()> fn); //����fd_�����˴���Ļص�����
};