#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//����ouch��ͨ������sig���ݽ������ź�������Ӧ��
void ouch(int sig)
{
 printf("signal %d\n", sig);
 //�ָ��ն��ж��ź�SIGINT��Ĭ����Ϊ
 (void) signal(SIGINT, SIG_DFL);
}
int main()
{
  //�ı��ն��ж��ź�SIGINT��Ĭ����Ϊ��ʹִ֮��ouch����
  (void) signal(SIGINT, ouch);
 
  while(1)
  {
   printf("Hello World!\n");
   sleep(1); 
  }
 return 0;
}