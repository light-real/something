#include<iostream>
#include<thread>
#include<unistd.h>

/*
一个进程崩溃之后，在保护模式下其他进程不会被影响，
但是一个线程崩溃，可能导致整个进程被操作系统杀掉，所以多进程要比多线程健壮
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
        pid < 0  fork()失败 
        pid = 0  子进程
        pid > 0  父进程
        */
        std::cerr <<"Fork failed!\n";
    }        
    else if(pid == 0)
    {        
        /*
            子进程的崩溃不会影响父进程
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