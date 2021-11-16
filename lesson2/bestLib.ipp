#include <stdio.h>
#include <string>

#pragma once
inline int printBest(int str)
{
    std::cout << str << " - THE BEST" << std::endl;
    return 0;
}

//inline не нужен в реализации (cpp) и в шаблонных функциях.
//space