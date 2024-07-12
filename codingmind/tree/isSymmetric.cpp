/*
判断一颗二叉树是否是对称的
*/

#include "head.hpp"

bool isSymmetric_badAnswer(TreeNode *head)
{
    if (!head)
    {
        return true;
    }
    std::queue<TreeNode *> que;
    que.push(head->left);
    que.push(head->right);
    while (!que.empty())
    {
        TreeNode *node1 = que.front();
        que.pop();
        TreeNode *node2 = que.front();
        que.pop();
        if (!node1 && !node2) // 两个节点都是空
        {
            continue;
        }
        if (!node1 || node2)
        {
            return false;
        }
        if (node1->val_ != node2->val_)
        {
            return false;
        }
        //加入的顺序需要规定一下
        que.push(node1->left);
        que.push(node2->right);
        que.push(node1->right);
        que.push(node2->left);
    }
    return true;
}

bool compare(TreeNode *left, TreeNode *right)
{
    if (left == nullptr && right != nullptr)
    {
        return false;
    }
    else if (left != nullptr && right == nullptr)
    {
        return false;
    }
    else if (!left && !right)
    {
        return true;
    }
    else if (left->val_ != right->val_)
    {
        return false;
    }

    bool outside = compare(left->left, right->right);
    bool inside = compare(left->right, right->left);
    bool isSame = outside && inside;
    return isSame;
}

bool recursive_isSymmetric(TreeNode *head) // 递归方法
{
    if (!head)
    {
        return true;
    }
    return compare(head->left, head->right);
}



int main()
{
    TreeNode *head = TreeNodeInit();
    levelOrder(head);
    std::cout << "--------我是分割线------" << std::endl;
    std::cout << recursive_isSymmetric(head) << std::endl;
    return 0;
}