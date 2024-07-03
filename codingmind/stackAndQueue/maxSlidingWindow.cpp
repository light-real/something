#include "head.hpp"

/*
����һ���������� nums����һ����СΪ k �Ļ������ڴ������������ƶ�����������Ҳࡣ
��ֻ���Կ����ڻ��������ڵ� k �����֡���������ÿ��ֻ�����ƶ�һλ��
���� ���������е����ֵ ��

ʾ�� 1��
���룺nums = [1,3,-1,-3,5,3,6,7], k = 3
�����[3,3,5,5,6,7]
*/

class MyQueue
{ // �������У��Ӵ�С��
public:
    std::deque<int> que; // ʹ��deque��ʵ�ֵ�������
    // ÿ�ε�����ʱ�򣬱Ƚϵ�ǰҪ��������ֵ�Ƿ���ڶ��г���Ԫ�ص���ֵ���������򵯳���
    // ͬʱpop֮ǰ�ж϶��е�ǰ�Ƿ�Ϊ�ա�
    void pop(int value)
    {
        if (!que.empty() && value == que.front())
        {
            que.pop_front();
        }
    }
    // ���push����ֵ�������Ԫ�ص���ֵ����ô�ͽ����к�˵���ֵ������ֱ��push����ֵС�ڵ��ڶ������Ԫ�ص���ֵΪֹ��
    // �����ͱ����˶��������ֵ�ǵ����Ӵ�С���ˡ�
    void push(int value)
    {
        while (!que.empty() && value > que.back())
        {
            que.pop_back();
        }
        que.push_back(value);
    }
    // ��ѯ��ǰ����������ֵ ֱ�ӷ��ض���ǰ��Ҳ����front�Ϳ����ˡ�
    int front()
    {
        return que.front();
    }
};
std::vector<int> maxSlidingWindow(std::vector<int> &nums, int k)
{
    MyQueue que;
    std::vector<int> result;
    for (int i = 0; i < k; i++)
    { // �Ƚ�ǰk��Ԫ�طŽ�����
        que.push(nums[i]);
    }
    result.push_back(que.front()); // result ��¼ǰk��Ԫ�ص����ֵ
    for (int i = k; i < nums.size(); i++)
    {
        que.pop(nums[i - k]);          // ���������Ƴ���ǰ��Ԫ��
        que.push(nums[i]);             // ��������ǰ����������Ԫ��
        result.push_back(que.front()); // ��¼��Ӧ�����ֵ
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