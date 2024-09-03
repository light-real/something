#include "EchoServer.h"
#include "ThreadPool.h"
#include "Timestamp.h"
#include <cstdio>
#include <functional>

EchoServer::EchoServer(const std::string &ip,const uint16_t port,int subthreadnum,int workthreadnum)
           :tcpserver_(ip,port,subthreadnum),threadpool_(workthreadnum, "WORKS")
{
    tcpserver_.setnewconnenctioncb(std::bind(&EchoServer::HandleNewConnection,this,std::placeholders::_1));
    tcpserver_.setcloseconnectioncb(std::bind(&EchoServer::HandleClose,this,std::placeholders::_1));
    tcpserver_.seterrorconnectioncb(std::bind(&EchoServer::HandleError,this,std::placeholders::_1));
    tcpserver_.setonmessagecb(std::bind(&EchoServer::HandleMessage,this,std::placeholders::_1,std::placeholders::_2));
    tcpserver_.setsendcompeletecb(std::bind(&EchoServer::HandleSendCompelete,this,std::placeholders::_1));
}

EchoServer::~EchoServer()
{
    
}

void EchoServer::Start() //启动服务
{
    tcpserver_.start();
}

void EchoServer::Stop() //终止服务
{
    //停止工作线程
    threadpool_.stop();
    printf("WORK thread has stop\n");
    //停止IO线程(事件循环)
    tcpserver_.stop();
}

void EchoServer::HandleNewConnection(spConnection conn) //处理新客户端的请求连接 在TcpServer类中回调此函数
{
    printf("%s new connection(fd=%d,ip=%s,port=%d)ok.\n",
    Timestamp::now().tostring().c_str(),conn->fd(),conn->ip().c_str(),conn->port());
    //增加其他的代码
}

void EchoServer::HandleClose(spConnection conn) //关闭客户端的连接 在TcpServer类中回调此函数
{
    printf("%s new connection closed(fd=%d,ip=%s,port=%d)ok.\n",
    Timestamp::now().tostring().c_str(),conn->fd(),conn->ip().c_str(),conn->port());    
}

void EchoServer::HandleError(spConnection conn) //客户端的连接错误 在TcpServer类中回调此函数
{
    
}

void EchoServer::HandleMessage(spConnection conn,std::string&message) //处理客户端的请求报文 在TcpServer类中回调此函数
{
    if(threadpool_.size()==0)
    {
        //如果没有工作线程 表示在IO线程中计算
        OnMessage(conn, message);
    }
    else
    {
        //把业务添加到线程池的任务队列中 交给工作线程去处理业务
        threadpool_.addtask(std::bind(&EchoServer::OnMessage,this,conn,message));
    }
}

void EchoServer::HandleSendCompelete(spConnection conn) //数据发送完成后 在TcpServer类中回调此函数
{
    
}

void EchoServer::OnMessage(spConnection conn,std::string& message) //处理客户端的请求报文 用于添加给线程池 
{
    message = "reply" +message; //回显业务
    conn->send(message.data(), message.size());
}