#include "head.hpp"

void recursive_Preorder_traversal(TreeNode *node, std::vector<int> &show)
{
    if (node == nullptr)
    {
        return;
    }
    show.push_back(node->val_);
    recursive_Preorder_traversal(node->left, show);
    recursive_Preorder_traversal(node->right, show);
}

void recursive_Inorder_traversal(TreeNode *node, std::vector<int> &show)
{
    if (node == nullptr)
    {
        return;
    }
    recursive_Preorder_traversal(node->left, show);
    show.push_back(node->val_);
    recursive_Preorder_traversal(node->right, show);
}

void recursive_Postorder_traversal(TreeNode *node, std::vector<int> &show)
{
    if (node == nullptr)
    {
        return;
    }
    recursive_Preorder_traversal(node->left, show);
    recursive_Preorder_traversal(node->right, show);
    show.push_back(node->val_);
}

int main()
{
    std::vector<int> show;
    TreeNode *head = TreeNodeInit();
    // recursive_Preorder_traversal(head,show);  //�������
    // recursive_Inorder_traversal(head,show);   //�������
    recursive_Postorder_traversal(head, show); // ��������
    printVec(show);
    return 0;
}