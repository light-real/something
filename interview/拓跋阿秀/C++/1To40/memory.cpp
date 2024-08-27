#include <iostream>
#include <string>

struct Info
{
    uint8_t a;
    uint16_t b;
    uint8_t c;
};

struct alignas(4) Info2
{
    uint8_t a;
    uint16_t b;
    uint8_t c;
};

void printMemory(const Info& info,const Info2& info2)
{
    std::cout<<"Info's memory showtime:"<<std::endl;
    std::cout<<&info.a<<std::endl;
    std::cout<<"-"<<&info.b<<"-"<<info.c<<std::endl;
    std::cout<<"Info2's memory showtime:"<<std::endl;
    std::cout<<info2.a<<"-"<<&info2.b<<"-"<<info2.c<<std::endl;
}

int main()
{
    Info info{67,2,68};
    Info2 info2{97,2,98};
    printMemory(info,info2);
    return 0;
}
