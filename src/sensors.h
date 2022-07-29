#ifndef SENSORS_H
#define SENSORS_H

#include "spi.h"

class sensors
{
private:
    /* data */
    
public:
   spi __spi;
   uint16_t readSpi(const spi& _spi, int channel=1);
    
};



#endif /* SENSORS_H */
