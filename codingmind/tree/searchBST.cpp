/*
给定二叉搜索树（BST）的根节点和一个值
在BST中找到节点值等于给定值的节点
返回以该节点为根的子树 如果节点不存在，则返回 NULL
*/

#include "head.hpp"

TreeNode *searchBST(TreeNode *root, int val)
{
    while (root)
    {
        if (root->val_ == val)
        {
            return root;
        }
        else if (root->val_ > val)
        {
            root = root->left;
        }
        else
        {
            root = root->right;
        }
    }
    return root;
}

int main()
{
    return 0;
}