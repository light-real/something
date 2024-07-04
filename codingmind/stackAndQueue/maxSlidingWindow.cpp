#include "head.hpp"

/*
自定义一个双端队列
push(value)
    如果vaulea值大于队列的入口元素 那么弹出入口元素 直至value小于队头元素

pop(value)
    如果value == 队列.front() 那么弹出队头元素 否则什么也不做

front()
    返回队头元素 即当前窗口的最大值
*/

class MyDeque
{
public:
    MyDeque()
    {
    }

    ~MyDeque()
    {
    }

    void push(int value)
    {
        while (!due.empty() && value > due.back())
        {
            due.pop_back();
        }
        due.push_back(value);
    }

    void pop(int value)
    {
        if (!due.empty() && value == due.front())
        {
            due.pop_front();
        }
    }

    int front()
    {
        return due.front();
    }

private:
    std::deque<int> due;
};

std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k)
{
    MyDeque md;
    std::vector<int> result;
    for (int i = 0; i < k; i++)
    {
        md.push(nums[i]);
    }
    result.push_back(md.front());
    for(int i = k;i<nums.size();i++)
    {
        md.pop(nums[i-k]);
        md.push(nums[i]);
        result.push_back(md.front());
    }
    printVec(result);
    return result;
}

int main()
{
    std::vector<int> vec = {1, 3, -1, -3, 5, 3, 6, 7};
    printVec(vec);
    std::cout << "-------" << std::endl;
    int k = 3;
    maxSlidingWindow(vec, k);
    return 0;
}