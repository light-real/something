/*
给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，将字符串中的字母字符保持不变，而将每个数字字符替换为number。

例如，对于输入字符串 "a1b2c3"，函数应该将其转换为 "anumberbnumbercnumber"。

对于输入字符串 "a5b"，函数应该将其转换为 "anumberb"

输入：一个字符串 s,s 仅包含小写字母和数字字符。

输出：打印一个新的字符串，其中每个数字字符都被替换为了number

样例输入：a1b2c3

样例输出：anumberbnumbercnumber
*/

#include"head.hpp"

void replaceNumber(std::string& str)
{
    int i = 0;
    std::string new_str = "";
    while(i < str.size())
    {
        if(str[i] >= 'a' && str[i] <= 'z')
        {
            new_str += str[i];
        }
        else
        {
            new_str += "number";
        }
        i++;
    }
    std::cout<<new_str<<std::endl;
}

int main()
{
    std::string str = "a1b2c3";
    replaceNumber(str);
    return 0;
}