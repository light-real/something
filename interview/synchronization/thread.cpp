#include<iostream>
#include<thread>
#include<unistd.h>

/*
һ�����̱���֮���ڱ���ģʽ���������̲��ᱻӰ�죬
����һ���̱߳��������ܵ����������̱�����ϵͳɱ�������Զ����Ҫ�ȶ��߳̽�׳
*/
void function_destroy()
{
    int a = 10 / 0;
    std::cout<<"function_destroy~\n";
}

void function_success()
{
    int a = 10 / 1;
    std::cout<<"function_success~\n";
}


int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        /*
        pid < 0  fork()ʧ�� 
        pid = 0  �ӽ���
        pid > 0  ������
        */
        std::cerr <<"Fork failed!\n";
    }        
    else if(pid == 0)
    {        
        /*
            �ӽ��̵ı�������Ӱ�츸����
        */
    std::thread t1(function_destroy);
    if(t1.joinable())
    {
        t1.join(); 
    }
    std::thread t2(function_success);
    t1.join();
        std::cout<< "child process!\n";
    }
    else{
        int b = 10 / 1; 
        std::cout<<"parent process!\n";
    }

    return 0;
}