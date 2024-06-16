/*
给定一个含有n个正整数的数组和一个正整数s 找出该数组中满足其和>=s的长度最小的连续子数组 并返回其长度
eg:
    输入：s = 7 nums = [2,3,1,2,4,3];
    输出：2
    解释：子数组[4,3]是该条件下长度最小的子数组
*/

#include "head.h"

int minSubArrayLen(const std::vector<int> &vec, int s) // 暴力解法
{
    int result = INT_MAX;
    int sum = 0;
    int sublen = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum = 0;
        for (int j = i; j < vec.size(); j++)
        {
            sum += vec[j];
            if (sum >= s)
            {
                sublen = j - i + 1;
                result = result <= sublen ? result : sublen;
                break;
            }
        }
    }
    return result == INT_MAX ? 0 : result;
}

int main()
{
    int s = 7;
    std::vector<int> vec = {2, 3, 1, 2, 4, 3};
    int ans = minSubArrayLen(vec,s);
    std::cout<<ans<<std::endl;
    return 0;
}