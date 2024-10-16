#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
using namespace std;
/*
找出给定数组的最长子区间，其中最长子区间内任意两个数的最大公约数gcd为1
*/

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

int maxLength(const vector<int> &nums)
{
}

int main()
{
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        cin >> nums[i];
    }
    
    return 0;
}