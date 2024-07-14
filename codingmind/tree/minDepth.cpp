/*
返回二叉树的最小深度
*/

#include "head.hpp"

int minDepth(TreeNode* head)
{
    int Depth = 1;
    std::queue<TreeNode*> que;
    if(!head)
    {
        return 0;
    }
    que.push(head);
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
            if(!node->left && !node->right)
            {
                return Depth;
            }
        }
        Depth++;
    }
    return Depth;
}

int main()
{
    TreeNode* head = TreeNodeInit();
    std::cout<<"minDepth = "<<minDepth(head)<<std::endl;
    return 0;
}