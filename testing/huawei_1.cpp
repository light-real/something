/*
��һ���˿����������ȡn�������һ�����У��涨����3����ͬ�ƺŵĿ��ƿ�������
ʣ�࿨�ư��յ�ǰ˳�����ºϲ����µ����к�����������ظ����ϲ���ֱ���޷���������������������ʣ��Ŀ�������

���룺��һ��һ��������n��1 ��n �� 52������ʾ���Ƶ��������ڶ���һ���ַ������Կո�ָ������ƺ����У����ƺŽ�����2-10��A��J��Q��K
8 
A 2 2 2 3 3 2 A

�����һ���ַ�������ӡ���ս�����Ŀ��ƺ����У����ƺ��Կո�ָ����������û�п���ʣ�����0
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
    int i = 0; //����ָʾvec��ǰ��λ��
    int index = 0; //����ָʾtemp��ǰ��λ��
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
    int n;  //����һ������ ��ʾ���Ƶ�����
    cin>>n; 
    cin.ignore();  //������뻺����
    vector<string> vec; //��Ҫ��string���н��� ��Ϊ��'10' ��char���ղ���
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