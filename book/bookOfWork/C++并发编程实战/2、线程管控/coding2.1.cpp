#include <iostream>
#include <thread>

// 用于演示
// 当前线程的函数已经返回，新线程却仍能访问局部变量

static void do_something(int i)
{
    // std::cout<<"i = "<<i<<" ";
    return ;
}

class func
{
public:
    func(int &i_) : i(i_) {}

    void operator()()
    {
        for (unsigned j = 0; j < 1000; j++)
        {
            do_something(i); // 这里可能访问悬空引用
        }
    }

private:
    int &i;
};

void oops()
{
    int some_local_state = 0;
    func my_func(some_local_state);
    std::thread my_thread(my_func);
    my_thread.detach(); //不等待新线程结束
    //新线程可能还在运行，而主线程的函数已结束
}

int main()
{
    std::thread t(oops);
    t.detach();
    int sum = 0;
    for(int i = 0;i<1000000;i++)
    {
        sum++;
    }
    return 0;
}