#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <cctype>

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
    if (x > str.size())
    {
        return 0;
    }
    reverse(str.begin(), str.end());
    // int ans = (x == 1 ? (str[0] - '0') : 0);
    int ans = 0;

    int i = 1;
    int times = x;
    while (i <= str.size())
    {
        if (i == times)
        {
            ans += (str[i - 1] - '0');
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
    for (int i = 0; i < k; i++)
    {
        string temp = numToBinary(i);
        cout << "numToBinary = " << temp << "     price = " << caculate(temp, 1) << endl;
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
    return previousPrice - 1;
}

string convert(string s, int numRows)
{
    int n = s.size();
    cout<<"n = "<<n<<endl;
    int coloum = (n / (numRows-1));
    cout<<"coloum = "<<coloum<<endl;
    vector<vector<char>> vec(numRows, vector<char>(coloum));
    int index = 0; // 用于指示字符串的下标
    int row = 0;
    int col = 0;
    bool flag = false; // 用于指示当前是否斜着走
    while (index < n)
    {
        if (col == 0 || !flag)
        {
            while (row != numRows)
            {
                vec[row][col] = s[index];
                row++;
                index++;
            }
            flag = true; // 指示当前需要斜着走
            row--;
        }
        if (flag)
        {
            row--;
            col++;
            vec[row][col] = s[index];
            index++;
            if (row == 0)
            {
                flag = false;
                row = 1;
            }
        }
    }
    for (auto au : vec)
    {
        for (auto a : au)
        {
            cout << a << "  ";
        }
        cout << endl;
    }
    return s;
}



int main()
{
    char str = '1';
    int x = isalnum(str);
    cout<<"x = "<<x<<endl;
    return 0;
}
// g++ -std=c++11 -o test test.cpp