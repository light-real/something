/*
判断一颗二叉树是否是对称的
*/

#include "head.hpp"

bool isSymmetric(TreeNode* head)
{
    if(!head)
    {
        return true;
    }
    std::queue<TreeNode*> que;
    que.push(head->left);
    que.push(head->right);
    while(!que.empty())
    {
        TreeNode* node1 = que.front();
        que.pop();
        TreeNode* node2 = que.front();
        que.pop();
        
    }
    return true;
}

int main()
{
    return 0;
}