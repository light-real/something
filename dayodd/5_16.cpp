#include<iostream>
#include<string>
using namespace std;

string decimaltoBinary(int n)
{
    if(n == 0)
    {
        return "0";
    }
    string binary = "";
    while(n > 0)
    {
        binary = to_string(n % 2) + binary;
        n /= 2;
    }
    return binary;
}
w
int main()
{
    int n = 13;
    string ans = decimaltoBinary(n);
    cout<<"ans = "<<ans<<endl;
    return 0;
}