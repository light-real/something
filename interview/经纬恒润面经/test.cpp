#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <sstream>
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
    cout << "n = " << n << endl;
    int coloum = (n / (numRows - 1));
    cout << "coloum = " << coloum << endl;
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

bool isValidSudoku(vector<vector<char>> &board)
{
    // 一个vector 记录当前行是否出现过重复的数字
    vector<int> repeat(10, 1);
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[i][j] == '.')
            {
                continue;
            }
            if (repeat[board[i][j] - '0'] == 1) // 判断行是否有重复
            {
                repeat[board[i][j] - '0']++;
            }
            else
            {
                return false;
            }
        }
        repeat.assign(repeat.size(), 1); // 重新恢复
    }

    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (board[j][i] == '.')
                continue;
            if (repeat[board[j][i] - '0'] == 1)
            {
                repeat[board[j][i] - '0']++;
            }
            else
            {
                return false;
            }
        }
        repeat.assign(repeat.size(), 1);
    }
    // 这时候repeat数组已经恢复了
    int i = 0;
    int j = 0;
    while (1)
    {
        if (board[i][j] == '.')
        {
            j++;
        }
        else if (repeat[board[i][j] - '0'] == 1)
        {
            repeat[board[i][j] - '0']++;
            j++;
        }
        else
        {
            return false;
        }
        if (i == 8 && j == 8)
        {
            break;
        }
        if (j == 8 && (i + 1) % 3 == 0)
        {
            i++;
            j = 0;
            repeat.assign(repeat.size(), 1);
        }
        if ((i + 1) % 3 == 0 && (j + 1) % 3 == 0)
        {
            i -= 2;
            j++;
            repeat.assign(repeat.size(), 1);
        }
        if ((j + 1) % 3 == 0)
        {
            i++;
            j -= 2;
        }
    }
    return true;
}

int main()
{
    string s = "dog is my dog";
    istringstream iss(s);
    string tmp;
    vector<string> vec;
    while(iss >> tmp)
    {
        vec.push_back(tmp);
    }
    for(auto c:vec)
    {
        cout<<c<<"";
    }
    cout<<endl;
    return 0;
}
// g++ -std=c++11 -o test test.cpp