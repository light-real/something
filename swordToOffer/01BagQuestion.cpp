#include "head.hpp"

// 01背包问题

void solve(const std::vector<int> &weight, const std::vector<int> &value, std::vector<std::vector<int>> &dp, int BagSize)
{
    // dp[i][j]表示在物品[0-i]并且容量为j的条件下，能得到的最大价值
    int m = dp.size();
    int n = dp[0].size();
    for (int i = 0; i < m; i++)
    {
        dp[i][0] = 0; // 容量为0 那么最大价值即为0
    }
    for (int i = 0; i < n; i++)
    {
        if (i < weight[0]) // 当前容量小于物品重量
        {
            dp[0][i] = 0;
        }
        else
        {
            dp[0][i] = value[0];
        }
    }
    for (int i = 1; i < m; i++) // 物品
    {
        for (int j = 1; j <= BagSize; j++) // 容量
        {
            if (j < weight[i]) // 如果当前容量都小于i的重量了，那么不会取到物品i
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = std::max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
        }
    }
}

int main()
{
    int BagSize = 4;
    std::vector<int> weight = {1, 3, 4};
    std::vector<int> value = {15, 20, 30};
    std::vector<std::vector<int>> dp(weight.size(), std::vector<int>(BagSize + 1, 0));
    solve(weight, value, dp, BagSize);
    std::cout << "result = " << dp[weight.size() - 1][BagSize] << std::endl;
    print2DVec(dp);
}