#include "head.hpp"


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