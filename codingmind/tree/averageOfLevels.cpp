#include "head.hpp"

std::vector<double> averageOfLevels(TreeNode *head)
{
    std::queue<TreeNode *> que;
    std::vector<double> result;
    if (head)
    {
        que.push(head);
    }
    while (!que.empty())
    {
        int size = que.size();
        int sum = 0;
        for (int i = 0; i < size; i++)
        {
            TreeNode *node = que.front();
            que.pop();
            sum += node->val_;
            if(node->left)
            {
                que.push(node->left);
            }
            if(node->right)
            {
                que.push(node->right);
            }
        }
        double cal = (double)sum / size;
        result.push_back(cal);
    }
    printVec(result);
    return result;
}

int main()
{
    TreeNode* head = TreeNodeInit();
    averageOfLevels(head);
    return 0;
}