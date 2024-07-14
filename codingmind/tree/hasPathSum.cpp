/*
给你二叉树的根节点 root 和一个表示目标和的整数 targetSum
判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于目标和 targetSum
如果存在，返回 true ；否则，返回 false
*/

#include "head.hpp"

bool hasPathSum(TreeNode *root, int targetSum)
{
    if (root == nullptr)
        return false;
    std::stack<std::pair<TreeNode *, int>> st; // 用pair去记录 第一个元素为当前节点的值 第二个元素为当前节点路径和
    st.push(std::pair<TreeNode *, int>(root, root->val_));
    while (!st.empty())
    {
        std::pair<TreeNode *, int> node = st.top();
        st.pop();
        if (node.first->left == nullptr && node.first->right == nullptr && node.second == targetSum)
        {
            return true;
        }
        if (node.first->left)
        {
            st.push(std::pair<TreeNode *, int>(node.first->left, node.second + node.first->left->val_));
        }
        if (node.first->right)
        {
            st.push(std::pair<TreeNode *, int>(node.first->right, node.second + node.first->right->val_));
        }
    }
    return false;
}

int main()
{
    int target = 15;
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *head = TreeNodeInitWithVector(values);
    levelOrder(head);
    std::cout << "result = " << hasPathSum(head, target) << std::endl;
    return 0;
}