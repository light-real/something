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

void EchoServer::Start() //��������
{
    tcpserver_.start();
}

void EchoServer::Stop() //��ֹ����
{
    //ֹͣ�����߳�
    threadpool_.stop();
    printf("WORK thread has stop\n");
    //ֹͣIO�߳�(�¼�ѭ��)
    tcpserver_.stop();
}

void EchoServer::HandleNewConnection(spConnection conn) //�����¿ͻ��˵��������� ��TcpServer���лص��˺���
{
    printf("%s new connection(fd=%d,ip=%s,port=%d)ok.\n",
    Timestamp::now().tostring().c_str(),conn->fd(),conn->ip().c_str(),conn->port());
    //���������Ĵ���
}

void EchoServer::HandleClose(spConnection conn) //�رտͻ��˵����� ��TcpServer���лص��˺���
{
    printf("%s new connection closed(fd=%d,ip=%s,port=%d)ok.\n",
    Timestamp::now().tostring().c_str(),conn->fd(),conn->ip().c_str(),conn->port());    
}

void EchoServer::HandleError(spConnection conn) //�ͻ��˵����Ӵ��� ��TcpServer���лص��˺���
{
    
}

void EchoServer::HandleMessage(spConnection conn,std::string&message) //����ͻ��˵������� ��TcpServer���лص��˺���
{
    if(threadpool_.size()==0)
    {
        //���û�й����߳� ��ʾ��IO�߳��м���
        OnMessage(conn, message);
    }
    else
    {
        //��ҵ����ӵ��̳߳ص���������� ���������߳�ȥ����ҵ��
        threadpool_.addtask(std::bind(&EchoServer::OnMessage,this,conn,message));
    }
}

void EchoServer::HandleSendCompelete(spConnection conn) //���ݷ�����ɺ� ��TcpServer���лص��˺���
{
    
}

void EchoServer::OnMessage(spConnection conn,std::string& message) //����ͻ��˵������� ������Ӹ��̳߳� 
{
    message = "reply" +message; //����ҵ��
    conn->send(message.data(), message.size());
}