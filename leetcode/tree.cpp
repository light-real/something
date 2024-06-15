#include<iostream>
#include<queue>
#include<vector>
#include<stack>
#include<math.h>
#include<algorithm>

using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(nullptr),right(nullptr){}
};

TreeNode* init()
{
    // 初始化节点
    TreeNode* node1 = new TreeNode(1);
    TreeNode* node2 = new TreeNode(2);
    TreeNode* node3 = new TreeNode(3);
    TreeNode* node4 = new TreeNode(4);
    TreeNode* node5 = new TreeNode(5);
    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node8 = new TreeNode(8);
    TreeNode* node9 = new TreeNode(9);
    TreeNode* node10 = new TreeNode(10);
    TreeNode* node11 = new TreeNode(11);
    /*
                    node1
           node2                  node3
    node4         node5       node6   node7
node8   node9  node10      node11
    
    */
    node1->left = node2;
    node1->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    node4->left = node8;
    node4->right = node9;
    node5->left = node10;
    node6->left = node11;
    return node1;
}

vector<int> levelOrder(TreeNode *root)
{
    /*
    二叉树的层次遍历
    层次遍历本质上属于广度优先遍历 广度优先遍历使用队列实现 
    */
    queue<TreeNode*> que;
    que.push(root);
    vector<int> vec;
    while(!que.empty())
    {
        TreeNode* node = que.front(); 
        que.pop();
        vec.push_back(node->val);
        if(node->left)
        {
            que.push(node->left);
        }
        if(node->right)
        {
            que.push(node->right);
        }
    }
    return vec;
}


vector<int> preOrder(TreeNode* root)
{
    /*
    二叉树的先序遍历 -- 根左右
    深度优先 --使用栈
    */
    vector<int> pre;
    stack<TreeNode*> sta;
    TreeNode* node = root;
    while(node || !sta.empty())
    {
        while(node)
        {
            pre.push_back(node->val);
            sta.push(node->right);
            node = node->left;
        }
        node = sta.top();
        sta.pop();
    }
    return pre;
}

vector<int> inOrder(TreeNode* root)
{
    /*
    二叉树中序遍历 -- 左根右
    */
    vector<int> vec;
    stack<TreeNode*> sta;
    TreeNode* node = root;
    while(node ||!sta.empty())
    {
        while(node)
        {
            sta.push(node);
            node = node->left;
        }
        node = sta.top();
        sta.pop();
        vec.push_back(node->val);
        node = node->right;
    }
    return vec;
}


TreeNode* mergeTree(TreeNode* t1,TreeNode* t2)
{
    /*
        合并两个树 如果对应的节点都存在 那么新节点的值为它两的和
    */
    if(!t1)
    {
        return t2;
    }
    if(!t2)
    {
        return t1;
    }
    TreeNode* head = new TreeNode(t1->val+t2->val);
    head->left = mergeTree(t1->left,t2->left);
    head->right = mergeTree(t1->right,t2->right);
    return head;
}

int maxDepth(TreeNode *root)
{
    //返回二叉树的最大层数
    if(!root)
    {
        return 0;
    }
    queue<TreeNode*> que;  //用于存储
    int res = 0;
    que.push(root);
    while(!que.empty())
    {
        int size = que.size();
        for(int i = 0;i<size;i++)
        {
            TreeNode* node = que.front();
            que.pop();
            if(node->left)
            {
                que.push(node->left);
            }
            if(node->right)
            {
                que.push(node->right);
            }
        }
        res++;
    }
    return res;
}

bool isBal = true;
int Depth(TreeNode* root)
{
    if(!root)
    {
        return 0;
    }
    int le = Depth(root->left);
    int ri = Depth(root->right);
    if(abs(le-ri) > 1)
    {
        isBal = false;
    }
    return max(le,ri)+1;
}

bool isBanlanced(TreeNode* root)
{
    //判断一个树是否为平衡二叉树  
    //solution: 求每个节点的深度 如果左右节点的深度之差大于1 则返回false
    Depth(root);
    cout<<"isBal is " << isBal<<endl;
    return isBal;
}

bool iscompeleteTree(TreeNode* root)
{
    //判断是否是完全二叉树
    //solution: 层次遍历 找到第一个空节点
    bool flag = false;
    queue<TreeNode*> que;
    que.push(root); 
    while(!que.empty())
    {
        int qsize = que.size();
        for(int i = 0;i<qsize;i++)
        {
            TreeNode* node = que.front();
            que.pop();
            if(node == nullptr)
            {
                flag = true;
            }
            else
            {
                if(flag)
                {
                    cout<<"The tree is not a compelete tree!"<<endl;
                    return false;
                }
                que.push(node->left);
                que.push(node->right);
            }
        }
    }
    cout<<"The tree is a compelete tree "<<endl;
    return true;
}

vector<int> getpath(TreeNode* root,int target)
{

    //这是二叉查找树的搜索
    vector<int> vec;
    TreeNode* node = root;
    while(node->val != target)
    {
        vec.push_back(node->val);
        if(node->val > target)
        {
            node = node->left;
        }
        else
        {
            node = node->right;
        }
    }
    vec.push_back(node->val);
    for(int i = 0;i<vec.size();i++)
    {
        cout<<vec[i]<<" ";
    }
    cout<<endl;
    return vec;
}

bool flagdfs = false;
void dfs(TreeNode* root,vector<int>& vec,int o)
{
    //对于任意二叉树搜索某节点 并且将路径存储在vec中
    
    //如果是空节点 直接return
    if(flagdfs || !root)  
    {
        return ;
    } 

    vec.push_back(root->val); 
    
    if(root->val == o)
    {
        flagdfs = true;
        return ;
    }

    dfs(root->left,vec,o);
    dfs(root->right,vec,o);

    if(flagdfs)  //找到
    {
        return ;
    }
    
    vec.pop_back();
}


int main()
{
    TreeNode* node = init();

    /*
                    node1
           node2                  node3
    node4         node5       node6   node7
node8   node9  node10      node11
    
    */
    vector<int> vec;
    // node = mergeTree(node,node);
    // vector<int> vec = inOrder(node);


    dfs(node,vec,11);
    
    
    // int res = maxDepth(node);
    // isBanlanced(node);
    // iscompeleteTree(node);
    // cout<<"maxDepth is "<<res<<endl;
    for(auto p:vec)
    {
        cout<<p<<" ";
    }
    cout<<endl;
    return 0;
}