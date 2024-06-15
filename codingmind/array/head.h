#include<iostream>
#include<vector>


template <class T>
void printVec(std::vector<T> vec)
{
    for(auto u : vec)
    {
        std::cout<<u<<" ";
    }
    std::cout<<std::endl;
}
