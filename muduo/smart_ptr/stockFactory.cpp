#include<iostream>
#include<memory>
#include<map>
#include<string>
#include<mutex>

using namespace std;

class stock
{
public:
    explicit stock(const string& k):key(k)  //explicit�ؼ��� ������ʽ���ù��캯�� ��ֻ������һ�������Ĺ��캯��
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
        weak_ptr<stock>& wkstock = stocks_[key];  //���key������ ��Ĭ�Ϲ���һ��
        pstock = wkstock.lock();  //��������Ϊshared_ptr
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
    mutable mutex mtx_;  //������  ʹ��mutable�ؼ��� ������const��Ա�����б��޸�
    map<string,weak_ptr<stock>> stocks_;  
};

int main()
{
    stockFactory factory;
    auto s1 = factory.get("GOOG");
    auto s2 = factory.get("IBM");
    
    auto s3 = factory.get("IBM");
    
    cout<<(s2 == s3)<<endl;  //���Ӧ���Ǵ�stockFactory���õ��� ���Է���1
    
    s1->printKey();
    s2->printKey();
    s3->printKey();
    
    cout<<"factory.size() = "<<factory.size()<<endl;
    return 0;
}