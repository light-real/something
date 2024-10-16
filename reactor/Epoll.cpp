#include "Epoll.h"
#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <strings.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>

Epoll::Epoll()
{
    if ((epollfd_ = epoll_create(1)) == -1) // �ڹ��캯���д���epollfd_  epoll������������
    {
        printf("epoll_create() failed(%d).\n", errno);
        exit(-1);
    }
}

Epoll::~Epoll()
{
    close(epollfd_); // �����������йر�epollfd_
}

void Epoll::updatechannel(Channel *ch) // ��channel���/���µ�������� channel����fd Ҳ�м��ӵ��¼�
{
    epoll_event ev;           // �����¼������ݽṹ
    ev.data.ptr = ch;         // ָ��channel
    ev.events = ch->events(); // ָ���¼�
    if (ch->inpoll())         // ���channel�Ѿ���������
    {
        if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, ch->fd(), &ev) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
    }
    else // ���channel��������
    {
        if ((epoll_ctl(epollfd_, EPOLL_CTL_ADD, ch->fd(), &ev)) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
        ch->setinepoll(true); // ��channel��inepoll_��Ա����Ϊtrue
    }
}

void Epoll::removechannel(Channel *ch) // �Ӻ������ɾ��channel
{
    if (ch->inpoll()) // ���channel�Ѿ���������
    {
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, ch->fd(), 0) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
    }
}

std::vector<Channel *> Epoll::loop(int timeout) // ����epoll_wait() �ȴ��¼��ķ��� �ѷ������¼���vector��������
{
    std::vector<Channel *> channels;                               // ���epoll_wait()���ص��¼�
    bzero(events_, sizeof(events_));                               // �����epoll_wait()�����¼��������ʼ�� ÿһ��ѭ�����ǽ��յ��µ��¼�
    int infds = epoll_wait(epollfd_, events_, MaxEvents, timeout); // �ȴ����ӵ�fd���¼�����

    // ����ʧ��
    if (infds < 0)
    {
        perror("epoll_wait() failed");
        exit(-1);
    }

    // ��ʱ
    if (infds == 0)
    {
        // ���epoll_wait()��ʱ ��ʾϵͳ�ܿ��� ���ص�channels��Ϊ��
        return channels;
    }

    // ���infds>0 ��ʾ���¼�������fd������
    /*
    typedef union epoll_data
    {
        void *ptr;
        int fd;
        uint32_t u32;
        uint64_t u64;
    }   epoll_data_t;

    struct epoll_event
    {
        uint32_t events;	// Epoll events
        epoll_data_t data; // User data variable
        }
    __EPOLL_PACKED;
    */
    // epoll_data��һ��������union ����epoll_data�е�ptr��Ա��void*���ͣ�����ת��Ϊ��������
    for (int i = 0; i < infds; i++)
    {
        Channel *ch = (Channel *)events_[i].data.ptr; // ȡ���ѷ����¼���channel
        ch->setrevents(events_[i].events);            // ����channel��revents_��Ա
        channels.push_back(ch);
    }
    return channels;
}