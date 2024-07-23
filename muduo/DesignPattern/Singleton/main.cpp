#include <iostream>
#include "Singleton.h"

int main()
{
    Singleton *s1 = Singleton::GetInstance();
    Singleton *s2 = Singleton::GetInstance();

    std::cout << "s1's address : " << s1 << std::endl;
    std::cout << "s2's address : " << s2 << std::endl;
    return 0;
}