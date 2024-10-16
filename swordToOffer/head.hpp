#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>

void printVec(const std::vector<int> &vec)
{
    for (auto &u : vec)
    {
        std::cout << u << " ";
    }
    std::cout << std::endl;
}

void print2DVec(const std::vector<std::vector<int>> &vec)
{
    for (auto &u : vec)
    {
        printVec(u);
    }
}

std::vector<std::vector<int>> default2DArray()
{
    int index = 1;
    std::vector<std::vector<int>> array = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}};
    return array;
}
std::vector<std::vector<int>> input2DArray(int m, int n) // 构建一个mxn的二维数组
{
    std::vector<std::vector<int>> array(m, std::vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> array[i][j];
        }
    }
    return array;
}