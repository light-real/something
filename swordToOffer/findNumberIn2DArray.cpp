#include "head.hpp"

/*
在一个二维数组中(每个一维数组的长度相同)，每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。
请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
    std::vector<std::vector<int>> array = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}};
*/

bool findNumberIn2DArray(const std::vector<std::vector<int>> &array, int target)
{
    int m = array.size();
    int n = array[0].size();
    // 每行进行搜索
    int index = 0;
    int begin = 0;
    int end = n - 1;
    while (index < m)
    {
        if (array[index][begin] == target || array[index][end] == target)
        {
            return true;
        }
        while (begin <= end && array[index][begin] < target && array[index][end] > target)
        {
            int mid = (begin + end) >> 1;
            if (array[index][mid] == target)
            {
                return true;
            }
            else if (array[index][mid] > target)
            {
                end = mid - 1;
            }
            else
            {
                begin = mid + 1;
            }
        }
        index++;
        begin = 0;
        end = n - 1;
    }
    return false;
}
int main()
{
    std::vector<std::vector<int>> array = default2DArray();
    print2DVec(array);
    std::cout << "findNumberIn2DArray = " << findNumberIn2DArray(array, 5) << std::endl;
    return 0;
}