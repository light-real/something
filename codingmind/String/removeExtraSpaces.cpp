#include "head.hpp"

void removeExtraSpaces(std::string& str)
{
    int i = 0;
    int size_ = str.size();
    int start = 0;
    int end = 0;
    while(i < size_)
    {
        if(str[i] == ' ')
        {
            i++;
        }
        else if(str[i] != ' ' && str[i-1] == ' ')
        {
            start = i;
            i++;
        }
        else if(i+1 < size_ &&str[i] != ' ' && str[i+1] == ' ')
        {
            reverseString(str,start,i);
            start = i;
            i++;
        }
        else
        {
            i++;    
        }
    }
    reverseString(str,start,i);
    std::cout<<str<<std::endl;
}

int main()
{
    std::string str = "the sky is blue";
    std::cout<<str<<std::endl;
    removeExtraSpaces(str);
    return 0;
}