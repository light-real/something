#pragma once
#include <arpa/inet.h>
#include <cstdint>
#include <netinet/in.h>
#include <string>

// socket�ĵ�ַЭ����
class InetAddress
{
private:
    sockaddr_in addr_; // ��ʾ��ַЭ��Ľṹ��
public:
    InetAddress();
    InetAddress(const std::string &ip, uint16_t port); // ����Ǽ�����fd ��������캯��
    InetAddress(const sockaddr_in addr);               // ����ǿͻ�����������fd ��������캯��
    ~InetAddress();

    const char *ip() const;               // �����ַ�����ʾ�ĵ�ַ ����192.168.150.128
    uint16_t port() const;                // ����������ʾ�Ķ˿� ����80 8080
    const sockaddr *addr() const;         // ����addr_��Ա�ĵ�ַ ת������sockaddr
    void setaddr(sockaddr_in clientaddr); // ����addr_��Ա��ֵ
};