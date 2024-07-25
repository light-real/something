/*
根据中序遍历和后序遍历构建树
*/

#include "head.hpp"

// 每次递归定义了新的vector 性能并不好
//  TreeNode *traversal(std::vector<int> Inorder, std::vector<int> Postorder)
//  {
//      // 后序遍历数组最后一个元素 就是当前的中间节点
//      int rootValue = Postorder[Postorder.size() - 1];
//      TreeNode *root = new TreeNode(rootValue);

//     // 叶子结点
//     if (Postorder.size() == 1)
//     {
//         return root;
//     }

//     // 找到中序遍历的切割点
//     int delimiterIndex;
//     for (delimiterIndex = 0; delimiterIndex < Inorder.size(); delimiterIndex++)
//     {
//         if (Inorder[delimiterIndex] == rootValue)
//             break;
//     }

//     // 切割中序数组
//     // 左闭右开
//     std::vector<int> leftInorder(Inorder.begin(), Inorder.begin() + delimiterIndex);
//     std::vector<int> rightInorder(Inorder.begin() + delimiterIndex + 1, Inorder.end());

//     Postorder.resize(Postorder.size()-1); //舍弃末尾元素

//     //切割后序数组
//     //使用左中序数组大小作为切割点
//     std::vector<int> leftPostorder(Postorder.begin(),Postorder.begin()+leftInorder.size());
//     std::vector<int> rightPostorder(Postorder.begin()+leftInorder.size(),Postorder.end());

//     root->left = traversal(leftInorder,leftPostorder);
//     root->right = traversal(rightInorder,rightPostorder);

//     return root;
// }

// 每次递归不创建vector 使用下标来标记
// end也即size
TreeNode *traversal(std::vector<int> Inorder, int InorderBegin, int InorderEnd, std::vector<int> PostOrder, int PostorderBegin, int PostorderEnd)
{
    if (PostorderBegin == PostorderEnd)
        return nullptr;
    int rootValue = PostOrder[PostorderEnd - 1];
    TreeNode *root = new TreeNode(rootValue);

    if (PostOrder.size() == 1)
        return root; // 如果只有一个节点 那么目前就是叶子节点

    // 后序数组的末尾即是根节点 使用根节点去划分中序数组
    int delimiterIndex;
    for (delimiterIndex = InorderBegin; delimiterIndex < InorderEnd; delimiterIndex++)
    {
        if (Inorder[delimiterIndex] == rootValue)
            break;
    }

    // 切割中序数组 左闭右开 相当于leftInorderEnd那个位置左数组是到不了的
    int leftInorderBegin = InorderBegin;
    int leftInorderEnd = delimiterIndex;
    int rightInorderBegin = delimiterIndex + 1;
    int rightInorderEnd = PostorderEnd;

    // 找到了中序数组的划分 分割后序数组
    int leftPostorderBegin = PostorderBegin;
    int leftPostorderEnd = PostorderBegin + delimiterIndex - InorderBegin; // 加上左数组的大小
    int rightPostorderBegin = PostorderBegin + delimiterIndex - InorderBegin;
    int rightPostorderEnd = PostorderEnd -1;

    root->left = traversal(Inorder, leftInorderBegin, leftInorderEnd, PostOrder, leftPostorderBegin, leftPostorderEnd);
    root->right = traversal(Inorder, rightInorderBegin, rightInorderEnd, PostOrder, rightPostorderBegin, rightPostorderEnd);

    return root;
}

int main()
{
    std::vector<int> Inorder = {9, 3, 15, 20, 7};
    std::vector<int> Postorder = {9, 15, 7, 20, 3};
    TreeNode *root = traversal(Inorder, 0, Inorder.size(), Postorder, 0, Postorder.size());
    levelOrder(root);
    return 0;
}