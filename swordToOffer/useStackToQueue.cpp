#include "head.hpp"

using namespace std;

// 使用两个栈实现队列

class MyQueue
{
public:
    int pop()
    {
        if (!s2.empty())
        {
        }
        else
        {
            while (!s1.empty())
            {
                int temp = s1.top();
                s1.pop();
                s2.push(temp);
            }
        }
        int result = s2.top();
        s2.pop();
        std::cout << "result = " << result << endl;
        return result;
    }

    void push(int val)
    {
        s1.push(val);
    }
    int size()
    {
        return s1.size() + s2.size();
    }

private:
    std::stack<int> s1;
    std::stack<int> s2;
};

int main()
{
    MyQueue *mq = new MyQueue();
    mq->push(1);
    mq->push(2);
    mq->push(3);
    mq->pop();
    mq->pop();
    mq->pop();
    return 0;
}