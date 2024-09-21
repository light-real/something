#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <time.h>
#include <thread>
#include <memory>
#include <mutex>
#include <shared_mutex>
/*  
交易市场数据 有工作线程对数据进行读 背景线程对数据进行写
*/

// 公司:<时间,价格>
// map<company,vector<pair<time,value>>>用于存储数据

#define time time_t
#define value int64_t
#define company std::string
class MarketingData
{
public:
    MarketingData();
    MarketingData(const std::map<company, std::vector<std::pair<time, value>>> &cdata);
    MarketingData(const MarketingData &) = delete;            // 删除拷贝构造函数
    MarketingData &operator=(const MarketingData &) = delete; // 删除赋值运算符
    MarketingData(MarketingData &&) noexcept;                 // 移动构造函数 noexcept表示不会抛出异常
    MarketingData &operator=(MarketingData &&) noexcept;      // 移动赋值运算符

    std::map<company, std::vector<std::pair<time, value>>> getData() const; // 读数据
    void printData() const;
    int size() const;
    void insertData(std::string str, std::vector<std::pair<time_t, int64_t>> vec);

private:
    /*
    1. 背景
    在C++中，mutable关键字允许即使在const成员函数中也可以修改某些成员变量。
    通常，const成员函数不能修改对象的成员变量，但有时我们需要在const成员函数中修改某些成员变量，例如用于同步的互斥锁（mutex）。

    2. 问题描述
    在多线程编程中，互斥锁（mutex）用于保护共享资源，防止数据竞争和不一致性。
    然而，如果互斥锁是类的成员变量，并且我们希望在const成员函数中使用它，会遇到问题，因为const成员函数不能修改成员变量。

    3. 解决方案
    为了解决这个问题，我们可以使用mutable关键字。mutable关键字允许我们在const成员函数中修改标记为mutable的成员变量。
    */
    mutable std::mutex mtx;         // 互斥锁
    mutable std::shared_mutex smtx; // 读锁
    std::map<company, std::vector<std::pair<time, value>>> data;
};