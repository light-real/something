// ����ͨѶ�Ŀͻ��˳���
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
�����ͻ��ˣ�����IP��ص���Ϣ������IP��ַ�Ͷ˿ںţ����ӷ�������������Ϣ
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
    servaddr.sin_family = AF_INET;                 // ָ��ʹ��ipv4��ַ
    servaddr.sin_addr.s_addr = inet_addr(argv[1]); // inet_addr������ip��ַ���ַ���ת��Ϊ�����ֽ��������
    servaddr.sin_port = htons(atoi(argv[2]));
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) // connect�����ɹ�����0 ʧ�ܷ���-1
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
        // todo �洢Ǳ�ڵ��ڴ���������� ���buf�Ĵ�С����1020��tmpbuf����װ����buf����������
        char tmpbuf[1024]; // ��ʱ��buffer ����ͷ��+��������
        memset(tmpbuf, 0, sizeof(tmpbuf));
        int len = strlen(buf);        // ���㱨�ĵĴ�С
        memcpy(tmpbuf, &len, 4);      // ƴ�ӱ���ͷ��
        memcpy(tmpbuf + 4, buf, len); // ƴ�ӱ�������
        // �����ǽ����ĳ���д����ǰ�ĸ��ֽ�
        send(sockfd, tmpbuf, len + 4, 0); // �������ķ��͸������� send(sockfd,buf,len,flags)ͨ����־λ����Ϊ0
        recv(sockfd, &len, 4, 0);         // �ȶ�ȡ4�ֽڵı���ͷ��
        memset(buf, 0, sizeof(buf));
        recv(sockfd, buf, len, 0);
    }
    printf("time of ending:%ld\n", time(0));
    return 0;
}