#include "head.hpp"

//输入一个字符串 一个n 将后n位的字符串移到前面
//eg:
//abcdefg 3
//efgabc

int main()
{
    std::string str = "abcdefg";
    int n = 3;
    std::reverse(str.begin(),str.end());
    std::reverse(str.begin(),str.begin()+n-1);
    std::reverse(str.begin()+n,str.end());
    std::cout<<str<<std::endl;
    return 0;
}