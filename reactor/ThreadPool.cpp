#include "ThreadPool.h"
#include <cstddef>
#include <cstdio>
#include <functional>
#include <mutex>
#include <sys/syscall.h>
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadnum,const std::string &threadtype):stop_(false),threadtype_(threadtype) //在构造函数中将启动threadnum个线程
{
    //启动threadnum个线程 每个线程将阻塞在条件变量上
    for(size_t i = 0;i<threadnum;i++)
    {
        //用lambda函数创建线程
        threads_.emplace_back([this]{
            printf("create %s thread(%ld).\n",threadtype_.c_str(),syscall(SYS_gettid)); //显示线程类型和线程ID
            while(stop_ == false)
            {
                std::function<void()> task; //用于存放出队的元素
                {
                    //锁作用域的开始
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    //等待生产者的条件变量
                    this->condition_.wait(lock,[this]{
                       return ((this->stop_==true)||(this->taskqueue_.empty()==false)); 
                    });
                    //在线程池停止之前 如果队列中还有任务 执行完在退出
                    if((this->stop_ == true)&& (this->taskqueue_.empty()==true))
                    {
                        return;
                    }
                    //出队一个任务
                    task = std::move(this->taskqueue_.front());
                    this->taskqueue_.pop();
                }
                task(); //执行任务
            }
        });
    }
}

void ThreadPool::addtask(std::function<void()> task) //把任务添加到队列中
{
    {
        //锁作用域的开始
        std::lock_guard<std::mutex> lock(mutex_);
        taskqueue_.push(task);
    }
    condition_.notify_one(); //唤醒一个线程
}

size_t ThreadPool::size() //获取线程池的大小
{
    return threads_.size();
}

void ThreadPool::stop() //停止线程
{
    if(stop_)
    {
        return;
    }
    stop_ = true;
    condition_.notify_all(); //唤醒所有线程
    //等待全部线程执行完任务后退出
    for(std::thread &th :threads_)
    {
        th.join();
    }
}

ThreadPool::~ThreadPool() //在析构函数中将停止线程
{
    stop();
}