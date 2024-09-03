#include "Buffer.h"
#include <cstdint>
#include <cstring>

Buffer::Buffer(uint16_t sep):sep_(sep)
{
    
}

Buffer::~Buffer()
{
    
}

void Buffer::append(const char *data,size_t size)  //把数据追加到buf_中
{
    buf_.append(data,size);
}

void Buffer::appendwithsep(const char *data,size_t size) //把数据追加到buf_中 附加报文分隔符
{
    if(sep_ == 0)  //没有分隔符
    {
        buf_.append(data,size); //处理报文内容
    }
    else if(sep_ == 1) //四字节的报头
    {   
        buf_.append((char*)&size,4); //处理报文长度
        buf_.append(data,size);
    }
}

void Buffer::erase(size_t pos,size_t nn) //从buf_的pos开始 删除nn个字节 pos从0开始
{
    buf_.erase(pos,nn);
}

size_t Buffer::size() //返回buf_的大小
{
    return buf_.size();
}

const char *Buffer::data() //返回buf_的首地址
{
    return buf_.data();
}

void Buffer::clear() //清空buf_
{
    buf_.clear();
}

bool Buffer::pickmessage(std::string &ss) //从buf_中拆分出一个报文 存放在ss中 如果buf_中没有报文 返回false
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
        memcpy(&len, buf_.data(),4);//从buf_中获取报文头部
        if(buf_.size()< len+4)  //如果buf_中的数据量小于报文头部 说明buf_中的报文内容不完整
        {
            return false;
        }
        ss = buf_.substr(4,len); //从buf_中获取一个报文
        buf_.erase(0,len+4);
    }
    return true;
}