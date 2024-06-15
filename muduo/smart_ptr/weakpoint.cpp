#include<iostream>
#include<memory>

//尝试weak_ptr进行lock提级成shared_ptr

// spL.get() 用于获取原始指针 获取原始指针的时候一定要注意 很可能会发生内存泄漏

int main()
{
    std::shared_ptr<int> sp = std::make_shared<int> (10);
    std::weak_ptr<int> wkp = sp;
    std::shared_ptr<int> spL = wkp.lock();
    std::cout<<*spL<<std::endl;
    return 0;
}