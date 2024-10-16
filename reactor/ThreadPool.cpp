#include "ThreadPool.h"
#include <cstddef>
#include <cstdio>
#include <functional>
#include <mutex>
#include <sys/syscall.h>
#include <unistd.h>

ThreadPool::ThreadPool(size_t threadnum,const std::string &threadtype):stop_(false),threadtype_(threadtype) //�ڹ��캯���н�����threadnum���߳�
{
    //����threadnum���߳� ÿ���߳̽�����������������
    for(size_t i = 0;i<threadnum;i++)
    {
        //��lambda���������߳�
        threads_.emplace_back([this]{
            printf("create %s thread(%ld).\n",threadtype_.c_str(),syscall(SYS_gettid)); //��ʾ�߳����ͺ��߳�ID
            while(stop_ == false)
            {
                std::function<void()> task; //���ڴ�ų��ӵ�Ԫ��
                {
                    //��������Ŀ�ʼ
                    std::unique_lock<std::mutex> lock(this->mutex_);
                    //�ȴ������ߵ���������
                    this->condition_.wait(lock,[this]{
                       return ((this->stop_==true)||(this->taskqueue_.empty()==false)); 
                    });
                    //���̳߳�ֹ֮ͣǰ ��������л������� ִ�������˳�
                    if((this->stop_ == true)&& (this->taskqueue_.empty()==true))
                    {
                        return;
                    }
                    //����һ������
                    task = std::move(this->taskqueue_.front());
                    this->taskqueue_.pop();
                }
                task(); //ִ������
            }
        });
    }
}

void ThreadPool::addtask(std::function<void()> task) //��������ӵ�������
{
    {
        //��������Ŀ�ʼ
        std::lock_guard<std::mutex> lock(mutex_);
        taskqueue_.push(task);
    }
    condition_.notify_one(); //����һ���߳�
}

size_t ThreadPool::size() //��ȡ�̳߳صĴ�С
{
    return threads_.size();
}

void ThreadPool::stop() //ֹͣ�߳�
{
    if(stop_)
    {
        return;
    }
    stop_ = true;
    condition_.notify_all(); //���������߳�
    //�ȴ�ȫ���߳�ִ����������˳�
    for(std::thread &th :threads_)
    {
        th.join();
    }
}

ThreadPool::~ThreadPool() //�����������н�ֹͣ�߳�
{
    stop();
}