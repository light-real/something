/*
计算完全二叉树节点的个数
*/

#include "head.hpp"

int getNodesNum(TreeNode *head)
{
    if(!head)
    {
        return 0;
    }
    //使用队列 层次遍历
    std::queue<TreeNode*> que;
    que.push(head);
    int count = 1;
    while(!que.empty())
    {
        TreeNode* node = que.front();
        que.pop();
        if(node->left)
        {
            que.push(node->left);
            count++;
        }
        if(node->right)
        {
            que.push(node->right);
            count++;
        }
        
    }
    std::cout<<"count = "<<count<<std::endl;
    return count;
}

int main()
{
    std::vector<int> values = {1,2,3,4,5};
    TreeNode* head = TreeNodeInitWithVector(values);
    levelOrder(head);
    getNodesNum(head);
    return 0;
}