#include "head.hpp"

/*
完美二叉树指向下一个右侧节点
*/

class PerfectTreeNode
{
public:
    PerfectTreeNode(int val) : val_(val)
    {
    }
    ~PerfectTreeNode() = default;

    PerfectTreeNode *left;
    PerfectTreeNode *right;
    PerfectTreeNode *next;
    int val_;
};

PerfectTreeNode *PerfectTreeNodeInit()
{
    PerfectTreeNode *head = new PerfectTreeNode(1);
    PerfectTreeNode *node1 = new PerfectTreeNode(2);
    PerfectTreeNode *node2 = new PerfectTreeNode(3);
    PerfectTreeNode *node3 = new PerfectTreeNode(4);
    PerfectTreeNode *node4 = new PerfectTreeNode(5);
    PerfectTreeNode *node5 = new PerfectTreeNode(6);
    PerfectTreeNode *node6 = new PerfectTreeNode(7);
    PerfectTreeNode *node7 = new PerfectTreeNode(8);
    // PerfectTreeNode *node8 = new PerfectTreeNode(9);
    // PerfectTreeNode *node9 = new PerfectTreeNode(10);

    head->left = node1;
    head->right = node2;
    node1->left = node3;
    node1->right = node4;
    node2->left = node5;
    node2->right = node6;
    node3->left = node7;
    return head;
}

std::vector<int> connect(PerfectTreeNode *head)
{
    std::queue<PerfectTreeNode *> que;
    std::vector<int> result;
    if (head)
    {
        que.push(head);
    }
    while (!que.empty())
    {
        int size = que.size();
        PerfectTreeNode *currentHead;
        for (int i = 0; i < size; i++)
        {
            PerfectTreeNode *node = que.front();
            que.pop();
            if (i == 0)
            {
                currentHead = node;
                result.push_back(node->val_);
            }
            else if (i != 0 && i != size - 1)
            {
                currentHead->next = node;
                currentHead = node;
                result.push_back(node->val_);
            }
            if (i == size - 1)
            {
                currentHead->next = nullptr;
                if (i != 0)
                {
                    result.push_back(node->val_);
                }
                result.push_back(-1);
            }
            if (node->left)
            {
                que.push(node->left);
            }
            if (node->right)
            {
                que.push(node->right);
            }
        }
    }
    printVec(result);
    return result;
}

int main()
{
    PerfectTreeNode *head = PerfectTreeNodeInit();
    connect(head);
    return 0;
}