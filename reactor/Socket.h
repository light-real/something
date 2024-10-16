#pragma once
#include <cstdint>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "InetAddress.h"

// ����һ����������socket
int createnonblocking();

// socket��
class Socket
{
private:
    const int fd_;   // socket���е�fd �ڹ��캯���д�����
    std::string ip_; // �����listenfd ��ŷ���˼�����ip  ����ǿͻ������ӵ�fd ��ŶԶ˵�ip
    uint16_t port_;  // �����listenfd ��ŷ���˼�����port ����ǿͻ������ӵ�fd ����ⲿ�˿�

public:
    Socket(int fd);                                       // ���캯�� ����һ���Ѿ�׼���õ�fd
    ~Socket();                                            // ������������ ��fd_�ر�
    int fd() const;                                       // ����fd_��Ա
    std::string ip() const;                               // ����ip_��Ա
    uint16_t port() const;                                // ����port_��Ա
    void setipport(const std::string &ip, uint16_t port); // ����ip_��port_��Ա

    void setreuseaddr(bool on);  // ����SO_REUSEADDRѡ�� true-�� false-�ر�
    void setreuseport(bool on);  // ����SO_REUSEPORTѡ��
    void settcpnodelay(bool on); // ����TCL_NODELAYѡ��
    void setkeepalive(bool on);  // ����SO_KEEPALIVEѡ��

    void bind(const InetAddress &servaddr); // ����˵�socket�����ô˺���
    void listen(int nn = 128);              // ����˵�socket�����ô˺���
    int accept(InetAddress &clientaddr);    // ����˵�socket�����ô˺���
};