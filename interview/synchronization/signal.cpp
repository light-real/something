#include <stdio.h>
#include <signal.h>
#include <unistd.h>

//函数ouch对通过参数sig传递进来的信号作出响应。
void ouch(int sig)
{
 printf("signal %d\n", sig);
 //恢复终端中断信号SIGINT的默认行为
 (void) signal(SIGINT, SIG_DFL);
}
int main()
{
  //改变终端中断信号SIGINT的默认行为，使之执行ouch函数
  (void) signal(SIGINT, ouch);
 
  while(1)
  {
   printf("Hello World!\n");
   sleep(1); 
  }
 return 0;
}