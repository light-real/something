/*
根据中序遍历和后序遍历构建树
*/

#include "head.hpp"

TreeNode *traversal(std::vector<int> Inorder, std::vector<int> Postorder)
{
    // 后序遍历数组最后一个元素 就是当前的中间节点
    int rootValue = Postorder[Postorder.size() - 1];
    TreeNode *root = new TreeNode(rootValue);

    // 叶子结点
    if (Postorder.size() == 1)
    {
        return root;
    }

    // 找到中序遍历的切割点
    int delimiterIndex;
    for (delimiterIndex = 0; delimiterIndex < Inorder.size(); delimiterIndex++)
    {
        if (Inorder[delimiterIndex] == rootValue)
            break;
    }

    // 切割中序数组
    // 左闭右开
    std::vector<int> leftInorder(Inorder.begin(), Inorder.begin() + delimiterIndex);
    std::vector<int> rightInorder(Inorder.begin() + delimiterIndex + 1, Inorder.end());

    Postorder.resize(Postorder.size()-1); //舍弃末尾元素

    //切割后序数组
    //使用左中序数组大小作为切割点
    std::vector<int> leftPostorder(Postorder.begin(),Postorder.begin()+leftInorder.size());
    std::vector<int> rightPostorder(Postorder.begin()+leftInorder.size(),Postorder.end());

    root->left = traversal(leftInorder,leftPostorder);
    root->right = traversal(rightInorder,rightPostorder);

    return root;
}



int main()
{
    std::vector<int> Inorder = {9, 3, 15, 20, 7};
    std::vector<int> Postorder = {9, 15, 7, 20, 3};
    TreeNode* root = traversal(Inorder,Postorder);
    levelOrder(root);
    return 0;
}