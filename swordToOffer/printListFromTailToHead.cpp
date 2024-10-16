#include "head.hpp"

// 从尾到头打印链表

std::vector<ListNode *> printListFromTailToHead(ListNode *head)
{
    std::vector<ListNode *> vec;
    while (head)
    {
        vec.push_back(head);
        head = head->next;
    }
    std::reverse(vec.begin(), vec.end());
    for (auto &u : vec)
    {
        std::cout << u->val << " ";
    }
    std::cout << std::endl;
    return vec;
}

int main()
{
    ListNode *head = createListNodeDefault();
    printListFromTailToHead(head);
    return 0;
}