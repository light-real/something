#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <strings.h>
#include <string.h>
#include <sys/epoll.h>
#include <vector>
#include <unistd.h>
#include "Channel.h"

class Channel;

// Epoll��
class Epoll
{
private:
    static const int MaxEvents = 100; // epoll_wait()�����¼�����Ĵ�С
    int epollfd_ = -1;                // epoll��� �ڹ��캯���д���
    epoll_event events_[MaxEvents];   // ���epoll_wait()�����¼������� �ڹ��캯���з����ڴ�

public:
    Epoll();                                       // �ڹ��캯���д�����epollfd_
    ~Epoll();                                      // �����������йر�epollfd_
    void updatechannel(Channel *ch);               // ��channel���/���µ�������� channel����fd Ҳ�м��ӵ��¼�
    void removechannel(Channel *ch);               // �Ӻ������ɾ��channel
    std::vector<Channel *> loop(int timeout = -1); // ����epoll_wait() �ȴ��¼��ķ��� �ѷ������¼���vector��������
};