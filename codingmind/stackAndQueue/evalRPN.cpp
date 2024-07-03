#include "head.hpp"

/*
逆波兰表达式求值
根据 逆波兰表示法，求表达式的值。
有效的运算符包括 + ,  - ,  * ,  / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
说明：
整数除法只保留整数部分。 给定逆波兰表达式总是有效的。
换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

示例 1：
输入: ["2", "1", "+", "3", " * "]
输出: 9
解释: 该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

示例 2：
输入: ["4", "13", "5", "/", "+"]
输出: 6
解释: 该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6
*/

int operation(int a, int b, std::string str)
{
    char op = str[0]; // switch只能处理字符类型 不能处理字符串类型
    switch (op)
    {
    case '+':
        return a + b;
        break;
    case '-':
        return a - b;
        break;
    case '*':
        return a * b;
        break;
    case '/':
        return a / b;
        break;
    default:
        break;
    }
    return 0;
}

int evalRPN(const std::vector<std::string> &vec)
{
    std::stack<int> sta;
    int i = 0;
    int sum = 0;
    int operation_1 = 0;
    int operation_2 = 0;
    while (i < vec.size())
    {
        if (vec[i] == "+" || vec[i] == "-" || vec[i] == "*" || vec[i] == "/")
        {
            operation_1 = sta.top();
            sta.pop();
            operation_2 = sta.top();
            sta.pop();
            sum = operation(operation_2, operation_1, vec[i]);
            sta.push(sum);
        }
        else
        {
            int temp = stoi(vec[i]);
            sta.push(temp);
        }
        i++;
    }
    return sum;
}

int main()
{
    std::vector<std::string> vec;
    std::string str = "4 13 5 / +";
    // std::getline(std::cin, str);
    std::istringstream iss(str);
    while (iss >> str)
    {
        vec.push_back(str);
    }
    printVec(vec);
    std::cout << "ans = " << evalRPN(vec) << std::endl;
    return 0;
}