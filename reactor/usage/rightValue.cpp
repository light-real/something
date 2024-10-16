#include <iostream>

using namespace std;

int main()
{
    // move可以将左值移动为右值
    int a = 10;
    int &&b = std::move(10);
    cout << b << endl;
    return 0;
}