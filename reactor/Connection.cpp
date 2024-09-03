#include "Connection.h"
#include "Epoll.h"
#include <cerrno>
#include <cstdio>
#include <functional>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
    EventLoop *loop_; //Connection对应事件的循环 在构造函数中传入
    std::unique_ptr<Socket> clientsock_; //与客户端通讯的Socket
    std::unique_ptr<Channel> clientchannel_; //Connection对应的channel 在构造函数中创建
    Buffer inputbuffer_;  //接收缓冲区
    Buffer outputbuffer_; //发送缓冲区
    std::atomic_bool disconnect_; //客户端连接是否已断开 如果已断开 设置为true
    std::function<void(spConnection)> closecallback_;  //关闭fd_的回调函数 将回调TcpServer::closeconnection()
    std::function<void(spConnection)> errorcallback_;  //fd_发生错误的回调函数 将回调TcpServer::errorconnection()
    std::function<void(spConnection,std::string&)> onmessagecallback_;  //处理报文的回调函数 将回调TcpServer::onmessage()
    std::function<void(spConnection)> sendcompletecallback_;  //发送数据完成的回调函数 将回调TcpServer::sendcomplete()
    Timestamp lastatime_; //时间戳 创建Connection对象时为当前时间 每接收一个报文 把时间戳更新为当前时间
*/

Connection::Connection(EventLoop *loop,std::unique_ptr<Socket> clientsock)
           :loop_(loop),clientsock_(std::move(clientsock)),disconnect_(false),
            clientchannel_(new Channel(loop_,clientsock_->fd()))
{
    //为新客户端连接准备读事件 并添加到epoll中
    clientchannel_->setreadcallback(std::bind(&Connection::onmessage,this));
    clientchannel_->setclosecallback(std::bind(&Connection::closecallback,this));
    clientchannel_->seterrorcallback(std::bind(&Connection::errorcallback,this));
    clientchannel_->setwritecallback(std::bind(&Connection::writecallback,this));
    clientchannel_->useet(); //客户端练上来的fd采用边缘触发
    clientchannel_->enablereading(); //让epoll_wait()监视clientchannel的读事件
}

Connection::~Connection()
{
    
}

int Connection::fd() const //返回客户端的fd
{
    return clientsock_->fd();
}

std::string Connection::ip() const //返回客户端的ip
{
    return clientsock_->ip();
}

uint16_t Connection::port() const //返回客户端的port
{
    return clientsock_->port();
}

void Connection::onmessage() //处理对端发送过来的信息
{
    char buffer[1024];
    while (true)  //由于使用非阻塞IO 一次读取buffer大小数据 直到全部的数据读取完毕
    {
        bzero(&buffer, sizeof(buffer));
        ssize_t nread = read(fd(),buffer,sizeof(buffer));
        if(nread > 0)  //如果成功读取到了数据
        {
            inputbuffer_.append(buffer,nread); //把读取的数据追加到接收缓冲区中
        }
        else if(nread == -1 && errno == EINTR) //读取数据的时候被信号中断 继续读取
        {
            continue;
        }
        else if(nread == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) //全部数据已读取完毕
        {
            std::string message;
            while(true) //从接收缓冲区中分析客户端的请求消息
            {
                if(inputbuffer_.pickmessage(message) == false) break;
                lastatime_ = Timestamp::now();  //更新Connenction的时间戳
                onmessagecallback_(shared_from_this(),message); //回调TcpServer::onmessage()处理客户端的请求信息
            }
            break;
        }
        else if(nread == 0) //客户端的连接已断开
        {
            closecallback(); //回调TcpServer::closecallback()
            break;
        }
    }
}

void Connection::closecallback() //Tcp连接关闭的回调函数 供Channel回调
{
    disconnect_ = true;
    clientchannel_->remove();  //从事件循环中删除Channel
    closecallback_(shared_from_this()); //回调TcpServer::errorconnection
}

void Connection::errorcallback() //Tcp连接错误的回调函数 供Channel回调
{
    disconnect_ = true;
    clientchannel_->remove();  //从事件循环中删除Channel
    closecallback_(shared_from_this()); //回调TcpServer::errorconnection
}

void Connection::writecallback() //处理写事件的回调函数 供Channel回调
{
    int writen = ::send(fd(), outputbuffer_.data(), outputbuffer_.size(), 0); //尝试把outputbuffer_中的数据全部发送出去
    if(writen > 0)
    {
        outputbuffer_.erase(0,writen); //从outputbuffer_中删除已发送成功的字节数
    }
    //如果发送缓冲区中没有数据了 表示数据已发送完成 不再关注写事件
    if(outputbuffer_.size()==0)
    {
        clientchannel_->disablewriting();
        sendcompletecallback_(shared_from_this());
    }
}

void Connection::setclosecallback(std::function<void(spConnection)> fn) //设置关闭fd_的回调函数
{
    closecallback_ = fn;
}

void Connection::seterrorcallback(std::function<void(spConnection)> fn)
{
    errorcallback_ = fn;
} 

void Connection::setonmessagecallback(std::function<void(spConnection,std::string&)> fn)
{
    onmessagecallback_ = fn;
}

void Connection::setsendcompletecallback(std::function<void(spConnection)> fn)
{
    sendcompletecallback_ = fn;
}

void Connection::send(const char *data,size_t size) //发送数据 不管在任何线程中 都是调用此函数发送数据
{
    if(disconnect_ == true)
    {
        printf("客户端连接已断开了,send()直接返回.\n");
        return;
    }
    if(loop_->isinloopthread()) //判断当前线程是否为事件循环线程 即IO线程
    {
        //如果当前线程是IO线程 直接调用sendinloop()发送数据
        sendinloop(data, size);
    }
    else
    {
        //如果当前线程不是IO线程 调用Eventloop::queueinloop() 把sendinloop()交给事件循环线程去执行
        loop_->queueinloop(std::bind(&Connection::sendinloop,this,data,size));
    }
}

void Connection::sendinloop(const char *data,size_t size) //发送数据 如果当前线程时IO线程 直接调用此函数 如果时工作线程 将此函数传给IO线程去执行
{
    outputbuffer_.appendwithsep(data,size); //把需要发送的数据保存到Connection的发送缓冲区
    clientchannel_->enablewriting(); //注册写事件
}

bool Connection::timeout(time_t now,int val) //判断TCP连接是否超时(空闲太久)
{
    return now-lastatime_.toint() > val;
}