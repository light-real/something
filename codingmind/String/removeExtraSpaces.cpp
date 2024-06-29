#include "head.hpp"

/*
注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。
返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
*/

// 移除多余空格 开头结尾空格out 中间字符串之间只能剩一个
void removeSpace(std::string &s)
{
    int slow = 0; // 整体思想参考https://programmercarl.com/0027.移除元素.html
    for (int i = 0; i < s.size(); ++i)
    { //
        if (s[i] != ' ')
        { // 遇到非空格就处理，即删除所有空格。
            if (slow != 0)
                s[slow++] = ' '; // 手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
            while (i < s.size() && s[i] != ' ')
            { // 补上该单词，遇到空格说明单词结束。
                s[slow++] = s[i++];
            }
        }
    }
    s.resize(slow); // slow的大小即为去除多余空格后的大小。
}

void removeExtraSpaces(std::string &str)
{
    removeSpace(str);
    int i = 0;
    int size_ = str.size();
    int start = 0;
    int end = 0;
    while (i < size_)
    {
        if (i > 0 && str[i] != ' ' && str[i - 1] == ' ')
        {
            start = i;
        }
        else if (i + 1 < size_ && str[i] != ' ' && str[i + 1] == ' ')
        {
            reverseString(str, start, i);
            start = i;
        }
        else if (str[i] != ' ' && i + 1 == size_)
        {
            reverseString(str, start, i);
        }
        i++;
    }
    reverseString(str, 0, size_ - 1);
    std::cout << str << std::endl;
}

int main()
{
    std::string str = "  hello world  ";
    std::cout << str << std::endl;
    removeExtraSpaces(str);
    return 0;
}