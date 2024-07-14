/*
返回二叉树的最大深度
*/

#include "head.hpp"

int maxDepth(TreeNode *head)
{
    std::queue<TreeNode *> que;
    if (!head)
    {
        return 0;
    }
    int Depth = 0;
    que.push(head);
    while (!que.empty())
    {
        int size = que.size();
        for (int i = 0; i < size; i++)
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
        Depth++;
    }
    return Depth;
}

int main()
{
    TreeNode *head = TreeNodeInit();
    std::cout << "maxDepth = " << maxDepth(head) << std::endl;
    return 0;
}