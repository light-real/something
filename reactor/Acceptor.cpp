#include "Acceptor.h"
#include "InetAddress.h"
#include "Socket.h"
#include <functional>
#include <memory>
    

/*
    EventLoop *loop_;  //Acceptor��Ӧ���¼�ѭ�� �ڹ��캯���д���
    Socket servsock_; //��������ڼ�����socket �ڹ��캯���д���
    Channel acceptorchannel_; //Acceptor��Ӧ��channel �ڹ��캯���д���
    std::function<void(std::unique_ptr<Socket>)> newconnectioncb_; //�����¿ͻ�����������Ļص����� ��ָ��TcpServer::newconnection()
*/
Acceptor::Acceptor(EventLoop *loop,const std::string &ip,const uint16_t port)
        :loop_(loop),servsock_(createnonblocking()),acceptorchannel_(loop_, servsock_.fd())
{
    InetAddress servaddr(ip,port); //����˵ĵ�ַ��Э��
    servsock_.setreuseport(true);
    servsock_.setreuseaddr(true);
    servsock_.settcpnodelay(true);
    servsock_.setkeepalive(true);
    servsock_.bind(servaddr);
    servsock_.listen();
    acceptorchannel_.setreadcallback(std::bind(&Acceptor::newconnection,this));
    acceptorchannel_.enablereading(); //��epoll_wait()����servchannel�Ķ��¼�
}

Acceptor::~Acceptor()
{
    
}

void Acceptor::newconnection() //�����¿ͻ����˽�����
{
    InetAddress clientaddr; //�ͻ��˵ĵ�ַ��Э��
    std::unique_ptr<Socket> clientsock(new Socket(servsock_.accept(clientaddr)));    
    clientsock->setipport(clientaddr.ip(), clientaddr.port());
    newconnectioncb_(std::move(clientsock)); //�ص�TcpServer::newconnnection()
}

//���ô����¿ͻ�����������ص����� ���ڴ���Acceptor�����ʱ��TcpServer��Ĺ��캯���У� ����
void Acceptor::setnewconnenctioncb(std::function<void(std::unique_ptr<Socket>)> fn)
{
    newconnectioncb_ = fn;
}