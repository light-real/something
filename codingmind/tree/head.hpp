#include "/root/file/codingmind/stackAndQueue/head.hpp"

class TreeNode
{
public:
    TreeNode(int val) : val_(val)
    {
    }
    ~TreeNode() = default;

    TreeNode *left;
    TreeNode *right;
    int val_;
};

TreeNode *TreeNodeInit()
{
    TreeNode *head = new TreeNode(1);
    TreeNode *node1 = new TreeNode(2);
    TreeNode *node2 = new TreeNode(3);
    TreeNode *node3 = new TreeNode(4);
    TreeNode *node4 = new TreeNode(5);
    TreeNode *node5 = new TreeNode(6);
    TreeNode *node6 = new TreeNode(7);
    TreeNode *node7 = new TreeNode(8);
    // TreeNode *node8 = new TreeNode(9);
    // TreeNode *node9 = new TreeNode(10);

    head->left = node1;
    head->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->right = node5;
    node4->left = node6;
    node4->right = node7;

    return head;
}

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

std::vector<int> Preorder_traversal(TreeNode *head)  //非递归先序遍历
{

    std::vector<int> result;
    if (!head)
    {
        return result;
    }
    std::stack<TreeNode *> sta;
    sta.push(head);
    while (!sta.empty())
    {
        TreeNode *node = sta.top();
        sta.pop();
        result.push_back(node->val_);
        if (node->right)
        {
            sta.push(node->right);
        }
        if (node->left)
        {
            sta.push(node->left);
        }
    }
    printVec(result);
    return result;
}

std::vector<int> Inorder_traversal(TreeNode* head) //非递归中序遍历
{
    std::vector<int> result;
    if(!head)
    {
        return result;
    }
    std::stack<TreeNode*> sta;
    TreeNode* node = head;
    while(!sta.empty() || node)
    {
        if(node)
        {
            sta.push(node);
            node = node->left;  //左
        }
        else
        {
            node = sta.top();
            sta.pop();
            result.push_back(node->val_);
            node = node->right;
        }
    }
    printVec(result);
    return result;
}

std::vector<int> PostOrder_traversal(TreeNode* head)
{
    std::vector<int> result;
    if(!head)
    {
        return result;
    }
    std::stack<TreeNode*> sta;
    sta.push(head);
    while(!sta.empty())
    {
        TreeNode* node = sta.top();
        sta.pop();
        result.push_back(node->val_);
        if(node->left)
        {
            sta.push(node->left);
        }
        if(node->right)
        {
            sta.push(node->right);
        }
    }
    std::reverse(result.begin(),result.end());
    printVec(result);
    return result;
}
