#include "head.h"

using namespace std;

//斐波那契数列-----其实还是一个动态规划问题
//f(0) = 0    f(1) = 1    -----初始条件
//f(n) = f(n-1) + f(n-2)-----状态转移方程

int fib_Recursion(int n)  //递归解法：时间复杂度和空间复杂度都很高
{
    if(n == 0)
    {
        return 0;
    }
    if(n == 1)
    {
        return 1;
    }

    return fib_Recursion(n-1) + fib_Recursion(n-2);
}

int fib_Vec(int n)  //通过维护一个数组来进行动态规划
{
    if(n <= 1)
    {
        return n;
    }
    vector<int> vec(n+1);
    vec[0] = 0;
    vec[1] = 1;
    for(int i = 2;i<=n;i++)
    {
        vec[i] = vec[i-1]+vec[i-2];
    }
    printVec(vec);
    return vec[n];
}

int fib_TwoIndex(int n)  //其实只要保存两个变量
{
    if(n <= 1)
    {
        return n;
    }
    vector<int> vec(2);
    vec[0] = 0;
    vec[1] = 1;
    for(int i = 2;i <= n;i++)
    {
        int sum = vec[0]+vec[1];
        vec[0] = vec[1];
        vec[1] = sum;  //将vec[1]固定存sum的位置
    }
    return vec[1];
}


int main()
{
    fib_Vec(10);
    int ans = fib_TwoIndex(10);
    cout<<ans<<endl;
    return 0;
}
