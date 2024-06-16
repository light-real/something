/*
给一个按非递减顺序排序的整数数组nums 返回每个数字的平方组成的新数组 要求也按照非递减顺序排序
*/

#include"head.h"

std::vector<int> sortedSquares(std::vector<int>& vec) //第一个方法：排序
{
    std::sort(vec.begin(),vec.end(),[&](int a,int b){
       return abs(a) <= abs(b);
    });
    for(auto &ele :vec)
    {
        ele = pow(ele,2);
    }
    return vec;
}

std::vector<int> sortedSquares_Twopoint(const std::vector<int>& vec)  //第二个方法：双指针
{
    int i = 0;
    int j = vec.size()-1;
    int index = j;  //用于指示ansVec的下标
    std::vector<int> ansVec(vec.size(),0);
    while(i <= j)
    {
        if(abs(vec[i]) <= abs(vec[j]))
        {
            ansVec[index--] = pow(vec[j],2);
            j--;
        }
        else
        {
            ansVec[index--] = pow(vec[i],2);
            i++;
        }
    }
    printVec(ansVec);
    return ansVec;
}

int main()
{
    std::vector<int> vec = {-4,-1,0,3,10};
    
    printVec(vec);
    
    // sortedSquares(vec);
    sortedSquares_Twopoint(vec);
    
    // printVec(vec);
    return 0;
}