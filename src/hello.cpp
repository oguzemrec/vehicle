#include <iostream>
#include "hello.h"

void hello::sayHi()
{
    std::cout << "Hii"<< "\n";
}
int hello::return7()
{
    return 7;
}

int hello::sumThreeParams(int a, int b, int c)
{
    return sum(a,sum(b,c));
}

int hello::sum(int a, int b)
{
    return a+b;
}
