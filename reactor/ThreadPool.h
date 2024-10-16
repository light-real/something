#pragma once
#include <cstddef>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <sys/syscall.h>
#include <mutex>
#include <unistd.h>
#include <thread>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool
{
private:
    std::queue<std::function<void()>> taskqueue_; // �������
    std::vector<std::thread> threads_;            // �̳߳��е��߳�
    std::mutex mutex_;                            // �������ͬ���Ļ�����
    std::condition_variable condition_;           // �������ͬ������������
    std::atomic_bool stop_;                       // ������������ ��stop_��ֵ����Ϊtrue ȫ�����߳̽��˳�
    const std::string threadtype_;                // �߳����� "IO" "WORKS"
public:
    ThreadPool(size_t threadnum, const std::string &threadtype); // �ڹ��캯���н�����threadnum���߳�
    void addtask(std::function<void()> task);                    // ��������ӵ�������
    size_t size();                                               // ��ȡ�̳߳صĴ�С
    void stop();                                                 // ֹͣ�߳�
    ~ThreadPool();                                               // �����������н�ֹͣ�߳�
};