#include <iostream>
#include <thread>

// ������ʾ
// ��ǰ�̵߳ĺ����Ѿ����أ����߳�ȴ���ܷ��ʾֲ�����

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
            do_something(i); // ������ܷ�����������
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
    my_thread.detach(); //���ȴ����߳̽���
    //���߳̿��ܻ������У������̵߳ĺ����ѽ���
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