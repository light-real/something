#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
#include<queue>

using namespace std;

/*
图的常见表示方式有邻接矩阵和邻接表

*/

//基于邻接矩阵实现的无向图类
class GraphAdjMat
{
    vector<int> vectices;  //顶点列表 元素代表顶点值
    vector<vector<int>> adjMat;  //邻接矩阵
    
public:
    GraphAdjMat(const vector<int>& vectices,const vector<vector<int>> %edges)
    {
        //添加顶点
        for(int val:vectices)
        {
            addVertex(val);
        }

        //添加边
        for(const vector<int>& edge :edges)
        {
            addEdge(edge[0],edge[1]);
        }
    }
    
    //获取顶点数量
    int size() const
    {
        return vectices.size();
    }

    //添加顶点
    void addVertex(int val)
    {
        int n = size();
        //向顶点列表中添加新顶点的值
        vectices.push_back(val);
        //在邻接矩阵中添加一行
        adjMat.emplace_back(vector<int>(n,0));
        //在邻接矩阵中添加一列
        for(vector<int> &row:adjMat)
        {
            row.push_back(0);
        }
    }
}
