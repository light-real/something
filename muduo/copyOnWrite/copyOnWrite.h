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
�����г����� �й����̶߳����ݽ��ж� �����̶߳����ݽ���д
*/

// ��˾:<ʱ��,�۸�>
// map<company,vector<pair<time,value>>>���ڴ洢����

#define time time_t
#define value int64_t
#define company std::string
class MarketingData
{
public:
    MarketingData();
    MarketingData(const std::map<company, std::vector<std::pair<time, value>>> &cdata);
    MarketingData(const MarketingData &) = delete;            // ɾ���������캯��
    MarketingData &operator=(const MarketingData &) = delete; // ɾ����ֵ�����
    MarketingData(MarketingData &&) noexcept;                 // �ƶ����캯�� noexcept��ʾ�����׳��쳣
    MarketingData &operator=(MarketingData &&) noexcept;      // �ƶ���ֵ�����

    std::map<company, std::vector<std::pair<time, value>>> getData() const; // ������
    void printData() const;
    int size() const;
    void insertData(std::string str, std::vector<std::pair<time_t, int64_t>> vec);

private:
    /*
    1. ����
    ��C++�У�mutable�ؼ�������ʹ��const��Ա������Ҳ�����޸�ĳЩ��Ա������
    ͨ����const��Ա���������޸Ķ���ĳ�Ա����������ʱ������Ҫ��const��Ա�������޸�ĳЩ��Ա��������������ͬ���Ļ�������mutex����

    2. ��������
    �ڶ��̱߳���У���������mutex�����ڱ���������Դ����ֹ���ݾ����Ͳ�һ���ԡ�
    Ȼ�����������������ĳ�Ա��������������ϣ����const��Ա������ʹ���������������⣬��Ϊconst��Ա���������޸ĳ�Ա������

    3. �������
    Ϊ�˽��������⣬���ǿ���ʹ��mutable�ؼ��֡�mutable�ؼ�������������const��Ա�������޸ı��Ϊmutable�ĳ�Ա������
    */
    mutable std::mutex mtx;         // ������
    mutable std::shared_mutex smtx; // ����
    std::map<company, std::vector<std::pair<time, value>>> data;
};