#pragma once
#include"EventLoop.h"
#include"Socket.h"
#include"Channel.h"
#include"Acceptor.h"
#include"Connection.h"
#include"ThreadPool.h"
#include <cstdint>
#include <functional>
#include<map>
#include<mutex>
#include<memory>
#include <vector>

//Tcp���������
class TcpServer
{
private:
    std::unique_ptr<EventLoop> mainloop_; //���¼�ѭ��
    std::vector<std::unique_ptr<EventLoop>> subloops_; //��Ŵ��¼�ѭ��������
    Acceptor acceptor_; //һ��TcpServerֻ��һ��Acceptor����
    int threadnum_;  //�̳߳صĴ�С �����¼�ѭ���ĸ���
    ThreadPool threadpool_; //�̳߳�
    std::mutex mmutex_; //����conns_�Ļ�����
    std::map<int,spConnection> conns_;  //һ��TcpServer�ж��Connection���� �����map������
    std::function<void(spConnection)> newconnectioncb_; //�ص�EchoServer::HandleNewconnection()
    std::function<void(spConnection)> closeconnectioncb_; //�ص�EchoServer::HandleClose()
    std::function<void(spConnection)> errorconnectioncb_; ////�ص�EchoServer::HandleError()
    std::function<void(spConnection,std::string &message)> onmessagecb_; //�ص�EchoServer::HandleMessage()
    std::function<void(spConnection)> sendcompletecb_; //�ص�EchoServer::HandleSendComplete()
    std::function<void(EventLoop*)> timeoutcb_; ////�ص�EchoServer::HandleTimeOut()
public:
    TcpServer(const std::string &ip,const uint16_t port,int threadnum=3);
    ~TcpServer();
    void start();  //�����¼�ѭ��
    void stop(); //ֹͣIO�̺߳��¼�ѭ��
    void newconnection(std::unique_ptr<Socket> clientsock); //�����¿ͻ����������� ��Acceptor���лص��˺���
    void closeconnection(spConnection conn); //�رտͻ��˵����� ��Connection���лص��˺���
    void errorconnection(spConnection conn); //�ͻ��˵����Ӵ��� ��Connection���лص��˺���
    void onmessage(spConnection conn,std::string &message); //����ͻ��˵������� ��Connection���лص��˺���
    void sendcomplete(spConnection conn); //���ݷ�����ɺ� ��Connection���лص��˺���
    void epolltimeout(EventLoop *loop); //epoll_wait()��ʱ ��EventLoop���лص��˺���
    
    void setnewconnenctioncb(std::function<void(spConnection)> fn); 
    void setcloseconnectioncb(std::function<void(spConnection)> fn);
    void seterrorconnectioncb(std::function<void(spConnection)> fn);
    void setonmessagecb(std::function<void(spConnection,std::string &message)> fn);
    void setsendcompeletecb(std::function<void(spConnection)> fn);
    void settimeoutcb(std::function<void(EventLoop*)> fn); 
    void removeconn(int fd); //ɾ��conns_�е�Connection���� ��EventLoop::handletimer()�н��ص��˺���
};