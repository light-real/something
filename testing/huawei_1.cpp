/*
从一副扑克牌中随机抽取n张牌组成一个序列，规定连续3张相同牌号的卡牌可以消除
剩余卡牌按照当前顺序重新合并成新的序列后继续消除，重复以上步骤直到无法消除，最后请输出结束后剩余的卡牌序列

输入：第一行一个正整数n（1 ≤n ≤ 52），表示卡牌的数量。第二行一个字符串，以空格分隔代表卡牌号序列，卡牌号仅包含2-10，A，J，Q，K
8 
A 2 2 2 3 3 2 A

输出：一个字符串，打印最终结束后的卡牌号序列，卡牌号以空格分隔。如果最终没有卡牌剩余输出0
A 3 3 2 A
*/

#include<iostream>
#include<stack>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

void eliminate(vector<string> &vec)
{
    vector<string> temp(vec.size());
    int i = 0; //用于指示vec当前的位置
    int index = 0; //用于指示temp当前的位置
    while(i < vec.size())
    {
        temp[index] = vec[i];
        if(index >= 2 && temp[index] == temp[index-1] &&temp[index-1] == temp[index-2])
        {
            index -= 2;
            i++;
            continue;   
        }
        i++;
        index++;
    }
    for(i = 0;i<=index;i++)
    {
        if(i == index)
        {
            cout<<temp[i];
        }
        else
        {
            cout<<temp[i]<<" ";
        }
    }
    cout<<endl;
}

int main()
{
    int n;  //输入一个整数 表示卡牌的数量
    cin>>n; 
    cin.ignore();  //清空输入缓冲区
    vector<string> vec; //需要用string进行接收 因为有'10' 用char接收不行
    string tmp;
    getline(cin,tmp);
    istringstream iss(tmp);
    while(iss>>tmp)
    {
        vec.push_back(tmp);
    }
    eliminate(vec);
    return 0;
}