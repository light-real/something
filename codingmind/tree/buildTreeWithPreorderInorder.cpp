// buildTreeWithPreorderInorder
// 使用前序遍历和中序遍历构建二叉树

#include "head.hpp"

TreeNode *traversal(std::vector<int> PreOrder, int PreOrderBegin, int PreOrderEnd, std::vector<int> InOrder, int InOrderBegin, int InOrderEnd)
{
    if (PreOrderBegin == PreOrderEnd)
        return nullptr; // 相当于空节点

    int rootValue = PreOrder[PreOrderBegin]; // 因为需要递归，所有不要用0 使用PreOrderBegin
    TreeNode *root = new TreeNode(rootValue);

    if (PreOrderEnd - PreOrderBegin == 1)
        return root; // 如果是叶子节点了 直接返回root

    // 找到根节点在中序数组中的位置
    int delimiterInder;
    for (delimiterInder = InOrderBegin; delimiterInder < InOrderEnd; delimiterInder++)
    {
        if (InOrder[delimiterInder] == rootValue)
            break;
    }

    // 使用根节点去切割中序数组
    int leftInorderBegin = InOrderBegin;
    int leftInorderEnd = delimiterInder;
    int rightInorderBegin = delimiterInder + 1;
    int rightInorderEnd = InOrderEnd;

    // 根据中序数组去切割前序数组
    int leftPreorderBegin = PreOrderBegin + 1;
    int leftPreorderEnd = PreOrderBegin + 1 + delimiterInder - InOrderBegin;
    int rightPreorderBegin = PreOrderBegin + 1 + delimiterInder - InOrderBegin;
    int rightPreorderEnd = PreOrderEnd;

    root->left = traversal(PreOrder, leftPreorderBegin, leftPreorderEnd, InOrder, leftInorderBegin, leftInorderEnd);
    root->right = traversal(PreOrder, rightPreorderBegin, rightPreorderEnd, InOrder, rightInorderBegin, rightInorderEnd);

    return root;
}

int main()
{
    std::vector<int> Preorder = {3, 9, 20, 15, 7};
    std::vector<int> Inorder = {9, 3, 15, 20, 7};
    TreeNode *root = traversal(Preorder, 0, Preorder.size(), Inorder, 0, Inorder.size());
    levelOrder(root);
    return 0;
}