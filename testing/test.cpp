/*
题目描述
一天一只顽猴想去从山脚爬到山顶，途中经过一个有个N个台阶的阶梯，但是这猴子有一个习惯： 每一次只能跳1步或跳3步，
试问猴子通过这个阶梯有多少种不同的跳跃方式？

f(n)  = f(n-1) + f(n-3)


解答要求
时间限制：1000ms, 内存限制：100MB
输入
输入只有一个整数N（0<N<=50）此阶梯有多少个阶梯

输出
输出有多少种跳跃方式（解决方案数）

样例
输入样例 1 复制

3
50
输出样例 1

2
122106097
提示样例 1
*/

#include<iostream>

int jump(int n)
{
    if(n <= 0)
    {
        return 0;
    }

    if(n == 1)
    {
        return 1;
    }
    
    if(n == 2)
    {
        return 1;
    }
    
    if(n == 3)  
    {
        return 2;
    }
    return jump(n-1)+jump(n-3);
}

int main()
{
    int n;
    std::cin>>n;
    int ans = jump(n);
    std::cout<<ans<<std::endl;
    return 0;
}