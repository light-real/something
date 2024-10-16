#pragma once
#include <cstddef>
#include <cstdint>
#include <string>
#include <cstring>
#include <iostream>

class Buffer
{
private:
    std::string buf_; //���ڴ������
    const uint16_t sep_; //���ķָ��� 0-�޷ָ���(�̶����� ��Ƶ�����) 1-���ֽڵı�ͷ 2-"\r\n\r\n"�ָ���(httpЭ��)
public:
    Buffer(uint16_t sep=1);
    ~Buffer();
    void append(const char *data,size_t size);  //������׷�ӵ�buf_��
    void appendwithsep(const char *data,size_t size); //������׷�ӵ�buf_�� ���ӱ��ķָ���
    void erase(size_t pos,size_t nn); //��buf_��pos��ʼ ɾ��nn���ֽ� pos��0��ʼ
    size_t size(); //����buf_�Ĵ�С
    const char *data(); //����buf_���׵�ַ
    void clear(); //���buf_
    bool pickmessage(std::string &ss); //��buf_�в�ֳ�һ������ �����ss�� ���buf_��û�б��� ����false
};