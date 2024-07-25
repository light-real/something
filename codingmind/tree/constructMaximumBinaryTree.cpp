// constructMaximumBinaryTree
/*
给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：

二叉树的根是数组中的最大元素。
左子树是通过数组中最大值左边部分构造出的最大二叉树。
右子树是通过数组中最大值右边部分构造出的最大二叉树。
通过给定的数组构建最大二叉树，并且输出这个树的根节点。
*/

#include "head.hpp"

TreeNode *constructMaximumBinaryTree(std::vector<int> &vec)
{
    TreeNode *node = new TreeNode(0);
    // 如果传入的数组大小为1 那么表示叶子节点
    if (vec.size() == 1)
    {
        node->val_ = vec[0];
        return node;
    }

    // 找到最大值确定根节点
    int MaxValue = INT_MIN;
    int MaxValueIndex = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (vec[i] > MaxValue)
        {
            MaxValue = vec[i];
            MaxValueIndex = i;
        }
    }
    node->val_ = MaxValue;

    // 最大值所在下标的左区间 构建左子树
    if (MaxValueIndex > 0)
    {
        std::vector<int> newVec(vec.begin(), vec.begin() + MaxValueIndex);
        node->left = constructMaximumBinaryTree(newVec);
    }

    // 最大值所在下标的右区间 构建右子树
    if (MaxValueIndex < vec.size() - 1)
    {
        std::vector<int> newVec(vec.begin() + MaxValueIndex + 1, vec.end());
        node->right = constructMaximumBinaryTree(newVec);
    }

    return node;
}

int main()
{
    std::vector<int> vec = {3, 2, 1, 6, 0, 5};
    TreeNode *root = constructMaximumBinaryTree(vec);
    levelOrder(root);
    return 0;
}