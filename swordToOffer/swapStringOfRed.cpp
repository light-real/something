#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
#include <unordered_map>
using namespace std;

/*
如果字符串s可以由某个字符串t重复x次得到，那么字符串s为周期串
现给出一个只包含小写字母的字符串，可以执行最多一次操作，选择任意下标，交换两个下标的字符，能否使得字符串s变成一个周期串
*/

void judge(string &s)
{
    // 想要是周期串，必须对半分 每个字符出现的次数必须是偶数次
    int size = s.size();
    unordered_map<char, int> hash;
    bool flag = true;
    for (int i = 0; i < size; i++)
    {
        hash[s[i]]++;
    }
    for (int i = 0; i < hash.size(); i++)
    {
        if (hash[i] % 2 == 1)
        {
            flag = false;
            break;
        }
    }
    if (flag)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}
int main()
{
    int T;
    cin >> T;
    while (T--)
    {
        string s;
        judge(s);
    }
    return 0;
}
