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
    // ��ʼ���ڵ�
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
    �������Ĳ�α���
    ��α������������ڹ�����ȱ��� ������ȱ���ʹ�ö���ʵ�� 
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
    ��������������� -- ������
    ������� --ʹ��ջ
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
    ������������� -- �����
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
        �ϲ������� �����Ӧ�Ľڵ㶼���� ��ô�½ڵ��ֵΪ�����ĺ�
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
    //���ض�������������
    if(!root)
    {
        return 0;
    }
    queue<TreeNode*> que;  //���ڴ洢
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
    //�ж�һ�����Ƿ�Ϊƽ�������  
    //solution: ��ÿ���ڵ����� ������ҽڵ�����֮�����1 �򷵻�false
    Depth(root);
    cout<<"isBal is " << isBal<<endl;
    return isBal;
}

bool iscompeleteTree(TreeNode* root)
{
    //�ж��Ƿ�����ȫ������
    //solution: ��α��� �ҵ���һ���սڵ�
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

    //���Ƕ��������������
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
    //�����������������ĳ�ڵ� ���ҽ�·���洢��vec��
    
    //����ǿսڵ� ֱ��return
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

    if(flagdfs)  //�ҵ�
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