#include "InetAddress.h"
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <sys/socket.h>

InetAddress::InetAddress()
{
}

InetAddress::InetAddress(const std::string &ip, uint16_t port) // ������fd���캯��
{
    addr_.sin_family = AF_INET;                    // IPv4����Э����׽�������
    addr_.sin_addr.s_addr = inet_addr(ip.c_str()); // ��������ڼ�����ip��ַ
    addr_.sin_port = htons(port);                  // ��������ڼ����Ķ˿�
}

InetAddress::InetAddress(const sockaddr_in addr) : addr_(addr) // �ͻ�����������fd���캯��
{
}

InetAddress::~InetAddress()
{
}

const char *InetAddress::ip() const // �����ַ�����ʾ�ĵ�ַ
{
    // ��һ��ipv4��ַ������"X.X.X.X"�������ַ���
    return inet_ntoa(addr_.sin_addr); // �������ֽ���ת��Ϊ�ַ�������ʽ �����ֽ���ͨ���Ǵ��ģʽ big-endian
}

uint16_t InetAddress::port() const // ����������ʾ�Ķ˿�
{
    return ntohs(addr_.sin_port);
}

const sockaddr *InetAddress::addr() const // ����addr_��Ա�ĵ�ַ ת������sockaddr
{
    return (sockaddr *)&addr_;
}

void InetAddress::setaddr(sockaddr_in clientaddr) // ����addr��Ա��ֵ
{
    addr_ = clientaddr;
}