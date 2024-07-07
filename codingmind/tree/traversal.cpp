#include "head.hpp"


int main()
{
    std::vector<int> show;
    TreeNode *head = TreeNodeInit();
    // recursive_Preorder_traversal(head,show);  //先序遍历
    // recursive_Inorder_traversal(head,show);   //中序遍历
    // recursive_Postorder_traversal(head, show); // 后续遍历
    // Preorder_traversal(head);
    // Inorder_traversal(head);
    // PostOrder_traversal(head);
    // levelOrder(head);
    // levelOrderBottom(head);
    // rightSideView(head);
    averageOfLevels(head);
    // printVec(show);
    return 0;
}