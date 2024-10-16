#include "head.hpp"

// 输入二叉树的前序遍历结果和中序遍历结果，并重建该二叉树 前序和中序中都不含重复的数字
TreeNode *reConstructBinaryTree(std::vector<int> preOrder, std::vector<int> inOrder)
{
    if (preOrder.empty() || inOrder.empty())
        return nullptr;
    TreeNode *root = new TreeNode(preOrder[0]);
    int mid = std::distance(inOrder.begin(), find(inOrder.begin(), inOrder.end(), preOrder[0]));
    std::vector<int> leftPre(preOrder.begin() + 1, preOrder.begin() + mid + 1);
    std::vector<int> rightPre(preOrder.begin() + mid + 1, preOrder.end());
    std::vector<int> leftIn(inOrder.begin(), inOrder.begin() + mid);
    std::vector<int> rightIn(inOrder.begin() + mid + 1, inOrder.end());
    root->left = reConstructBinaryTree(leftPre, leftIn);
    root->right = reConstructBinaryTree(rightPre, rightIn);
    return root;
}

bool ifEqual(const std::vector<int> &postOrder, const std::vector<int> &generate)
{
    for (int i = 0; i < postOrder.size(); i++)
    {
        if (postOrder[i] != generate[i])
        {
            return false;
        }
    }
    return true;
}
int main()
{
    TreeNode *root = createTreeNodeDefault();
    levelOrderTraversal(root);
    std::vector<int> preOrderVec = preOrderTraversal(root);
    std::vector<int> inOrderVec = inOrderTraversal(root);
    std::vector<int> postOrderVec = postOrderTraversal(root);
    // printVec(preOrderVec);
    // printVec(inOrderVec);
    printVec(postOrderVec);
    TreeNode *node = reConstructBinaryTree(preOrderVec, inOrderVec);
    std::vector<int> generate = postOrderTraversal(node);
    std::cout << ifEqual(postOrderVec, generate) << std::endl;
    return 0;
}