#include "head.hpp"

/*
给你一个整数数组 nums 和一个整数 k ，请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。

示例 1:
输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]

示例 2:
输入: nums = [1], k = 1
输出: [1]
*/

// 定义小顶堆的排序方式
class Mycompariosn
{
public:
    bool operator() (const std::pair<int, int> &lhs, const std::pair<int, int> &rhs)
    {
        return lhs.second > rhs.second;
    }
};

std::vector<int> topKFrequent(const std::vector<int> &vec, int k)
{
    // 统计每个数字的频率
    std::unordered_map<int, int> umap;
    for (int i = 0; i < vec.size(); i++)
    {
        umap[vec[i]]++;
    }

    // 加入小顶堆
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Mycompariosn> pq; // 定义一个小顶堆 大小为k

    for (auto u = umap.begin(); u != umap.end(); u++)
    {
        printPair(*u);
        pq.push(*u);
        
        if (pq.size() > k)
        {
            pq.pop();
        }
    }

    // 找出出现频率最大的k个元素
    std::vector<int> result(k);
    for (int i = k - 1; i >= 0; i--)
    {
        result[i] = pq.top().first;
        pq.pop();
    }
    printVec(result);
    return result;
}

int main()
{
    std::vector<int> vec = {1,11,2,1,2,2,3};
    topKFrequent(vec,2);
    return 0;
}