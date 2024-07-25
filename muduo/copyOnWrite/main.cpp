#include "copyOnWrite.h"

std::mutex mmtx;

MarketingData init()
{
    std::map<std::string, std::vector<std::pair<time_t, int64_t>>> dataMap;
    dataMap["meituan"] = {{2024, 100}, {2023, 120}};
    dataMap["tengxun"] = {{2024, 200}};
    MarketingData md{dataMap};
    // md.printData();
    md.insertData("alibaba", {{2022, 300}});
    // md.printData();
    return md;
}

void workThread(const MarketingData &md) // 工作线程用于读取数据
{
    std::map<std::string, std::vector<std::pair<time_t, int64_t>>> workData = md.getData();
    {
        std::lock_guard<std::mutex> lock(mmtx);
        std::cout << "workThread is running" << std::endl;
    }
}

void backGroundThread(MarketingData &md,const std::string& str,const std::vector<std::pair<time_t,int64_t>>& vec) // 背景线程用于写线程
{
    md.insertData(str, vec);
    {
        std::lock_guard<std::mutex> lock(mmtx);
        std::cout << "backGroundThread is running" << std::endl;
    }
}

void callThread(MarketingData &md)
{
    int workThreadNums = 10; // 创建十个线程读
    std::vector<std::thread> workThreadVector;
    for (int i = 0; i < workThreadNums; i++)
    {
        workThreadVector.emplace_back(workThread, std::ref(md));
    }

    // 等待所有读线程完成
    for (auto &thread : workThreadVector)
    {
        thread.join();
    }

    int backgroundThreadNums = 5; //创建五个线程写
    std::string str = "huya";
    std::vector<std::pair<time_t,int64_t>> vec = {{2019,99}};
    std::thread backgroundThread01(backGroundThread,std::ref(md),str,vec);
    backgroundThread01.join();
}

int main()
{
    MarketingData md = init(); // 不能使用默认的拷贝构造和移动构造函数 因为mtx和smtx无法被复制
    callThread(md);
    md.printData();
    return 0;
}

//todo 加入线程池进行优化 
//todo 连接数据库
//todo 加入网络模块 能够将数据从数据库中读取并且发出
//todo IO多路复用