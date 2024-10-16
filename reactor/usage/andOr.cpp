#include <iostream>
#include <functional>
#include <memory>
#include <ctime>
using namespace std;

int main()
{
    int a = 1; // 0b0001;
    int b = 2; // 0b0010;
    cout << (a & b) << endl; // 0
    cout << (a | b) << endl; // 3
    return 0;
}