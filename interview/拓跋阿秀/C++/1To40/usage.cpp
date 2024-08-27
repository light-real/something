#include <iostream>
#include <string>

using namespace std;

int main()
{
    int x = 10;
    int another = 20;
    int *const p = &x;  //常量指针 指针的指向不能变动
    // p = &another; //error: assignment of read-only variable ‘p’
    cout<<"*p = "<<*p<<endl;
    return 0;
}