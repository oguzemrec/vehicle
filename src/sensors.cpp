#include "sensors.h"
#include <type_traits>

std::ostream& operator<<(std::ostream& os, const sensorInterface& sensor)
{
  os << "{ " << sensor.name << ": ID: " << static_cast<std::underlying_type_t<sensorID>>(sensor.id) << " Value: " << sensor.getValue() << " is runnig:" << sensor.runStatus << "}";

  return os;
}

