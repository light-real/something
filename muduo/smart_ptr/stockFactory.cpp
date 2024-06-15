#include<iostream>
#include<memory>
#include<map>
#include<string>
#include<mutex>

using namespace std;

class stock
{
public:
    explicit stock(const string& k):key(k)  //explicit关键字 用于显式调用构造函数 且只适用于一个参数的构造函数
    {
        
    }

    void printKey() const
    {
        cout<<"stock key : "<<key<<endl;
    }
private:
    string key;
};

class stockFactory
{
public:
    stockFactory() = default;

    shared_ptr<stock> get(const string& key)
    {
        shared_ptr<stock> pstock;
        lock_guard<mutex> lock(mtx_);
        weak_ptr<stock>& wkstock = stocks_[key];  //如果key不存在 会默认构造一个
        pstock = wkstock.lock();  //尝试提升为shared_ptr
        if(!pstock)
        {
            pstock = make_shared<stock>(key);
            wkstock = pstock;
        }
        return pstock;
    }

    int size() const
    {
        return stocks_.size();
    }

private:
    mutable mutex mtx_;  //互斥量  使用mutable关键字 可以在const成员函数中被修改
    map<string,weak_ptr<stock>> stocks_;  
};

int main()
{
    stockFactory factory;
    auto s1 = factory.get("GOOG");
    auto s2 = factory.get("IBM");
    
    auto s3 = factory.get("IBM");
    
    cout<<(s2 == s3)<<endl;  //这个应该是从stockFactory中拿到的 所以返回1
    
    s1->printKey();
    s2->printKey();
    s3->printKey();
    
    cout<<"factory.size() = "<<factory.size()<<endl;
    return 0;
}