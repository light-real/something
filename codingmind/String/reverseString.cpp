#include "head.hpp"

void reverseString(std::string& str)
{
    int i = 0;
    int j = str.size();
    while(i<j)
    {
        std::swap(str[i],str[j]);
        i++;
        j--;
    }
    std::cout<<str<<std::endl;
}

int main()
{
    std::string str = "reverseString";
    std::cout<<str<<std::endl;
    reverseString(str);
    return 0;
}