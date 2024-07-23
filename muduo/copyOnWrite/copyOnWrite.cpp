#include "copyOnWrite.h"

MarketingData::MarketingData()
{
}

MarketingData::MarketingData(const std::map<company, std::vector<std::pair<time, value>>> &cdata) : data(cdata)
{
}
std::map<company, std::vector<std::pair<time, value>>> MarketingData::getData() const
{
    std::lock_guard<std::shared_mutex> lock(smtx);
    return data;
}

int MarketingData::size() const
{
    return data.size();
}

void MarketingData::printData() const
{
    std::lock_guard<std::mutex> lock(mtx);
    for (auto it = data.begin(); it != data.end(); it++)
    {
        std::cout << "company : " << it->first << std::endl;
        for (auto itv = it->second.begin(); itv != it->second.end(); itv++)
        {
            std::cout << "time : " << itv->first << std::endl;
            std::cout << "value : " << itv->second << std::endl;
            if (itv == it->second.begin() + it->second.size() - 1)
            {
                continue;
            }
            std::cout << "-----year gap -----" << std::endl;
        }
        std::cout << std::endl;
        // std::cout << "-----next company -----" << std::endl;
    }
}

void MarketingData::insertData(std::string str, std::vector<std::pair<time_t, int64_t>> vec)
{
    if (size() == 0) // 如果此时没有数据 那么不用对数据进行拷贝 直接插入
    {
        std::lock_guard<std::mutex> lock(mtx);
        data.insert({std::make_pair(str, vec)});
        return;
    }

    std::map<std::string, std::vector<std::pair<time_t, int64_t>>> newdata = data;
    newdata.insert({std::make_pair(str, vec)});
    {
        std::lock_guard<std::mutex> lock(mtx);
        data = newdata;
    }
}

MarketingData::MarketingData(MarketingData &&other) noexcept // 移动构造函数 noexcept表示不会抛出异常
{
    std::unique_lock lock(other.mtx);
    data = std::move(other.data);
}

MarketingData &MarketingData::operator=(MarketingData &&other) noexcept // 移动赋值运算符
{
    if (this != &other)
    {
        std::unique_lock llock(mtx, std::defer_lock); // std::defer_lock表示构造的时候先不加锁
        std::unique_lock rlock(mtx, std::defer_lock);
        std::lock(llock, rlock); // 同时加锁 避免死锁
        data = std::move(other.data);
    }
    return *this;
}