#include "head.hpp"

// 返回二叉树的右视图
std::vector<int> rightSideView(TreeNode *head)
{
    std::vector<int> result;
    std::queue<TreeNode *> que;
    if (head)
    {
        que.push(head);
    }
    while (!que.empty())
    {
        int size = que.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = que.front();
            que.pop();
            if (i == size - 1)
            {
                result.push_back(node->val_);
            }
            if (node->left)
            {
                que.push(node->left);
            }
            if (node->right)
            {
                que.push(node->right);
            }
        }
    }
    printVec(result);
    return result;
}

int main()
{
    TreeNode* head = TreeNodeInit();
    rightSideView(head);
    return 0;
}