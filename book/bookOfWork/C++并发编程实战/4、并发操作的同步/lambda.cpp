#include <iostream>
#include <algorithm>
#include <string>


using namespace std;


int main()
{
    int local_variable = 10;
    int x = 19;
    auto result = [=,&x](int &out)->int{  //(int &out)��ʾ�����Ĳ��� Ҳ������ʱ��Ҫ����Ĳ���
        x = 29;
        out = x;
        return x + local_variable;
    };
    int out = 0;
    result(out);
    cout<<"result = "<<out<<endl;
    return 0;
}

//g++ -std=c++11 -o main lambda.cpp