#include <signal.h>
// #include "BankServer.h"
#include "EchoServer.h"

// 1������2��15���źš�
// 2�����źŴ�������ֹͣ�����¼�ѭ���͹����̡߳�
// 3��������������˳���

EchoServer *bankserver;

void Stop(int sig)    // �ź�2��15�Ĵ�������������ֹͣ�������
{
    printf("sig=%d\n",sig);
    // ����BankServer::Stop()ֹͣ����
    bankserver->Stop();
    printf("bankserver has stop\n");
    delete bankserver;
    printf("delete bankserver\n");
    exit(0); 
}

int main(int argc,char *argv[])
{
    if (argc != 3) 
    { 
        printf("usage: ./bankserver ip port\n"); 
        printf("example: ./bankserver 192.168.0.65 5085\n\n"); 
        return -1; 
    }

    signal(SIGTERM,Stop);    // �ź�15��ϵͳkill��killall����Ĭ�Ϸ��͵��źš�
    signal(SIGINT,Stop);        // �ź�2����Ctrl+C���͵��źš�

    bankserver=new EchoServer(argv[1],atoi(argv[2]),3,2);
    bankserver->Start();

    return 0;
}
