#include "Socket.h"
#include "InetAddress.h"
#include <asm-generic/socket.h>
#include <cerrno>
#include <cstdint>
#include <cstdio>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

// 创建一个非阻塞的socket
int createnonblocking()
{
    int listenfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, IPPROTO_TCP);
    if (listenfd < 0)
    {
        printf("%s:%s:%d listen socket create error:%d\n", __FILE__, __FUNCTION__, __LINE__, errno);
        exit(-1);
    }
    return listenfd;
}

// 构造函数 传入一个已经准备好的fd
Socket::Socket(int fd) : fd_(fd)
{
}

// 在析构函数中 将fd_关闭
Socket::~Socket()
{
    ::close(fd_);
}

int Socket::fd() const
{
    return fd_;
}

std::string Socket::ip() const
{
    return ip_;
}

uint16_t Socket::port() const
{
    return port_;
}

void Socket::setreuseaddr(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
}

void Socket::setreuseport(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));
}

void Socket::settcpnodelay(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));
}

void Socket::setkeepalive(bool on)
{
    int optval = on ? 1 : 0;
    ::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));
}

void Socket::bind(const InetAddress &servaddr)
{
    if (::bind(fd_, servaddr.addr(), sizeof(servaddr)) < 0)
    {
        perror("bind() failed");
        close(fd_);
        exit(-1);
    }
    setipport(servaddr.ip(), servaddr.port());
}

// 设置ip_和port_成员
void Socket::setipport(const std::string &ip, uint16_t port)
{
    ip_ = ip;
    port_ = port;
}

void Socket::listen(int nn)
{
    if (::listen(fd_, nn) != 0)
    {
        perror("listen() failed");
        close(fd_);
        exit(-1);
    }
}

int Socket::accept(InetAddress &clientaddr) // 这里表示拷贝 会改变传过来的clientaddr
{
    sockaddr_in peeraddr;
    socklen_t len = sizeof(peeraddr);
    int clientfd = accept4(fd_, (sockaddr *)&peeraddr, &len, SOCK_NONBLOCK);
    clientaddr.setaddr(peeraddr); // 客户端的地址和协议
    return clientfd;
}