/*
����һ������n���������������һ��������s �ҳ����������������>=s�ĳ�����С������������ �������䳤��
eg:
    ���룺s = 7 nums = [2,3,1,2,4,3];
    �����2
    ���ͣ�������[4,3]�Ǹ������³�����С��������
*/

#include "head.h"

int minSubArrayLen(const std::vector<int> &vec, int s) // �����ⷨ
{
    int result = INT_MAX;
    int sum = 0;
    int sublen = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        sum = 0;
        for (int j = i; j < vec.size(); j++)
        {
            sum += vec[j];
            if (sum >= s)
            {
                sublen = j - i + 1;
                result = result <= sublen ? result : sublen;
                break;
            }
        }
    }
    return result == INT_MAX ? 0 : result;
}

int main()
{
    int s = 7;
    std::vector<int> vec = {2, 3, 1, 2, 4, 3};
    int ans = minSubArrayLen(vec,s);
    std::cout<<ans<<std::endl;
    return 0;
}