#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

/*
ͼ�ĳ�����ʾ��ʽ���ڽӾ�����ڽӱ�

*/

//�����ڽӾ���ʵ�ֵ�����ͼ��
class GraphAdjMat
{
    vector<int> vectices;  //�����б� Ԫ�ش�����ֵ
    vector<vector<int>> adjMat;  //�ڽӾ���
    
public:
    GraphAdjMat(const vector<int>& vectices,const vector<vector<int>> %edges)
    {
        //��Ӷ���
        for(int val:vectices)
        {
            addVertex(val);
        }

        //��ӱ�
        for(const vector<int>& edge :edges)
        {
            addEdge(edge[0],edge[1]);
        }
    }
    
    //��ȡ��������
    int size() const
    {
        return vectices.size();
    }

    //��Ӷ���
    void addVertex(int val)
    {
        int n = size();
        //�򶥵��б�������¶����ֵ
        vectices.push_back(val);
        //���ڽӾ��������һ��
        adjMat.emplace_back(vector<int>(n,0));
        //���ڽӾ��������һ��
        for(vector<int> &row:adjMat)
        {
            row.push_back(0);
        }
    }
}
