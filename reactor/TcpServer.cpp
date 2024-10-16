#include"TcpServer.h"
#include "Acceptor.h"
#include "Channel.h"
#include "Connection.h"
#include "ThreadPool.h"
#include <cstdio>
#include <functional>
#include <mutex>

TcpServer::TcpServer(const std::string &ip,const uint16_t port,int threadnum)
          :threadnum_(threadnum),mainloop_(new EventLoop(true)),
          acceptor_(mainloop_.get(),ip,port),threadpool_(threadnum, "IO")
{
    //����epoll_wait()��ʱ�Ļص�����
    mainloop_->setepolltimeoutcallback(std::bind(&TcpServer::epolltimeout,this,std::placeholders::_1));
    //���ô����¿ͻ�����������Ļص�����
    acceptor_.setnewconnenctioncb(std::bind(&TcpServer::newconnection,this,std::placeholders::_1));
    //�������¼�ѭ��
    for(int i = 0;i<threadnum_;i++)
    {
        subloops_.emplace_back(new EventLoop(false,5,10)); //�������¼�ѭ�� ����subloops_������
        subloops_[i]->setepolltimeoutcallback(std::bind(&TcpServer::epolltimeout,this,std::placeholders::_1));
        subloops_[i]->settimercallback(std::bind(&TcpServer::removeconn,this,std::placeholders::_1));
        threadpool_.addtask(std::bind(&EventLoop::run,subloops_[i].get())); //���̳߳������д��¼�ѭ��
    }
}

TcpServer::~TcpServer()
{
    
}

void TcpServer::start()  //�����¼�ѭ��
{
    mainloop_->run();
}

void TcpServer::stop() //ֹͣIO�̺߳��¼�ѭ��
{
    mainloop_->stop(); //ֹͣ���¼�ѭ��
    printf("mainloop_ has stop.\n");
    //ֹͣ���¼�ѭ��
    for(int i = 0;i<threadnum_;i++)
    {
        subloops_[i]->stop();
    }
    printf("subloop has stop.\n");
    //ֹͣIO�߳�
    threadpool_.stop();
    printf("IO thread has stop.\n");
}
void TcpServer::newconnection(std::unique_ptr<Socket> clientsock) //�����¿ͻ����������� ��Acceptor���лص��˺���
{
    //���½���conn��������¼�ѭ��
    spConnection conn(new Connection(subloops_[clientsock->fd()%threadnum_].get(),std::move(clientsock)));
    conn->setclosecallback(std::bind(&TcpServer::closeconnection,this,std::placeholders::_1));
    conn->seterrorcallback(std::bind(&TcpServer::errorconnection,this,std::placeholders::_1));
    conn->setonmessagecallback(std::bind(&TcpServer::onmessage,this,std::placeholders::_1,std::placeholders::_2));
    conn->setsendcompletecallback(std::bind(&TcpServer::sendcomplete,this,std::placeholders::_1));
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_[conn->fd()] = conn; //��conn��ŵ�TcpServer��map������
    }
    subloops_[conn->fd()%threadnum_]->newconnection(conn); //��conn��ŵ�EventLoop��map������
    if(newconnectioncb_)
    {
        newconnectioncb_(conn); //�ص�EchoServer::HandleNewConnection()
    }
}

void TcpServer::closeconnection(spConnection conn) //�رտͻ��˵����� ��Connection���лص��˺���
{
    if(closeconnectioncb_)
    {
        closeconnectioncb_(conn);//�ص�EchoServer::HandleClose()
    }
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(conn->fd()); //��map��ɾ��conn
    }
}

void TcpServer::errorconnection(spConnection conn) //�ͻ��˵����Ӵ��� ��Connection���лص��˺���
{
        if(errorconnectioncb_)
    {
        errorconnectioncb_(conn);//�ص�EchoServer::HandleError()
    }
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(conn->fd()); //��map��ɾ��conn
    }
}

void TcpServer::onmessage(spConnection conn,std::string &message) //����ͻ��˵������� ��Connection���лص��˺���
{
    if(onmessagecb_)
    {
        onmessagecb_(conn,message); //�ص�EchoServer::HandleMessage()
    }
}

void TcpServer::sendcomplete(spConnection conn) //���ݷ�����ɺ� ��Connection���лص��˺���
{
    if(sendcompletecb_)
    {
        sendcompletecb_(conn); //�ص�EchoServer::HandleSendCompelete()
    }  
}

void TcpServer::epolltimeout(EventLoop *loop) //epoll_wait()��ʱ ��EventLoop���лص��˺���
{
    if(timeoutcb_)
    {
        timeoutcb_(loop); //�ص�EchoServer::HandleTimeOut()
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
void TcpServer::setonmessagecb(std::function<void(spConnection,std::string &message)> fn)
{
    onmessagecb_ = fn;
}
void TcpServer::setsendcompeletecb(std::function<void(spConnection)> fn)
{
    sendcompletecb_ = fn;
}
void TcpServer::settimeoutcb(std::function<void(EventLoop*)> fn)
{
    timeoutcb_ = fn;
} 
void TcpServer::removeconn(int fd) //ɾ��conns_�е�Connection���� ��EventLoop::handletimer()�н��ص��˺���
{
    {
        std::lock_guard<std::mutex> gd(mmutex_);
        conns_.erase(fd); //��map��ɾ��conn
    }
}