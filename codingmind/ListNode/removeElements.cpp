#include"head.h"

int main()
{
    std::vector<int> vec = {1,2,3,4,5};
    ListNode<int>* head = ListNodeInit(vec);
    printListNode(head);
    deleteListNode(head);
    return 0;
}