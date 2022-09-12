#ifndef SENSORS_H
#define SENSORS_H

#include <string>
#include <memory.h>
#include "energymanagament.h"

#define SONAR_ENERGY_CON_RATE 0.003
#define INFRARED_ENERGY_CON_RATE 0.001
#define TIME_OF_FLIGHT_CON_RATE 0.002

enum class sensorID {
  SONAR =1,
  INFRARED,
  TIME_OF_FLIGHT,
  OUT_TEMPERATURE,
  IN_TEMPERATURE,
  HUMIDITY,
  AIR_PRESSURE,
  OUT_GAS,
  LIGHT,
};


class sensorInterface
{
public:
virtual void read()const = 0;
virtual double getValue() const = 0;

virtual void setRunning(bool value)
{
  runStatus = value;
};

bool isRunning() const
{
  return runStatus;
};

std::string getName() const
{
  return name;
};

sensorID getId() const
{
  return id;
};

friend std::ostream& operator<<(std::ostream& os, const sensorInterface& em);

protected:
bool runStatus = false;

std::string name;
sensorID id { 0 };
};


class temperature : public sensorInterface
{
public:
temperature(sensorID _id)
{
  id = _id;

  if (sensorID::OUT_TEMPERATURE == id)
    name = "Outside Temperature";
  else if (sensorID::IN_TEMPERATURE == id)
    name = "Inside Temperature";
};
void read() const
{
};
double getValue() const
{
  return temperatureValue;
};
private:
double temperatureValue;
};

class sonar : public sensorInterface
{
public:
sonar(const std::shared_ptr<energyManagament> &_em)
{
  name = "Sonar";
  id = sensorID::SONAR;
  em = _em;

  if (em)
    em->insertConsumption(this->getName(), SONAR_ENERGY_CON_RATE, true);
};

virtual void read() const override
{
};
virtual double getValue() const override
{
  return distance;
};
virtual void setRunning(bool value) override
{
  runStatus = value;
  if (em)
    em->changeConsumptionRunningStatus(this->getName(), runStatus);
};
private:
double distance;

std::shared_ptr<energyManagament> em;
};
class infrared : public sensorInterface
{
public:
infrared(const std::shared_ptr<energyManagament> &_em)
{
  name = "Infrared";
  id = sensorID::INFRARED;
  em = _em;

  if (em)
    em->insertConsumption(this->getName(), INFRARED_ENERGY_CON_RATE, true);
};

virtual void read() const override
{
};
virtual double getValue() const override
{
  return distance;
};
virtual void setRunning(bool value) override
{
  runStatus = value;
  if (em)
    em->changeConsumptionRunningStatus(this->getName(), runStatus);
};
private:
double distance;

std::shared_ptr<energyManagament> em;
};

class timeOfFlight : public sensorInterface
{
public:
timeOfFlight(const std::shared_ptr<energyManagament> &_em)
{
  name = "Time-of-Flight";
  id = sensorID::TIME_OF_FLIGHT;
  em = _em;

  if (em)
    em->insertConsumption(this->getName(), TIME_OF_FLIGHT_CON_RATE, true);
};

virtual void read() const override
{
};
virtual double getValue() const override
{
  return distance;
};
virtual void setRunning(bool value) override
{
  runStatus = value;
  if (em)
    em->changeConsumptionRunningStatus(this->getName(), runStatus);
};

private:
double distance;

std::shared_ptr<energyManagament> em;
};

#endif // SENSORS_H
