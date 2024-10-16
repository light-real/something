#include "Buffer.h"
#include <cstdint>
#include <cstring>

Buffer::Buffer(uint16_t sep):sep_(sep)
{
    
}

Buffer::~Buffer()
{
    
}

void Buffer::append(const char *data,size_t size)  //������׷�ӵ�buf_��
{
    buf_.append(data,size);
}

void Buffer::appendwithsep(const char *data,size_t size) //������׷�ӵ�buf_�� ���ӱ��ķָ���
{
    if(sep_ == 0)  //û�зָ���
    {
        buf_.append(data,size); //����������
    }
    else if(sep_ == 1) //���ֽڵı�ͷ
    {   
        buf_.append((char*)&size,4); //�����ĳ���
        buf_.append(data,size);
    }
}

void Buffer::erase(size_t pos,size_t nn) //��buf_��pos��ʼ ɾ��nn���ֽ� pos��0��ʼ
{
    buf_.erase(pos,nn);
}

size_t Buffer::size() //����buf_�Ĵ�С
{
    return buf_.size();
}

const char *Buffer::data() //����buf_���׵�ַ
{
    return buf_.data();
}

void Buffer::clear() //���buf_
{
    buf_.clear();
}

bool Buffer::pickmessage(std::string &ss) //��buf_�в�ֳ�һ������ �����ss�� ���buf_��û�б��� ����false
{
    if(buf_.size()==0)
    {
        return false;
    }
    
    if(sep_ == 0)
    {
        ss = buf_;
        buf_.clear();
    }
    else if(sep_ == 1)
    {
        int len;
        memcpy(&len, buf_.data(),4);//��buf_�л�ȡ����ͷ��
        if(buf_.size()< len+4)  //���buf_�е�������С�ڱ���ͷ�� ˵��buf_�еı������ݲ�����
        {
            return false;
        }
        ss = buf_.substr(4,len); //��buf_�л�ȡһ������
        buf_.erase(0,len+4);
    }
    return true;
}