#include "head.hpp"

void removeDuplicates(std::string& str)
{
    if(str == " ")
    {
        return ;
    }
    std::stack<char> sta;
    sta.push(str[0]);
    int i = 1;
    char temp;
    while(i < str.size())
    {
        if(sta.empty())
        {
            sta.push(str[i]);
            i++;
            continue;
        }
        temp  = sta.top();
        if(temp == str[i])
        {
            sta.pop();
            i++;
            continue;
        }
        sta.push(str[i]);
        i++;
    }
    str = "";
    while(!sta.empty())
    {
        temp = sta.top();
        sta.pop();
        str += temp;
    }
    std::reverse(str.begin(),str.end());
}


int main()
{
    std::string str;
    std::cin>>str;
    std::cout<<"input str = "<<str<<std::endl;
    removeDuplicates(str);
    std::cout<<"output str = "<<str<<std::endl;
    return 0;
}