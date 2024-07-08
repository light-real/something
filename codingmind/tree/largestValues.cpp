/*
找到二叉树每一层的最大值
*/

#include "head.hpp"

std::vector<int> largestValues(TreeNode *head)
{
    // 层次遍历 找到对应vector的最大值
    std::queue<TreeNode *> que;
    std::vector<int> result;
    if (head)
    {
        que.push(head);
    }
    while (!que.empty())
    {
        int size = que.size();
        int levelmax = INT_MIN;
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = que.front();
            que.pop();
            levelmax = levelmax > node->val_ ? levelmax : node->val_;
            if (node->left)
            {
                que.push(node->left);
            }
            if (node->right)
            {
                que.push(node->right);
            }
        }
        result.push_back(levelmax);
    }
    printVec(result);
    return result;
}

int main()
{
    TreeNode *head = TreeNodeInit();
    largestValues(head);
    return 0;
}