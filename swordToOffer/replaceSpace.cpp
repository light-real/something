#include "head.hpp"

/*
请实现一个函数，将一个字符串中的每个空格替换成“%20”。
例如，当字符串为We Are Happy,则经过替换之后的字符串为We%20Are%20Happy.
*/

// 这个算是直接调用replace方法
// string.replace(index,替换原字符串的大小,目标字符串)
void replaceSpaceDirect(std::string &str)
{
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ' ')
        {
            str.replace(i, 1, "%20");
        }
    }
}

// 先计算出需要的总大小，然后从后往前进行替换
void replaceSpace(std::string &str) 
{
    int count = 0;
    int size = str.size();
    for (int i = 0; i < size; i++)
    {
        if (str[i] == ' ')
        {
            ++count;
        }
    }
    int totalLength = size + count * 2;
    str.resize(totalLength);
    --totalLength;
    for (int i = size - 1; i >= 0; --i)
    {
        if (str[i] != ' ')
        {
            str[totalLength--] = str[i];
        }
        else
        {
            str[totalLength--] = '0';
            str[totalLength--] = '2';
            str[totalLength--] = '%';
        }
    }
}


int main()
{
    std::string str = "We Are Happy";
    std::cout << "before modify = " << str << std::endl;
    replaceSpace(str);
    std::cout << "after modify = " << str << std::endl;
    return 0;
}