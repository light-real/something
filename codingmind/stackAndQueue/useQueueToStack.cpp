#include "head.hpp"

/*
使用队列实现栈
push(x) -- 元素 x 入栈
pop() -- 移除栈顶元素
top() -- 获取栈顶元素
empty() -- 返回栈是否为空
*/

class MyStack
{
public:
    MyStack()
    {
    }

    ~MyStack()
    {
    }

    void push(int x)
    {
        if (mQue1_.empty())
        {
            mQue2_.push(x);
        }
        else
        {
            mQue1_.push(x);
        }
    }

    int pop() // 移除栈顶元素
    {
        int temp = -1;
        if (mQue1_.empty())
        {
            while (!mQue2_.empty())
            {
                temp = mQue2_.front();
                mQue2_.pop();
                if (mQue2_.empty())
                {
                    std::cout<<temp<<std::endl;
                    return temp;
                }
                mQue1_.push(temp);
            }
        }
        else
        {
            while (!mQue1_.empty())
            {
                temp = mQue1_.front();
                mQue1_.pop();
                if (mQue1_.empty())
                {
                    std::cout<<temp<<std::endl;
                    return temp;
                }
                mQue2_.push(temp);
            }
        }
        return -1;
    }

    int top()
    {
        int ans = pop();
        if(mQue1_.empty())
        {
            mQue2_.push(ans);
        }
        else
        {
            mQue1_.push(ans);
        }
        return ans;
    }

    bool empty()
    {
        return mQue1_.empty() && mQue2_.empty();
    }

private:
    std::queue<int> mQue1_;
    std::queue<int> mQue2_;
};

int main()
{
    MyStack sta;
    sta.push(1);
    sta.push(2);
    sta.push(3);
    sta.push(4);
    sta.push(5);

    sta.pop();
    sta.pop();
    std::cout<<"-----------"<<std::endl;
    sta.top();
    std::cout<<"-----------"<<std::endl;
    sta.pop();
    sta.pop();
    sta.pop();
    
    
    std::cout<<"-----------"<<std::endl;
    std::cout<<sta.empty()<<std::endl;
    return 0;
}