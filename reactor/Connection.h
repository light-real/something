#pragma once
#include <cstddef>
#include <cstdint>
#include <ctime>
#include <functional>
#include "Socket.h"
#include "InetAddress.h"
#include "Channel.h"
#include "EventLoop.h"
#include "Buffer.h"
#include "Timestamp.h"
#include <memory>
#include <atomic>
#include <sys/syscall.h>

class EventLoop;
class Channel;
class Connection;
using spConnection = std::shared_ptr<Connection>;

class Connection : public std::enable_shared_from_this<Connection>
{
private:
    EventLoop *loop_;                                                    // Connection对应事件的循环 在构造函数中传入
    std::unique_ptr<Socket> clientsock_;                                 // 与客户端通讯的Socket
    std::unique_ptr<Channel> clientchannel_;                             // Connection对应的channel 在构造函数中创建
    Buffer inputbuffer_;                                                 // 接收缓冲区
    Buffer outputbuffer_;                                                // 发送缓冲区
    std::atomic_bool disconnect_;                                        // 客户端连接是否已断开 如果已断开 设置为true
    std::function<void(spConnection)> closecallback_;                    // 关闭fd_的回调函数 将回调TcpServer::closeconnection()
    std::function<void(spConnection)> errorcallback_;                    // fd_发生错误的回调函数 将回调TcpServer::errorconnection()
    std::function<void(spConnection, std::string &)> onmessagecallback_; // 处理报文的回调函数 将回调TcpServer::onmessage()
    std::function<void(spConnection)> sendcompletecallback_;             // 发送数据完成的回调函数 将回调TcpServer::sendcomplete()
    Timestamp lastatime_;                                                // 时间戳 创建Connection对象时为当前时间 每接收一个报文 把时间戳更新为当前时间
public:
    Connection(EventLoop *loop, std::unique_ptr<Socket> clientsock);
    ~Connection();
    int fd() const;                                              // 返回客户端的fd
    std::string ip() const;                                      // 返回客户端的ip
    uint16_t port() const;                                       // 返回客户端的port
    void onmessage();                                            // 处理对端发送过来的信息
    void closecallback();                                        // Tcp连接关闭的回调函数 供Channel回调
    void errorcallback();                                        // Tcp连接错误的回调函数 供Channel回调
    void writecallback();                                        // 处理写事件的回调函数 供Channel回调
    void setclosecallback(std::function<void(spConnection)> fn); // 设置关闭fd_的回到函数
    void seterrorcallback(std::function<void(spConnection)> fn);
    void setonmessagecallback(std::function<void(spConnection, std::string &)> fn);
    void setsendcompletecallback(std::function<void(spConnection)> fn);
    void send(const char *data, size_t size);       // 发送数据 不管在任何线程中 都是调用此函数发送数据
    void sendinloop(const char *data, size_t size); // 发送数据 如果当前线程时IO线程 直接调用此函数 如果时工作线程 将此函数传给IO线程去执行
    bool timeout(time_t now, int val);              // 判断TCP连接是否超时(空闲太久)
};