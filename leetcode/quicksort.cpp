#include<iostream>
#include<vector>
#include<sstream>
#include<string>

int i = 0;

int partition(std::vector<int> &nums,int left,int right)
{
    std::cout<<"this is the "<<i++<<" partition : ";
    int i = left;
    int j = right;
    int temp = nums[left];
    while(i < j)
    {
        while(i<j && nums[j] >= temp)
            j--;
        if(i<j)
            nums[i++] = nums[j];
        while(i<j && nums[i] < temp)
            i++;
        if(i<j)
            nums[j--] = nums[i];
    }
    nums[i] = temp;
    for(int i = 0;i<nums.size();i++)
    {
        std::cout<<nums[i]<<" ";
    }
    std::cout<<std::endl;
    return i;
}

void quicksort(std::vector<int> &nums,int left,int right)
{
    if(left >= right)
    {
        return ;
    }
    int pivot = partition(nums,left,right);
    quicksort(nums,left,pivot-1);
    quicksort(nums,pivot+1,right);
}

int main()
{
    std::string str; //用于接收输入
    std::getline(std::cin,str);
    std::istringstream iss(str);
    int num;
    std::vector<int> vec;
    while(iss>>num)
    {
        vec.push_back(num);
    }
    quicksort(vec,0,vec.size()-1);
    std::cout<<"------------"<<std::endl;
    for(int i = 0;i<vec.size();i++)
    {
        std::cout<<vec[i]<<" ";
    }
    std::cout<<std::endl;
    return 0;
}
