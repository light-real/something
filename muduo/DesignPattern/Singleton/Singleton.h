/*
单例模式：保证一个类只有一个实例，并提供一个访问该实例的全局节点

单例模式允许在程序的任何地方访问特定对象，它可以保护该实例不被其他代码覆盖

单例的实现:
    1、将默认构造函数设为私有，防止其他对象使用单例类的new运算符
    2、新建一个静态构建方法作为构造函数，该函数会调用私有构造函数来创建对象，并将其保存在一个静态成员变量中
       此后所有对于该函数的调用都将返回这一缓存对象
*/

// 线程安全的懒汉单例模式
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <string>
#include <mutex>
#include <thread>

class Singleton
{
public:
    static Singleton *GetInstance()
    {
        if (instance_ == nullptr)
        {
            std::lock_guard<std::mutex> lock(m_mutex_);
            instance_ = new Singleton();
        }
        return instance_;
    }

private:
    Singleton() {}
    static Singleton *instance_;
    static std::mutex m_mutex_;
};

#endif
