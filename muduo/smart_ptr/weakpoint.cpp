#include<iostream>
#include<memory>

//����weak_ptr����lock�ἶ��shared_ptr

// spL.get() ���ڻ�ȡԭʼָ�� ��ȡԭʼָ���ʱ��һ��Ҫע�� �ܿ��ܻᷢ���ڴ�й©

int main()
{
    std::shared_ptr<int> sp = std::make_shared<int> (10);
    std::weak_ptr<int> wkp = sp;
    std::shared_ptr<int> spL = wkp.lock();
    std::cout<<*spL<<std::endl;
    return 0;
}