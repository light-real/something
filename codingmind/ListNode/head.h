#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <cmath>
#include <string>

template <typename T>
class ListNode
{
public:
    T val;
    // int val;
    ListNode *next;

    ListNode() : val(T()), next(nullptr) {}

    ListNode(T val_) : val(val_), next(nullptr)
    {
    }

    ~ListNode() = default;
};

template <typename T>
ListNode<T> *ListNodeInit(const std::vector<T> &vec)
{
    ListNode<T> *pre = new ListNode<T>(-1);
    ListNode<T> *cur = pre;

    for (auto u : vec)
    {
        ListNode<T> *node = new ListNode<T>(u);
        cur->next = node;
        cur = cur->next;
    }

    cur = pre->next;
    delete pre;
    return cur;
}

template <typename T>
void printListNode(ListNode<T> *head)
{
    while (head)
    {
        std::cout << head->val << "->";
        head = head->next;
    }
    std::cout << "nullptr" <<std::endl;
}

template<typename T>
void deleteListNode(ListNode<T> *head)
{
    while(head)
    {
        ListNode<T>* node = head;
        head = head->next;
        delete node;
    }
}