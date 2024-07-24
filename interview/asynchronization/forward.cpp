/*
std::forward 完美转发
1. 简介
std::forward是C++11引入的标准库函数模板，用于实现完美转发（perfect forwarding）。它能够将参数完美地转发给另一个函数，保持参数的值类别（左值或右值）不变。

2. 功能
std::forward的主要功能是将传递给它的参数转发给另一个函数，并确保参数的值类别（左值或右值）保持不变。这在泛型编程中非常有用，尤其是当需要将参数传递给另一个函数模板时。
*/

#include <iostream>
#include <utility>

void process(int &x)
{
    std::cout << "Lvalue reference process : " << x << std::endl;
}

void process(int &&x)
{
    std::cout << "Rvalue reference process : " << x << std::endl;
}

template <typename T>
void forwarder(T &&arg) // T&&表示万能引用（universal reference），可以绑定到左值和右值
{
    process(std::forward<T>(arg));
}

/*
左值和右值的区别：
    左值（Lvalue）：表示对象的身份，可以取地址。例如变量x。
    右值（Rvalue）：表示对象的值，不能取地址。例如字面值20。
*/

int main()
{
    int x = 20;
    forwarder(x);  // 调用process(int &x) x这里表示一个左值
    forwarder(20); // 调用process(int &&x) 20这里表示一个右值
    return 0;
}