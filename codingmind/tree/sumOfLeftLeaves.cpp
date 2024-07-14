/*
左叶子之和
*/

#include "head.hpp"

int sumOfLeftLeaves(TreeNode *root)
{
    std::queue<TreeNode *> treeQue;
    if (root == nullptr)
    {
        return 0;
    }
    int sum = 0;
    treeQue.push(root);
    while (!treeQue.empty())
    {
        TreeNode *node = treeQue.front();
        treeQue.pop();
        if (node->left)
        {
            if (node->left->left == nullptr && node->left->right == nullptr)
            {
                sum += node->left->val_;
            }
            treeQue.push(node->left);
        }
        if (node->right)
        {
            treeQue.push(node->right);
        }
    }
    return sum;
}

int main()
{
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *head = TreeNodeInitWithVector(values);
    levelOrder(head);
    std::cout << sumOfLeftLeaves(head) << std::endl;
    return 0;
}