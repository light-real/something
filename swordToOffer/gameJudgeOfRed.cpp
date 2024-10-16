#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <cctype>
#include <map>
using namespace std;

char gameJudge(string &s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    // 评分去除最高分和最低分
    sort(s.begin(), s.end());
    int result = 0;
    for (long long i = 1; i < s.size() - 1; i++)
    {
        result += (s[i] - 'a');
    }
    result = (result % (s.size() - 2) == 0 ? result / (s.size() - 2) : result / (s.size() - 2) + 1);
    return result + 'a';
}
int main()
{
    // 第一行输入两个整数 n评委的数量 m选手的数量
    // 此后n行，第i行输入一个长度为m，且有大小写混合构成的字符串 表示第i个评委对第j个选手做出的评分
    long long n, m;
    cin >> n >> m;
    // 存储每个学生的编号和成绩
    map<char, vector<long long>> student;
    vector<string> score(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> score[i];
    }
    for (long long i = 0; i < m; i++)
    {
        string temp;
        for (long long j = 0; j < n; j++)
        {
            temp += score[j][i];
        }
        char result = gameJudge(temp);
        student[result].push_back(i); // 使用map存储，但是成绩相同时会被覆盖
    }
    for (auto i : student)
    {
        for (auto u : i.second)
        {
            cout << u + 1 << " ";
        }
    }
    cout << endl;
    for (auto i : student)
    {
        for (int u = 0; u < i.second.size(); u++)
        {
            cout << i.first << " ";
        }
    }
    cout << endl;
    return 0;
}