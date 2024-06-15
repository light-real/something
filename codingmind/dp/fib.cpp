#include "head.h"

using namespace std;

//쳲���������-----��ʵ����һ����̬�滮����
//f(0) = 0    f(1) = 1    -----��ʼ����
//f(n) = f(n-1) + f(n-2)-----״̬ת�Ʒ���

int fib_Recursion(int n)  //�ݹ�ⷨ��ʱ�临�ӶȺͿռ临�Ӷȶ��ܸ�
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

int fib_Vec(int n)  //ͨ��ά��һ�����������ж�̬�滮
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

int fib_TwoIndex(int n)  //��ʵֻҪ������������
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
        vec[1] = sum;  //��vec[1]�̶���sum��λ��
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
