#pragma once
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <functional>
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Buffer.h"
#include "Timestamp.h"
#include <memory>
#include <atomic>
#include <sys/syscall.h>

class EventLoop;
class Channel;
class Connection;
using spConnection = std::shared_ptr<Connection>;

class Connection:public std::enable_shared_from_this<Connection>
{
private:
    EventLoop *loop_; //Connection��Ӧ�¼���ѭ�� �ڹ��캯���д���
    std::unique_ptr<Socket> clientsock_; //��ͻ���ͨѶ��Socket
    std::unique_ptr<Channel> clientchannel_; //Connection��Ӧ��channel �ڹ��캯���д���
    Buffer inputbuffer_;  //���ջ�����
    Buffer outputbuffer_; //���ͻ�����
    std::atomic_bool disconnect_; //�ͻ��������Ƿ��ѶϿ� ����ѶϿ� ����Ϊtrue
    std::function<void(spConnection)> closecallback_;  //�ر�fd_�Ļص����� ���ص�TcpServer::closeconnection()
    std::function<void(spConnection)> errorcallback_;  //fd_��������Ļص����� ���ص�TcpServer::errorconnection()
    std::function<void(spConnection,std::string&)> onmessagecallback_;  //�����ĵĻص����� ���ص�TcpServer::onmessage()
    std::function<void(spConnection)> sendcompletecallback_;  //����������ɵĻص����� ���ص�TcpServer::sendcomplete()
    Timestamp lastatime_; //ʱ��� ����Connection����ʱΪ��ǰʱ�� ÿ����һ������ ��ʱ�������Ϊ��ǰʱ��
public:
    Connection(EventLoop *loop,std::unique_ptr<Socket> clientsock);
    ~Connection();
    int fd() const; //���ؿͻ��˵�fd
    std::string ip() const; //���ؿͻ��˵�ip
    uint16_t port() const; //���ؿͻ��˵�port
    void onmessage(); //����Զ˷��͹�������Ϣ
    void closecallback(); //Tcp���ӹرյĻص����� ��Channel�ص�
    void errorcallback(); //Tcp���Ӵ���Ļص����� ��Channel�ص�
    void writecallback(); //����д�¼��Ļص����� ��Channel�ص�
    void setclosecallback(std::function<void(spConnection)> fn); //���ùر�fd_�Ļص�����
    void seterrorcallback(std::function<void(spConnection)> fn); 
    void setonmessagecallback(std::function<void(spConnection,std::string&)> fn);
    void setsendcompletecallback(std::function<void(spConnection)> fn); 
    void send(const char *data,size_t size); //�������� �������κ��߳��� ���ǵ��ô˺�����������
    void sendinloop(const char *data,size_t size); //�������� �����ǰ�߳�ʱIO�߳� ֱ�ӵ��ô˺��� ���ʱ�����߳� ���˺�������IO�߳�ȥִ��
    bool timeout(time_t now,int val); //�ж�TCP�����Ƿ�ʱ(����̫��)
};