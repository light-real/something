#include "TcpServer.h"
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "ThreadPool.h"
#include <cstdio>
#include <functional>
#include <mutex>

TcpServer::TcpServer(const std::string &ip, const uint16_t port, int threadnum)
    : threadnum_(threadnum), mainloop_(new EventLoop(true)),
      acceptor_(mainloop_.get(), ip, port), threadpool_(threadnum, "IO")
{
    // 设置epoll_wait()超时的回调函数
    mainloop_->setepolltimeoutcallback(std::bind(&TcpServer::epolltimeout, this, std::placeholders::_1));
    // 设置处理新客户端连接请求的回调函数
    acceptor_.setnewconnenctioncb(std::bind(&TcpServer::newconnection, this, std::placeholders::_1));
    // 创建从事件循环
    for (int i = 0; i < threadnum_; i++)
    {
        subloops_.emplace_back(new EventLoop(false, 5, 10)); // 创建从事件循环 存入subloops_容器中
        subloops_[i]->setepolltimeoutcallback(std::bind(&TcpServer::epolltimeout, this, std::placeholders::_1));
        subloops_[i]->settimercallback(std::bind(&TcpServer::removeconn, this, std::placeholders::_1));
        threadpool_.addtask(std::bind(&EventLoop::run, subloops_[i].get())); // 在线程池在运行从事件循环
    }
}

TcpServer::~TcpServer()
{
}

void TcpServer::start() // 运行事件循环
{
    mainloop_->run();
}

void TcpServer::stop() // 停止IO线程和事件循环
{
    mainloop_->stop(); // 停止主事件循环
    printf("mainloop_ has stop.\n");
    // 停止从事件循环
    for (int i = 0; i < threadnum_; i++)
    {
        subloops_[i]->stop();
    }
    printf("subloop has stop.\n");
    // 停止IO线程
    threadpool_.stop();
    printf("IO thread has stop.\n");
}
void TcpServer::newconnection(std::unique_ptr<Socket> clientsock) // 处理新客户端连接请求 在Acceptor类中回调此函数
{
    // 把新建的conn分配给从事件循环
    spConnection conn(new Connection(subloops_[clientsock->fd() % threadnum_].get(), std::move(clientsock)));
    conn->setclosecallback(std::bind(&TcpServer::closeconnection, this, std::placeholders::_1));
    conn->seterrorcallback(std::bind(&TcpServer::errorconnection, this, std::placeholders::_1));
    conn->setonmessagecallback(std::bind(&TcpServer::onmessage, this, std::placeholders::_1, std::placeholders::_2));
    conn->setsendcompletecallback(std::bind(&TcpServer::sendcomplete, this, std::placeholders::_1));
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_[conn->fd()] = conn; // 把conn存放到TcpServer的map容器中
    }
    subloops_[conn->fd() % threadnum_]->newconnection(conn); // 把conn存放到EventLoop的map容器中
    if (newconnectioncb_)
    {
        newconnectioncb_(conn); // 回调EchoServer::HandleNewConnection()
    }
}

void TcpServer::closeconnection(spConnection conn) // 关闭客户端的连接 在Connection类中回调此函数
{
    if (closeconnectioncb_)
    {
        closeconnectioncb_(conn); // 回调EchoServer::HandleClose()
    }
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(conn->fd()); // 从map中删除conn
    }
}

void TcpServer::errorconnection(spConnection conn) // 客户端的连接错误 在Connection类中回调此函数
{
    if (errorconnectioncb_)
    {
        errorconnectioncb_(conn); // 回调EchoServer::HandleError()
    }
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(conn->fd()); // 从map中删除conn
    }
}

void TcpServer::onmessage(spConnection conn, std::string &message) // 处理客户端的请求报文 在Connection类中回调此函数
{
    if (onmessagecb_)
    {
        onmessagecb_(conn, message); // 回调EchoServer::HandleMessage()
    }
}

void TcpServer::sendcomplete(spConnection conn) // 数据发送完成后 在Connection类中回调此函数
{
    if (sendcompletecb_)
    {
        sendcompletecb_(conn); // 回调EchoServer::HandleSendCompelete()
    }
}

void TcpServer::epolltimeout(EventLoop *loop) // epoll_wait()超时 在EventLoop类中回调此函数
{
    if (timeoutcb_)
    {
        timeoutcb_(loop); // 回调EchoServer::HandleTimeOut()
    }
}

void TcpServer::setnewconnenctioncb(std::function<void(spConnection)> fn)
{
    newconnectioncb_ = fn;
}
void TcpServer::setcloseconnectioncb(std::function<void(spConnection)> fn)
{
    closeconnectioncb_ = fn;
}
void TcpServer::seterrorconnectioncb(std::function<void(spConnection)> fn)
{
    errorconnectioncb_ = fn;
}
void TcpServer::setonmessagecb(std::function<void(spConnection, std::string &message)> fn)
{
    onmessagecb_ = fn;
}
void TcpServer::setsendcompeletecb(std::function<void(spConnection)> fn)
{
    sendcompletecb_ = fn;
}
void TcpServer::settimeoutcb(std::function<void(EventLoop *)> fn)
{
    timeoutcb_ = fn;
}
void TcpServer::removeconn(int fd) // 删除conns_中的Connection对象 在EventLoop::handletimer()中将回调此函数
{
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(fd); // 从map中删除conn
    }
}