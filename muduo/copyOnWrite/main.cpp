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

void workThread(const MarketingData &md) // �����߳����ڶ�ȡ����
{
    std::map<std::string, std::vector<std::pair<time_t, int64_t>>> workData = md.getData();
    {
        std::lock_guard<std::mutex> lock(mmtx);
        std::cout << "workThread is running" << std::endl;
    }
}

void backGroundThread(MarketingData &md,const std::string& str,const std::vector<std::pair<time_t,int64_t>>& vec) // �����߳�����д�߳�
{
    md.insertData(str, vec);
    {
        std::lock_guard<std::mutex> lock(mmtx);
        std::cout << "backGroundThread is running" << std::endl;
    }
}

void callThread(MarketingData &md)
{
    int workThreadNums = 10; // ����ʮ���̶߳�
    std::vector<std::thread> workThreadVector;
    for (int i = 0; i < workThreadNums; i++)
    {
        workThreadVector.emplace_back(workThread, std::ref(md));
    }

    // �ȴ����ж��߳����
    for (auto &thread : workThreadVector)
    {
        thread.join();
    }

    int backgroundThreadNums = 5; //��������߳�д
    std::string str = "huya";
    std::vector<std::pair<time_t,int64_t>> vec = {{2019,99}};
    std::thread backgroundThread01(backGroundThread,std::ref(md),str,vec);
    backgroundThread01.join();
}

int main()
{
    MarketingData md = init(); // ����ʹ��Ĭ�ϵĿ���������ƶ����캯�� ��Ϊmtx��smtx�޷�������
    callThread(md);
    md.printData();
    return 0;
}

//todo �����̳߳ؽ����Ż� 
//todo �������ݿ�
//todo ��������ģ�� �ܹ������ݴ����ݿ��ж�ȡ���ҷ���
//todo IO��·����