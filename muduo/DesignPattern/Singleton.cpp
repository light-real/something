#include "Singleton.h"

// ��̬����instance��ʼ����Ҫ����ͷ�ļ��У��������ļ�����singleton.h������ظ���������
Singleton *Singleton::instance_ = nullptr;
std::mutex Singleton::m_mutex_;