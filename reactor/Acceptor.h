#pragma once
#include <cstdint>
#include<functional>
#include"Socket.h"
#include"InetAddress.h"
#include"Channel.h"
#include"EventLoop.h"
#include<memory>

class Acceptor
{
private:
    EventLoop *loop_;  //Acceptor��Ӧ���¼�ѭ�� �ڹ��캯���д���
    Socket servsock_; //��������ڼ�����socket �ڹ��캯���д���
    Channel acceptorchannel_; //Acceptor��Ӧ��channel �ڹ��캯���д���
    std::function<void(std::unique_ptr<Socket>)> newconnectioncb_; //�����¿ͻ�����������Ļص����� ��ָ��TcpServer::newconnection()
public:
    Acceptor(EventLoop *loop,const std::string &ip,const uint16_t port);
    ~Acceptor();
    void newconnection(); //�����¿ͻ����˽�����
    
    //���ô����¿ͻ�����������ص����� ���ڴ���Acceptor�����ʱ��TcpServer��Ĺ��캯���У� ����
    void setnewconnenctioncb(std::function<void(std::unique_ptr<Socket>)> fn);
};