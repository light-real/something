/*
输出二叉树的路径 从根节点到叶子节点
*/

#include "head.hpp"

std::vector<std::string> pathofTree(TreeNode *head)
{
    std::stack<TreeNode *> treest;   // 用于存储节点
    std::stack<std::string> pathst;  // 用于存储当前的路径
    std::vector<std::string> result; // 用于存储结果
    if (head == nullptr)
    {
        return result;
    }
    treest.push(head);
    pathst.push(std::to_string(head->val_));
    while (!treest.empty())
    {
        TreeNode *node = treest.top();
        treest.pop();
        std::string path = pathst.top();
        pathst.pop();
        if (node->left == nullptr && node->right == nullptr)
        {
            result.push_back(path);
        }
        if (node->right)
        {
            treest.push(node->right);
            pathst.push(path + "->" + std::to_string(node->right->val_));
        }
        if (node->left)
        {
            treest.push(node->left);
            pathst.push(path + "->" + std::to_string(node->left->val_));
        }
    }
    printVec(result);
    return result;
}

int main()
{
    std::vector<int> values = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    TreeNode *head = TreeNodeInitWithVector(values);
    pathofTree(head);
    return 0;
}