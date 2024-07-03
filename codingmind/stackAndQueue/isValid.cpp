#include "head.hpp"

// 判断是否是有效的括号
bool isValid(const std::string &str)
{
    std::stack<char> sta;
    int i = 0;
    while (i < str.size())
    {
        if (str[i] == '(' || str[i] == '[' || str[i] == '{')
        {
            sta.push(str[i]);
        }
        else
        {
            char temp = sta.top();
            sta.pop();
            if (temp == '(' && str[i] != ')')
            {
                return false;
            }
            else if (temp == '[' && str[i] != ']')
            {
                return false;
            }
            else if (temp == '{' && str[i] != '}')
            {
                return false;
            }
        }
        i++;
    }
    if (!sta.empty())
    {
        return false;
    }
    return true;
}

int main()
{
    std::string str;
    std::cin >> str;
    std::cout << str << std::endl;
    std::cout << isValid(str) << std::endl;
    return 0;
}