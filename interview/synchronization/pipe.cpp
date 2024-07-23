/*
�����ܵ���ͨ��
pipe()����
*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int fd[2]; // �����ļ�������
    pid_t pid;
    char str[1024] = "hello\n";
    char buf[1024];
    if (pipe(fd) < 0) // �����ܵ����ɹ�����0��ʧ�ܷ���-1
    {
        perror("pipe");
        exit(1);
    }
    pid = fork(); // ����һ���ӽ���
    // ���ܣ���д�Ӷ�
    if (pid > 0) // ������
    {
        close(fd[0]); // �����̹رն���
        sleep(2);
        write(fd[1], str, strlen(str)); // ��ܵ���д����
        wait(NULL); // �����ӽ���
    }
    else if (pid == 0) // �ӽ���
    {
        close(fd[1]); // �ӽ��̹ر�д��
        int len = read(fd[0], buf, sizeof(buf)); // �ӹܵ��������
        write(STDOUT_FILENO, buf, len); // �Ѷ���������д����׼���
    }
    else // �����ӽ���ʧ��
    {
        perror("fork");
        exit(1);
    }
    return 0;
}
