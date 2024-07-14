/*
判断一棵树是否是平衡二叉树
*/

#include "head.hpp"

int getDepth(TreeNode *node)
{
    if (!node)
    {
        return 0;
    }

    int leftDepth = getDepth(node->left);
    if (leftDepth == -1)
        return -1;
    int rightDepth = getDepth(node->right);
    if (rightDepth == -1)
        return -1;

    return abs(leftDepth - rightDepth) > 1 ? -1 : 1 + std::max(leftDepth, rightDepth);
}

bool isBanlanced(TreeNode* root)
{
    return getDepth(root) == -1 ? false:true;
}

int main()
{
    TreeNode* head = TreeNodeInit();
    std::cout<<isBanlanced(head)<<std::endl;
    return 0;
}