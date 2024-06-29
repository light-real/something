/*
移除元素 移除数组中所有等于val的元素 并且返回移除之后的数组
*/

#include "head.hpp"

template <class T, class ele>
T removeElement(T &elements, const ele &val)
{
    int left = 0;  // 用于标记elements[left] == val元素 用于覆盖的下标
    int right = 0; // 不等于val的元素
    int size_ = elements.size();
    while (right < size_)
    {
        if (elements[right] != val)
        {
            elements[left++] = elements[right];
        }
        right++;
    }
    elements.resize(left);
    return elements;
}

int main()
{
    int i = 3;
    // std::vector<int> vec = {1, 2, 3, 4, 5, 6};
    std::string str = " you are the best ";
    // printVec(vec);
    std::cout<<str<<std::endl;
    removeElement(str, ' ');
    // printVec(vec);
    std::cout<<str<<std::endl;
    return 0;
}
