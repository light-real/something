#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

int main()
{
    string s = "barfoothefoobarman";
    vector<string> words{"foo","bar"};
    int sLen = s.size();
    int n = words.size();
    int m = words[0].size();
    if (sLen < n * m)
    {
        return {};
    }
    vector<int> umapw{26, 0};
    vector<int> umaps{26, 0};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout<<words[i][j]<<endl;
            ++umapw[words[i][j]-'a'];
        }
        umaps[s[i] - 'a']++;
    }
    cout<<umapw[0]<<endl;
    cout<<umapw[1]<<endl;
    cout<<umapw[2]<<endl;
    for(int i = 0;i<umapw.size();i++)
    {
        cout<<umapw[i]<<" ";
    }
    cout<<endl;
    return 0;
}