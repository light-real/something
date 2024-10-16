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
    if ((epollfd_ = epoll_create(1)) == -1) // 在构造函数中创建epollfd_  epoll句柄（红黑树）
    {
        printf("epoll_create() failed(%d).\n", errno);
        exit(-1);
    }
}

Epoll::~Epoll()
{
    close(epollfd_); // 在析构函数中关闭epollfd_
}

void Epoll::updatechannel(Channel *ch) // 把channel添加/更新到红黑树上 channel中有fd 也有监视的事件
{
    epoll_event ev;           // 声明事件的数据结构
    ev.data.ptr = ch;         // 指定channel
    ev.events = ch->events(); // 指定事件
    if (ch->inpoll())         // 如果channel已经在树上了
    {
        if (epoll_ctl(epollfd_, EPOLL_CTL_MOD, ch->fd(), &ev) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
    }
    else // 如果channel不在树上
    {
        if ((epoll_ctl(epollfd_, EPOLL_CTL_ADD, ch->fd(), &ev)) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
        ch->setinepoll(true); // 把channel的inepoll_成员设置为true
    }
}

void Epoll::removechannel(Channel *ch) // 从红黑树上删除channel
{
    if (ch->inpoll()) // 如果channel已经在树上了
    {
        if (epoll_ctl(epollfd_, EPOLL_CTL_DEL, ch->fd(), 0) == -1)
        {
            perror("epoll_ctl() failed.\n");
            exit(-1);
        }
    }
}

std::vector<Channel *> Epoll::loop(int timeout) // 运行epoll_wait() 等待事件的发生 已发生的事件用vector容器返回
{
    std::vector<Channel *> channels;                               // 存放epoll_wait()返回的事件
    bzero(events_, sizeof(events_));                               // 将存放epoll_wait()返回事件的数组初始化 每一次循环都是接收的新的事件
    int infds = epoll_wait(epollfd_, events_, MaxEvents, timeout); // 等待监视的fd有事件发生

    // 返回失败
    if (infds < 0)
    {
        perror("epoll_wait() failed");
        exit(-1);
    }

    // 超时
    if (infds == 0)
    {
        // 如果epoll_wait()超时 表示系统很空闲 返回的channels将为空
        return channels;
    }

    // 如果infds>0 表示有事件发生的fd的数量
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
    // epoll_data是一个联合体union 其中epoll_data中的ptr成员是void*类型，可以转换为其他类型
    for (int i = 0; i < infds; i++)
    {
        Channel *ch = (Channel *)events_[i].data.ptr; // 取出已发生事件的channel
        ch->setrevents(events_[i].events);            // 设置channel的revents_成员
        channels.push_back(ch);
    }
    return channels;
}