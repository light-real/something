#include<iostream>
#include<vector>

using namespace std;

string decimal(int n)
{
    string str = "";
    while(n > 0)
    {
        str = to_string(n % 2) + str;
        n /= 2;
    }
    cout<<str<<endl;
    return str;
}


int main()
{
    string str1 = decimal(1);
    string str2 = decimal(4);
    int size1 = str1.size();
    int size2 = str2.size();
    
    int ret = 1 ^ 4;
    string str = to_string(ret);
    cout<<"str = "<<str<<endl;
    cout<<str2<<endl;
    vector<int> vec = {1,2,3,4,5,6};
    // int n = vec.size();
    // vec.resize(2 * n,1);
    // for(int i = 0;i<vec.size();i++)
    // {
    //     cout<<vec[i]<<" ";
    // }
    // cout<<endl;
    return 0;
}