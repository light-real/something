#include "Acceptor.h"
#include "InetAddress.h"
#include "Socket.h"
#include <functional>
#include <memory>
    

/*
    EventLoop *loop_;  //Acceptor对应的事件循环 在构造函数中传入
    Socket servsock_; //服务端用于监听的socket 在构造函数中创建
    Channel acceptorchannel_; //Acceptor对应的channel 在构造函数中创建
    std::function<void(std::unique_ptr<Socket>)> newconnectioncb_; //处理新客户端连接请求的回调函数 将指向TcpServer::newconnection()
*/
Acceptor::Acceptor(EventLoop *loop,const std::string &ip,const uint16_t port)
        :loop_(loop),servsock_(createnonblocking()),acceptorchannel_(loop_, servsock_.fd())
{
    InetAddress servaddr(ip,port); //服务端的地址和协议
    servsock_.setreuseport(true);
    servsock_.setreuseaddr(true);
    servsock_.settcpnodelay(true);
    servsock_.setkeepalive(true);
    servsock_.bind(servaddr);
    servsock_.listen();
    acceptorchannel_.setreadcallback(std::bind(&Acceptor::newconnection,this));
    acceptorchannel_.enablereading(); //让epoll_wait()监视servchannel的读事件
}

Acceptor::~Acceptor()
{
    
}

void Acceptor::newconnection() //处理新客户端了解请求
{
    InetAddress clientaddr; //客户端的地址和协议
    std::unique_ptr<Socket> clientsock(new Socket(servsock_.accept(clientaddr)));    
    clientsock->setipport(clientaddr.ip(), clientaddr.port());
    newconnectioncb_(std::move(clientsock)); //回调TcpServer::newconnnection()
}

//设置处理新客户端连接请求回调函数 将在创建Acceptor对象的时候（TcpServer类的构造函数中） 设置
void Acceptor::setnewconnenctioncb(std::function<void(std::unique_ptr<Socket>)> fn)
{
    newconnectioncb_ = fn;
}