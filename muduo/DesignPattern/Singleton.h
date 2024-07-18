/*
����ģʽ����֤һ����ֻ��һ��ʵ�������ṩһ�����ʸ�ʵ����ȫ�ֽڵ�

����ģʽ�����ڳ�����κεط������ض����������Ա�����ʵ�������������븲��

������ʵ��:
    1����Ĭ�Ϲ��캯����Ϊ˽�У���ֹ��������ʹ�õ������new�����
    2���½�һ����̬����������Ϊ���캯�����ú��������˽�й��캯�����������󣬲����䱣����һ����̬��Ա������
       �˺����ж��ڸú����ĵ��ö���������һ�������
*/

// �̰߳�ȫ����������ģʽ
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
