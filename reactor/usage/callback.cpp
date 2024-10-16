#include <iostream>
#include <functional>
#include <memory>
#include <ctime>
using namespace std;

/* 普通回调函数
int Add(std::function<int(int, int)> add, int a, int b)
{
    cout << add(a, b) << endl;
    return 0;
}

int add(int a, int b)
{
    return a + b;
}
*/

// 注意std::function的使用
// std::function<returnType(argTypr,argTypr,...)> func
// 普通回调函数无法调用类成员函数

class MyAdd
{
public:
    void add(int a, int b)
    {
        cout << a + b << endl;
    }
    int a, b;
};

void callback()
{
    int a = 1;
    int b = 2;
    std::shared_ptr<MyAdd> cuso = std::make_shared<MyAdd>();
    std::function<void(int, int)> addFunc = std::bind(&MyAdd::add, cuso, std::placeholders::_1, std::placeholders::_2);
    addFunc(a, b);
}
int main()
{
    time_t time1 = time(0);
    tm *timeNow = localtime(&time1);
    char buf[32] = {0};
    snprintf(buf, 20, "%4d-%02d-%02d-%02d:%02d", timeNow->tm_year + 1900, timeNow->tm_mon, timeNow->tm_mday, timeNow->tm_hour, timeNow->tm_min);
    for (auto &c : buf)
    {
        cout << c;
    }
    cout << endl;
    return 0;
}