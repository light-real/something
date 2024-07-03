// 使用栈实现队列
/*
push(x) -- 将一个元素放入队列的尾部。
pop() -- 从队列首部移除元素。
peek() -- 返回队列首部的元素。
empty() -- 返回队列是否为空。
*/
#include "head.hpp"

class MyQueue
{
public:
    MyQueue()
    {
    
    }
    ~MyQueue()
    {
        
    }
    
    void push(int x) //将x放入队列的尾部
    {
        mSta1_.push(x);
    }
    
    int pop()
    {
        if(empty())
        {
            return -1;
        }
        if(mSta2_.empty())
        {
            while(!mSta1_.empty())
            {
                int x = mSta1_.top();
                mSta1_.pop();
                mSta2_.push(x);
            }
        }
        int ret = mSta2_.top();
        mSta2_.pop();
        return ret;
    }
    
    int peek()
    {
        int ret = pop();
        return ret;
    }

    bool empty()
    {
        return mSta1_.empty() && mSta2_.empty();
    }

private:
    std::stack<int> mSta1_;
    std::stack<int> mSta2_;
};

int main()
{
    MyQueue mq;
    mq.push(1);
    mq.push(2);
    mq.push(3);
    mq.push(4);
    mq.push(5);
    std::cout<<mq.pop()<<std::endl;
    std::cout<<mq.pop()<<std::endl;
    std::cout<<mq.pop()<<std::endl;
    std::cout<<mq.empty()<<std::endl;
    std::cout<<mq.pop()<<std::endl;
    std::cout<<mq.pop()<<std::endl;
}