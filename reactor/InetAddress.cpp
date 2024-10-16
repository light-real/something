#include "InetAddress.h"
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>

InetAddress::InetAddress()
{
}

InetAddress::InetAddress(const std::string &ip, uint16_t port) // 监听的fd构造函数
{
    addr_.sin_family = AF_INET;                    // IPv4网络协议的套接字类型
    addr_.sin_addr.s_addr = inet_addr(ip.c_str()); // 服务端用于监听的ip地址
    addr_.sin_port = htons(port);                  // 服务端用于监听的端口
}

InetAddress::InetAddress(const sockaddr_in addr) : addr_(addr) // 客户端连上来的fd构造函数
{
}

InetAddress::~InetAddress()
{
}

const char *InetAddress::ip() const // 返回字符串表示的地址
{
    // 将一个ipv4地址解析成"X.X.X.X"这样的字符串
    return inet_ntoa(addr_.sin_addr); // 将网络字节序转换为字符串的形式 网络字节序通常是大端模式 big-endian
}

uint16_t InetAddress::port() const // 返回整数表示的端口
{
    return ntohs(addr_.sin_port);
}

const sockaddr *InetAddress::addr() const // 返回addr_成员的地址 转换成了sockaddr
{
    return (sockaddr *)&addr_;
}

void InetAddress::setaddr(sockaddr_in clientaddr) // 设置addr成员的值
{
    addr_ = clientaddr;
}