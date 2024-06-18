/*
����һ��������n ���ɰ���1��$n^{2}$����Ԫ�أ���Ԫ�ذ�˳ʱ���������е������ξ���

eg:
    ���룺3
    �����[
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
    int starty = 0;   // ������ʼλ��
    int loop = n / 2; // ����ѭ������ ���n = 3 ��ֻѭ��������һȦ
    int mid = n / 2;  // �м�λ�� ���ڵ�����ֵ
    int count = 1;
    int offset = 1; // ����ƫ����
    int i, j;
    while (loop--)
    {
        i = startx;
        j = starty;

        for (j; j < n - offset; j++) // ���д������Ҹ�ֵ ����ҿ�
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