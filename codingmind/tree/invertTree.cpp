/*
反转二叉树

                    1
            2               3
        4      5                6
            7      8

*/

#include "head.hpp"

TreeNode *invertTree_recursive(TreeNode *head) // 递归法
{
    if (!head)
    {
        return nullptr;
    }
    std::swap(head->left, head->right);
    invertTree_recursive(head->left);
    invertTree_recursive(head->right);
    return head;
}

TreeNode *invertTree(TreeNode *head)
{
    std::queue<TreeNode *> que;
    if (!head)
    {
        return nullptr;
    }
    que.push(head);
    while (!que.empty())
    {
        int size = que.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode* node = que.front();
            que.pop();
            std::swap(node->left,node->right);
            if(node->left)
            {
                que.push(node->left);
            }
            if(node->right)
            {
                que.push(node->right);
            }
        }
    }
    return head;
}

int main()
{
    TreeNode *head = TreeNodeInit();
    // head = invertTree_recursive(head);
    head = invertTree(head);
    levelOrder(head);
    return 0;
}