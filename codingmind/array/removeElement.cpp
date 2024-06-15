/*
����һ������ nums ��һ��ֵ val������Ҫ ԭ�� �Ƴ�������ֵ���� val ��Ԫ�أ��������Ƴ���������³��ȡ�

��Ҫʹ�ö��������ռ䣬������ʹ�� O(1) ����ռ䲢ԭ���޸��������顣

Ԫ�ص�˳����Ըı䡣�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

ʾ�� 1: ���� nums = [3,2,2,3], val = 3, ����Ӧ�÷����µĳ��� 2, ���� nums �е�ǰ����Ԫ�ؾ�Ϊ 2�� 
�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

ʾ�� 2: ���� nums = [0,1,2,2,3,0,4,2], val = 2, ����Ӧ�÷����µĳ��� 5, ���� nums �е�ǰ���Ԫ��Ϊ 0, 1, 3, 0, 4��

�㲻��Ҫ���������г����³��Ⱥ����Ԫ��
*/

#include"head.h"

using namespace std;

int removeElement(const vector<int>& vec,int target)
{
    int count = 0;
    for(int i = 0;i<vec.size();i++)
    {
        if(vec[i] == target)
        {
            count++;
        }
    }
    return vec.size()-count;
}

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 8, 9};
    cout<<removeElement(vec,1)<<endl;
}
