#include <iostream>
#include <future>
#include <chrono>
#include <thread>

void asyncTask()
{
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::cout << "Task Compeleted" << std::endl;
}

int main()
{
    std::cout << "Task begin" << std::endl;
    auto future = std::async(std::launch::async, asyncTask);
    // std::this_thread::sleep_for(std::chrono::seconds(3));
    std::cout << "Task Start,continue" << std::endl;
    future.get(); // 等待任务完成并获取结果
    std::cout << "Task finish" << std::endl;
    return 0;
}