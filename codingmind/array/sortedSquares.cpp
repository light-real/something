/*
��һ�����ǵݼ�˳���������������nums ����ÿ�����ֵ�ƽ����ɵ������� Ҫ��Ҳ���շǵݼ�˳������
*/

#include"head.h"

std::vector<int> sortedSquares(std::vector<int>& vec) //��һ������������
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

std::vector<int> sortedSquares_Twopoint(const std::vector<int>& vec)  //�ڶ���������˫ָ��
{
    int i = 0;
    int j = vec.size()-1;
    int index = j;  //����ָʾansVec���±�
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