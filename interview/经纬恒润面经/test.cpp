#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string numToBinary(long long k)
{
    string ans = "";
    int record = 0;
    while (k > 0)
    {
        record = k % 2;
        k /= 2;
        ans += to_string(record);
    }
    reverse(ans.begin(), ans.end());

    return ans;
}



// 计算二进制数的价值
int caculate(string &str, int x)
{
    if(x > str.size())
    {
        return 0;
    }
    reverse(str.begin(),str.end());
    // int ans = (x == 1 ? (str[0] - '0') : 0);
    int ans = 0;

    int i = 1;
    int times = x;
    while (i <= str.size())
    {
        if (i == times)
        {
            ans += (str[i-1] - '0');
            times += x;
            i = times;
        }
        else
        {
            i++;
        }
    }
    return ans;
}

void testCaculate(long long k)
{
    for(int i = 0;i < k;i++)
    {
        string temp = numToBinary(i);
        cout<<"numToBinary = "<<temp<<"     price = "<<caculate(temp,1)<<endl;
    }
}

long long findMaximumNumber(long long k, int x)
{
    string str = numToBinary(k);
    int sumPrice = 0;
    int previousPrice = 0;
    for (int i = 1; sumPrice <= k; i++)
    {
        string temp = numToBinary(i);
        sumPrice += caculate(temp, x);
        // cout<<"sumPrice = "<<sumPrice<<endl;
        previousPrice = i;
    }
    return previousPrice-1;
}

int main()
{
    cout<<findMaximumNumber(3278539330613, 5)<<endl;
    // testCaculate(10);
    return 0;
}