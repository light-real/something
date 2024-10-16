// 网络通讯的客户端程序
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/types.h>


/*
整个客户端：做好IP相关的信息，输入IP地址和端口号，连接服务器，发送消息
*/
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("exampple:./client 192.168.184.128 5085\n");
        return -1;
    }
    int sockfd;
    struct sockaddr_in servaddr;
    char buf[1024];
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("socket() failed.\n");
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;                 // 指定使用ipv4地址
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); // inet_addr将包含ip地址的字符串转换为网络字节序的整数
    servaddr.sin_port = htons(atoi(argv[2]));
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) // connect函数成功返回0 失败返回-1
    {
        printf("connect(%s:%s) failed", argv[1], argv[2]);
        close(sockfd);
        return -1;
    }
    printf("connect ok.\n");
    printf("time of beginning:%ld\n", time(0));
    for (int i = 0; i < 1; i++)
    {
        memset(buf, 0, sizeof(buf));
        sprintf(buf, "This is the %d supergirl!", i);
        // todo 存储潜在的内存溢出的问题 如果buf的大小超过1020，tmpbuf存在装不下buf的数据问题
        char tmpbuf[1024]; // 临时的buffer 报文头部+报文内容
        memset(tmpbuf, 0, sizeof(tmpbuf));
        int len = strlen(buf);        // 计算报文的大小
        memcpy(tmpbuf, &len, 4);      // 拼接报文头部
        memcpy(tmpbuf + 4, buf, len); // 拼接报文内容
        // 这里是将报文长度写进了前四个字节
        send(sockfd, tmpbuf, len + 4, 0); // 将请求报文发送给服务器 send(sockfd,buf,len,flags)通常标志位设置为0
        recv(sockfd, &len, 4, 0);         // 先读取4字节的报文头部
        memset(buf, 0, sizeof(buf));
        recv(sockfd, buf, len, 0);
    }
    printf("time of ending:%ld\n", time(0));
    return 0;
}