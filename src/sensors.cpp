#include "sensors.h"

uint16_t sensors::readSpi( const spi& _spi, int channel)
{
   return _spi.read(channel);
}

