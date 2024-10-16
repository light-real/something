#pragma once
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>

//ʱ���
class Timestamp
{
private:
    time_t secsinceepoch_; //������ʾ��ʱ�䣨��1970����������ȥ��������
public:
    Timestamp();  //�õ�ǰʱ���ʼ������
    Timestamp(int64_t secsinceepoch); //��һ��������ʾ��ʱ���ʼ������
    static Timestamp now(); //���ص�ǰʱ���Timestamp����
    time_t toint() const; //����������ʾ��ʱ��
    std::string tostring() const; //�����ַ�����ʾ��ʱ�� ��ʽyyyy-mm-dd hh24:mi:ss
};