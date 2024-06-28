/*
给定一个字符串 s 和一个整数 k，从字符串开头算起, 每计数至 2k 个字符
就反转这 2k 个字符中的前 k 个字符。

如果剩余字符少于 k 个，则将剩余字符全部反转。

如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。

示例:

输入: s = "abcdefg", k = 2
输出: "bacdfeg"
*/

#include "head.hpp"

void reverseString(std::string &str, int start, int end)
{
    for (int i = start, j = end; i < j; i++, j--)
    {
        std::swap(str[i], str[j]);
    }
}

void reverseStr(std::string &str, int k)
{
    int size_ = str.size();
    int count = 1; // 用于统计index的下标
    int index = 0;
    while (index < size_)
    {
        if (size_ - index < k)
        {
            reverseString(str, index, size_ - 1);
            break;
        }
        else if (size_ - index > k && size_ - index < 2 * k)
        {
            reverseString(str, index, index + k - 1);
            break;
        }
        else if (index < size_)
        {
            reverseString(str, index, index + k - 1);
            index = 2 * k * count;
            count++;
        }
    }
    std::cout<<str<<std::endl;
}

int main()
{
    std::string str = "abcdefg";
    std::cout<<str<<std::endl;
    reverseStr(str,2);
    return 0;
}