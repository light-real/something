#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>
#include <queue>
#include <iomanip>
#include <cmath>
#include <stack>

void printVec(const std::vector<int> &vec)
{
    for (auto &u : vec)
    {
        std::cout << u << " ";
    }
    std::cout << std::endl;
}

void print2DVec(const std::vector<std::vector<int>> &vec)
{
    for (auto &u : vec)
    {
        printVec(u);
    }
}

std::vector<std::vector<int>> default2DArray()
{
    std::vector<std::vector<int>> array = {
        {1, 2, 8, 9},
        {2, 4, 9, 12},
        {4, 7, 10, 13},
        {6, 8, 11, 15}};
    return array;
}
std::vector<std::vector<int>> input2DArray(int m, int n) // 构建一个mxn的二维数组
{
    std::vector<std::vector<int>> array(m, std::vector<int>(n, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cin >> array[i][j];
        }
    }
    return array;
}

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode *createListNodeWithVector(std::vector<int> &vec)
{
    ListNode *head = new ListNode(vec[0]);
    ListNode *cur = head;
    for (int i = 1; i < vec.size(); i++)
    {
        cur->next = new ListNode(vec[i]);
        cur = cur->next;
    }
    return head;
}

ListNode *createListNodeDefault()
{
    ListNode *head = new ListNode(1);
    ListNode *cur = head;
    cur->next = new ListNode(2);
    cur = cur->next;
    cur->next = new ListNode(3);
    cur = cur->next;
    cur->next = new ListNode(4);
    cur = cur->next;
    cur->next = new ListNode(5);
    return head;
}

class TreeNode
{
public:
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode *createTreeNodeDefault()
{
    TreeNode *root = new TreeNode(1);
    TreeNode *node2 = new TreeNode(2);
    TreeNode *node3 = new TreeNode(3);
    TreeNode *node4 = new TreeNode(4);
    TreeNode *node5 = new TreeNode(5);
    TreeNode *node6 = new TreeNode(6);
    TreeNode *node7 = new TreeNode(7);
    TreeNode *node8 = new TreeNode(8);
    TreeNode *node9 = new TreeNode(9);
    root->left = node2;
    root->right = node3;
    node2->left = node4;
    node2->right = node5;
    node3->left = node6;
    node3->right = node7;
    node4->left = node8;
    node4->right = node9;
    return root;
}

// 计算二叉树的深度
int getDepth(TreeNode *root)
{
    if (!root)
        return 0;
    return std::max(getDepth(root->left), getDepth(root->right)) + 1;
}

void levelOrderTraversal(TreeNode *root)
{
    if (!root)
    {
        return;
    }

    int depth = getDepth(root); // 获取树的深度
    std::queue<TreeNode *> q;
    q.push(root);

    int maxWidth = std::pow(2, depth - 1) + 1; // 这里表示最后一层应该占据的空格数 如depth = 2 -> 3,3 -> 7
    int currentDepth = 1;
    while (!q.empty())
    {
        int size = q.size();
        int levelSpace = maxWidth / size; // 当前层的空格宽度

        for (int i = 0; i < size; i++)
        {
            TreeNode *node = q.front();
            q.pop();
            int repeatCount = currentDepth == depth ? 1 : levelSpace / 2;
            std::string space(repeatCount, ' ');
            if (currentDepth == depth)
            {
                std::cout << node->val << space;
            }
            else
            {
                std::cout << space << node->val << space;
            }
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
        currentDepth++;
        std::cout << std::endl;
    }
}

std::vector<int> preOrderTraversal(TreeNode *root)
{

    if (!root)
        return {};
    std::vector<int> res;
    std::stack<TreeNode *> s;
    while (!s.empty() || root)
    {
        while (root)
        {
            res.push_back(root->val);
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        root = root->right;
    }
    return res;
}

std::vector<int> inOrderTraversal(TreeNode *root)
{
    std::vector<int> res;
    if (!root)
        return res;
    std::stack<TreeNode *> s;
    while (!s.empty() || root)
    {
        while (root)
        {
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        res.push_back(root->val);
        root = root->right;
    }
    return res;
}

std::vector<int> postOrderTraversal(TreeNode *root)
{
    std::vector<int> res;
    std::stack<TreeNode *> s;
    TreeNode *cur = root;
    TreeNode *pre;

    while (cur)
    {
        s.push(cur);
        cur = cur->left;
    }
    while (!s.empty())
    {
        cur = s.top();
        if (cur->right == nullptr || cur->right == pre)
        {
            res.push_back(cur->val);
            pre = cur;
            s.pop();
        }
        else
        {
            // 访问右孩子
            cur = cur->right;
            while (cur)
            {
                s.push(cur);
                cur = cur->left;
            }
        }
    }
    return res;
}
