#include<iostream>
#include<memory>

//enable_shared_from_this

class Bad
{
public:
    std::shared_ptr<Bad> getptr()
    {
        return std::shared_ptr<Bad> (this);  //�����൱���´�����һ������ 
    }

    ~Bad()
    {
        std::cout<<"Bad destruct"<<std::endl;
    }
};

int main()
{
    std::shared_ptr<Bad> spb (new Bad());
    std::shared_ptr<Bad> spl = spb->getptr();
    //����ָ���ԭʼָ����һ���� ָ�����ͬһ���ڴ�
    std::cout<<"spb : "<<spb.get()<<std::endl;   //spb : 0x55dba3b5ceb0
    std::cout<<"spl : "<<spl.get()<<std::endl;   //spl : 0x55dba3b5ceb0
    std::cout<<"spb.use_count() = "<<spb.use_count()<<std::endl;
    std::cout<<"spl.use_count() = "<<spl.use_count()<<std::endl;
    return 0;
}