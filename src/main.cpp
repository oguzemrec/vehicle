#include <iostream>
#include "sum.h"
#include "hello.h"

int main(int, char**) {

    hello h;
    h.sayHi();
    std::cout << "Sum:  " << sum().getSum(5,5) << "\n";
     std::cout << "Sum 3Param:  " << h.sumThreeParams(5,3,6) << "\n";
}
