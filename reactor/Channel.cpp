#include "Channel.h"
#include <sys/epoll.h>

Channel::Channel(EventLoop* loop,int fd):loop_(loop),fd_(fd) //构造函数 Channel是Acceptor和Connnection的下层类
{

}

Channel::~Channel()   //析构函数
{
    //在析构函数中 不要销毁loop_ 也不能关闭fd_ 因为这两个东西不属于Channel类 Channel类只是需要他们 使用他们而已
}

int Channel::fd()  //返回fd_成员
{
    return fd_;
}

void Channel::useet()  //采用边缘触发
{
    events_ = events_|EPOLLET;
}

void Channel::enablereading()  //让epoll_wait()监视fd_的读事件 注册读事件
{
    events_|=EPOLLIN;
    loop_->updatechannel(this);
}

void Channel::disablereading()  //取消读事件
{
    events_&=~EPOLLIN;
}

void Channel::enablewriting()  //注册写事件
{
    events_ |= EPOLLOUT;
}

void Channel::disablewriting() //取消写事件
{
    events_ &= ~EPOLLOUT;
    loop_->updatechannel(this);
}

void Channel::disableall()  //取消全部事件
{
    events_ = 0;
    loop_->updatechannel(this);
}

void Channel::remove()   //从事件循环中删除Channel
{
    disableall(); //先取消全部事件
    loop_->removechannel(this); //从红黑树上删除fd
}

void Channel::setinepoll(bool inepoll) //设置inepoll_成员的值
{
    inepoll_ = inepoll;
}

void Channel::setrevents(uint32_t ev) //设置revents_成员的值为参数ev
{
    revents_ = ev;
}

bool Channel::inpoll()  //返回inepoll_成员的值
{
    return inepoll_;
}

uint32_t Channel::events() //返回events_成员的值
{
    return events_;
}

uint32_t Channel::revents() //返回revents_成员的值
{
    return revents_;
}

void Channel::handleevent() //事件处理函数 epoll_wait()返回的时候 执行它
{
    if(revents_&EPOLLRDHUP) //对方已关闭 有些系统监测不到 可以使用EPOLLIN recv()返回0
    {
        closecallback_();  //回调Connnection::closecallback();
    }
    else if(revents_&(EPOLLIN|EPOLLPRI)) //接收缓冲区中有数据可以读
    {
        //fd_读事件的回调函数 如果是acceptchannel 将回调Acceptor::newconnection() 
        //如果是clientchannel 将回调Connection::onmessage()
        readcallback_();
    }
    else if(revents_ &EPOLLOUT) //有数据需要写
    { 
        writecallback_(); //回调Connnection::writecallback()
    }
    else // 其他事件 都视为错误
    {
        errorcallback_(); //回调Connenction::errorcallback()
    }
}

void Channel::setreadcallback(std::function<void()> fn)  //设置fd_读事件的回调函数
{
    readcallback_ = fn;
}

void Channel::setwritecallback(std::function<void()> fn) //设置fd_写事件的回调函数
{
    writecallback_ = fn;
}

void Channel::setclosecallback(std::function<void()> fn) //设置关闭fd_事件的回调函数
{
    closecallback_ = fn;
}

void Channel::seterrorcallback(std::function<void()> fn) //设置fd_发生了错误的回调函数
{
    errorcallback_ = fn;
}