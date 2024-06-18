/*
给定一个正整数n 生成包含1到$n^{2}$所有元素，且元素按顺时针螺旋排列的正方形矩阵

eg:
    输入：3
    输出：[
        [1,2,3],
        [8,9,4],
        [7,6,5]
    ]
*/

#include "head.h"

std::vector<std::vector<int>> generateMatrix(int n)
{
    std::vector<std::vector<int>> vec(n, std::vector<int>(n,0));
    int startx = 0;
    int starty = 0;   // 定义起始位置
    int loop = n / 2; // 定义循环次数 如果n = 3 则只循环最外面一圈
    int mid = n / 2;  // 中间位置 用于单独赋值
    int count = 1;
    int offset = 1; // 定义偏移量
    int i, j;
    while (loop--)
    {
        i = startx;
        j = starty;

        for (j; j < n - offset; j++) // 上行从左向右赋值 左闭右开
        {
            vec[i][j] = count++;
        }

        for (i; i < n - offset; i++)
        {
            vec[i][j] = count++;
        }

        for (; j > starty; j--)
        {
            vec[i][j] = count++;
        }

        for (; i > startx; i--)
        {
            vec[i][j] = count++;
        }

        startx++;
        starty++;
    }
    if (n % 2 == 1)
    {
        vec[mid][mid] = count;
    }
    return vec;
}

int main()
{
    int n = 3;
    printTwo_Vec(generateMatrix(n));
    return 0;
}