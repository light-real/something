/*
给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。

假设二叉树中至少有一个节点。
*/

#include "head.hpp"

int findBottomLeftValue(TreeNode *root)
{
    // 还真得用层次遍历来写
    std::queue<TreeNode *> treeQue;
    if (root == nullptr)
    {
        return 0;
    }
    int result = 0;
    treeQue.push(root);
    while (!treeQue.empty())
    {
        int size = treeQue.size();
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = treeQue.front();
            treeQue.pop();
            if (i == 0)
                result = node->val_; // 记录最后一行最后一个元素
            if (node->left)
            {
                treeQue.push(node->left);
            }
            if (node->right)
            {
                treeQue.push(node->right);
            }
        }
    }
    std::cout<<"result = "<<result<<std::endl;
    return result;
}

int main()
{
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *head = TreeNodeInitWithVector(values);
    levelOrder(head);
    findBottomLeftValue(head);
    return 0;
}