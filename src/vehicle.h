#ifndef VEHICLE_H
#define VEHICLE_H

#include <type_traits>
#include "energymanagament.h"
#include "sensors.h"
#include "camera.h"
#include "movement.h"

class vehicle
{
public:
explicit vehicle();

private:
std::shared_ptr<energyManagament> battery;
std::unique_ptr<movement> _movement;
std::unique_ptr<camera> cam;

std::vector<std::shared_ptr<sensorInterface> > envSensors;
std::vector<std::shared_ptr<sensorInterface> > distanceSensors;

std::shared_ptr<sonar> senSonar;
std::shared_ptr<timeOfFlight> senTimeOfFlight;
std::shared_ptr<infrared> senInfrared;
std::shared_ptr<temperature> senOutTemperature;
std::shared_ptr<temperature> senInTemperature;
std::shared_ptr<humidity> senHumidity;
std::shared_ptr<airPressure> senAirPressure;
std::shared_ptr<outGas> senOutGas;
std::shared_ptr<light> senLight;

enum class runningModes {
  IDLE,
  NORMAL,
  TURBO,
};

enum class modeBatteryLevels {
  IDLE = 0,       // 0 to 29
  NORMAL =30,       //30 to 79
  TURBO =80,       // 80 to 100
};

runningModes mode{ runningModes::IDLE };
unsigned int distanceSensorOrder = 0;

//[low,high)
template <typename T, typename U>
bool isInBounds(const T& value, const U& low, const U& high)
{
  return !(value < static_cast<T>(low)) && (value < static_cast<T>(high));
}
};

#endif // VEHICLE_H
