//归并排序
#include<iostream>
#include<vector>

using namespace std;
void merge(vector<int> &nums,int left,int mid,int right)
{
    //左数组区间为[left,mid] 右数组区间为[mid+1,right]
    //用一个临时的数组temp来存放合并之后的结果
    vector<int> temp(right-left+1);
    int i = left,j = mid+1,k = 0;
    while(i<=mid && j <= right)
    {
        if(nums[i] < nums[j])
        {
            temp[k++] = nums[i++];
        }
        else
        {
            temp[k++] = nums[j++];
        }
    }
    while(i<=mid)
    {
        temp[k++] = nums[i++];
    }
    while(j<=right)
    {
        temp[k++] = nums[j++];
    }
    //将临时数组赋给nums
    for(k = 0;k<temp.size();k++)
    {
        nums[left + k] = temp[k];
    }
}

void mergesort(vector<int> &nums,int left,int right)
{
    if(left>=right)
    {
        return;
    }
    int mid = (left+right)/2;  //计算中点
    mergesort(nums,left,mid); //分割左数组
    mergesort(nums,mid+1,right);
    merge(nums,left,mid,right);
}

int main()
{
    vector<int> nums = {3,1,8,5,9,3,6,2};
    mergesort(nums,0,nums.size()-1);
    for(auto num : nums)
    {
        cout<<num<<" ";
    }
    cout<<endl;
    return 0;
}