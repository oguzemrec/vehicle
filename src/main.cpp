#include <iostream>
#include "sum.h"
#include "hello.h"
#include "sensors.h"
int main(int, char**) {

    hello h;
    h.sayHi();

    sensors sensor;
    std::cout << "Sum:  " << sum().getSum(5,5) << "\n";
     std::cout << "Sum 3Param:  " << h.sumThreeParams(5,3,6) << "\n";

      std::cout << "Sensor Spi Param Channel 2s " << sensor.readSpi(sensor.__spi) << "\n";
}
