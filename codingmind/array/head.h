#include<iostream>
#include<vector>
#include<algorithm>
#include<map>
#include<list>
#include<cmath>
#include<climits>

template <class T>
void printVec(std::vector<T> vec)
{
    for(auto u : vec)
    {
        std::cout<<u<<" ";
    }
    std::cout<<std::endl;
}
