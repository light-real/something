/*
合并两颗二叉树
*/

#include "head.hpp"

TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2)
{
    if (!root1)
        return root2; // 如果root1为空 直接返回root2
    if (!root2)
        return root1; // 如果root1为空 直接返回root2

    root1->val_ += root2->val_;
    root1->left = mergeTrees(root1->left, root2->left);
    root1->right = mergeTrees(root1->right, root2->right);

    return root1;
}

int main()
{
    std::vector<int> values1 = {1, 2, 3, 4, 5};
    std::vector<int> values2 = {1, 2, 3, 4, 5};
    TreeNode *root1 = TreeNodeInitWithVector(values1);
    TreeNode *root2 = TreeNodeInitWithVector(values2);
    root1 = mergeTrees(root1, root2);
    levelOrder(root1);
    return 0;
}
