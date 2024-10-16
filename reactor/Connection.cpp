#include "Connection.h"
#include "Epoll.h"
#include <cerrno>
#include <cstdio>
#include <functional>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>

/*
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
*/

Connection::Connection(EventLoop *loop,std::unique_ptr<Socket> clientsock)
           :loop_(loop),clientsock_(std::move(clientsock)),disconnect_(false),
            clientchannel_(new Channel(loop_,clientsock_->fd()))
{
    //Ϊ�¿ͻ�������׼�����¼� ����ӵ�epoll��
    clientchannel_->setreadcallback(std::bind(&Connection::onmessage,this));
    clientchannel_->setclosecallback(std::bind(&Connection::closecallback,this));
    clientchannel_->seterrorcallback(std::bind(&Connection::errorcallback,this));
    clientchannel_->setwritecallback(std::bind(&Connection::writecallback,this));
    clientchannel_->useet(); //�ͻ�����������fd���ñ�Ե����
    clientchannel_->enablereading(); //��epoll_wait()����clientchannel�Ķ��¼�
}

Connection::~Connection()
{
    
}

int Connection::fd() const //���ؿͻ��˵�fd
{
    return clientsock_->fd();
}

std::string Connection::ip() const //���ؿͻ��˵�ip
{
    return clientsock_->ip();
}

uint16_t Connection::port() const //���ؿͻ��˵�port
{
    return clientsock_->port();
}

void Connection::onmessage() //����Զ˷��͹�������Ϣ
{
    char buffer[1024];
    while (true)  //����ʹ�÷�����IO һ�ζ�ȡbuffer��С���� ֱ��ȫ�������ݶ�ȡ���
    {
        bzero(&buffer, sizeof(buffer));
        ssize_t nread = read(fd(),buffer,sizeof(buffer));
        if(nread > 0)  //����ɹ���ȡ��������
        {
            inputbuffer_.append(buffer,nread); //�Ѷ�ȡ������׷�ӵ����ջ�������
        }
        else if(nread == -1 && errno == EINTR) //��ȡ���ݵ�ʱ���ź��ж� ������ȡ
        {
            continue;
        }
        else if(nread == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK))) //ȫ�������Ѷ�ȡ���
        {
            std::string message;
            while(true) //�ӽ��ջ������з����ͻ��˵�������Ϣ
            {
                if(inputbuffer_.pickmessage(message) == false) break;
                lastatime_ = Timestamp::now();  //����Connenction��ʱ���
                onmessagecallback_(shared_from_this(),message); //�ص�TcpServer::onmessage()����ͻ��˵�������Ϣ
            }
            break;
        }
        else if(nread == 0) //�ͻ��˵������ѶϿ�
        {
            closecallback(); //�ص�TcpServer::closecallback()
            break;
        }
    }
}

void Connection::closecallback() //Tcp���ӹرյĻص����� ��Channel�ص�
{
    disconnect_ = true;
    clientchannel_->remove();  //���¼�ѭ����ɾ��Channel
    closecallback_(shared_from_this()); //�ص�TcpServer::errorconnection
}

void Connection::errorcallback() //Tcp���Ӵ���Ļص����� ��Channel�ص�
{
    disconnect_ = true;
    clientchannel_->remove();  //���¼�ѭ����ɾ��Channel
    closecallback_(shared_from_this()); //�ص�TcpServer::errorconnection
}

void Connection::writecallback() //����д�¼��Ļص����� ��Channel�ص�
{
    int writen = ::send(fd(), outputbuffer_.data(), outputbuffer_.size(), 0); //���԰�outputbuffer_�е�����ȫ�����ͳ�ȥ
    if(writen > 0)
    {
        outputbuffer_.erase(0,writen); //��outputbuffer_��ɾ���ѷ��ͳɹ����ֽ���
    }
    //������ͻ�������û�������� ��ʾ�����ѷ������ ���ٹ�עд�¼�
    if(outputbuffer_.size()==0)
    {
        clientchannel_->disablewriting();
        sendcompletecallback_(shared_from_this());
    }
}

void Connection::setclosecallback(std::function<void(spConnection)> fn) //���ùر�fd_�Ļص�����
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

void Connection::send(const char *data,size_t size) //�������� �������κ��߳��� ���ǵ��ô˺�����������
{
    if(disconnect_ == true)
    {
        printf("�ͻ��������ѶϿ���,send()ֱ�ӷ���.\n");
        return;
    }
    if(loop_->isinloopthread()) //�жϵ�ǰ�߳��Ƿ�Ϊ�¼�ѭ���߳� ��IO�߳�
    {
        //�����ǰ�߳���IO�߳� ֱ�ӵ���sendinloop()��������
        sendinloop(data, size);
    }
    else
    {
        //�����ǰ�̲߳���IO�߳� ����Eventloop::queueinloop() ��sendinloop()�����¼�ѭ���߳�ȥִ��
        loop_->queueinloop(std::bind(&Connection::sendinloop,this,data,size));
    }
}

void Connection::sendinloop(const char *data,size_t size) //�������� �����ǰ�߳�ʱIO�߳� ֱ�ӵ��ô˺��� ���ʱ�����߳� ���˺�������IO�߳�ȥִ��
{
    outputbuffer_.appendwithsep(data,size); //����Ҫ���͵����ݱ��浽Connection�ķ��ͻ�����
    clientchannel_->enablewriting(); //ע��д�¼�
}

bool Connection::timeout(time_t now,int val) //�ж�TCP�����Ƿ�ʱ(����̫��)
{
    return now-lastatime_.toint() > val;
}