// ���ֲ���
/*����һ�� n ��Ԫ������ģ������������� nums ��һ��Ŀ��ֵ target
дһ���������� nums �е� target�����Ŀ��ֵ���ڷ����±꣬���򷵻� -1
*/

#include <iostream>
#include <vector>

using namespace std;

int search(const vector<int> &vec, int target)
{
    int i = 0;
    int j = vec.size();
    while (i <= j)
    {
        int mid = i + (j - i) / 2;
        if (vec[mid] == target)
        {
            return mid;
        }
        else if (vec[mid] < target)
        {
            i = mid + 1;
        }
        else
        {
            j = mid - 1;
        }
    }
    return -1;
}

int main()
{
    vector<int> vec = {1, 2, 3, 4, 5, 6, 8, 9};
    cout<<search(vec,10)<<endl;
    return 0;
}