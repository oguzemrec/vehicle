#ifndef SPI_H
#define SPI_H

#include "stdint.h"

class spi
{
private:
    /* data */
public:
   // spi(/* args */);
   // ~spi();

   virtual uint16_t read(int channel) const{

    return channel*2;
 };
};





#endif /* SPI_H */
