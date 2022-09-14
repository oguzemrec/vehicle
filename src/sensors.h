#ifndef SENSORS_H
#define SENSORS_H

#include <string>
#include <memory>
#include "energymanagament.h"

constexpr double SONAR_ENERGY_CON_RATE = 0.003;
constexpr double INFRARED_ENERGY_CON_RATE = 0.001;
constexpr double TIME_OF_FLIGHT_CON_RATE = 0.002;

enum class sensorID
{
  SONAR = 1,
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
  virtual ~sensorInterface() = default;
  virtual void read() = 0;
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

  friend std::ostream &operator<<(std::ostream &os, const sensorInterface &em);

protected:
  bool runStatus = true;

  std::string name;
  sensorID id{0};
};

class temperature : public sensorInterface
{
public:
  explicit temperature(sensorID _id)
  {
    id = _id;

    if (sensorID::OUT_TEMPERATURE == id)
      name = "Outside Temperature";
    else if (sensorID::IN_TEMPERATURE == id)
      name = "Inside Temperature";
  };

  void read() override
  {
    // some MCU works: SPI, I2C...
  };
  double getValue() const override
  {
    return temperatureValue;
  };

  void setValue(double value)  //test function
  {
    temperatureValue = value;
  }

private:
  double temperatureValue;
};

class humidity : public sensorInterface
{
public:
  explicit humidity(sensorID _id)
  {
    id = _id;

    name = "Humidity";
  };
  void read() override
  {
    // some MCU works: SPI, I2C...
    humidtyLevel = 0;
  };
  double getValue() const override
  {
    return humidtyLevel;
  };

private:
  double humidtyLevel;
};

class airPressure : public sensorInterface
{
public:
  explicit airPressure(sensorID _id)
  {
    id = _id;

    name = "Air Pressure";
  };
  void read() override
  {
    pressureLevel = 0;
    // some MCU works: SPI, I2C...
  };
  double getValue() const override
  {
    return pressureLevel;
  };

private:
  double pressureLevel;
};

class light : public sensorInterface
{
public:
  explicit light(sensorID _id)
  {
    id = _id;

    name = "Light";
  };
  void read() override
  {
    lightLevel = 0;
  };
  double getValue() const override
  {
    return lightLevel;
  };

private:
  double lightLevel;
};

class outGas : public sensorInterface
{
public:
  explicit outGas(sensorID _id)
  {
    id = _id;

    name = "Out Gas";
  };
  void read() override
  {
    outGasLevel = 0;
  };
  double getValue() const override
  {
    return outGasLevel;
  };

private:
  double outGasLevel;
};

class sonar : public sensorInterface
{
public:
  explicit sonar(const std::shared_ptr<energyManagament> &_em)
      : em{_em}
  {
    name = "Sonar";
    id = sensorID::SONAR;

    if (em)
      em->insertConsumption(this->getName(), SONAR_ENERGY_CON_RATE, true);
  };

  void read() override
  {
    distance = 0;
  };
  double getValue() const override
  {
    return distance;
  };
  void setRunning(bool value) override
  {
    runStatus = value;
    if (em)
      em->changeConsumptionRunningStatus(this->getName(), this->isRunning());
  };

private:
  double distance;

  std::shared_ptr<energyManagament> em;
};
class infrared : public sensorInterface
{
public:
  explicit infrared(const std::shared_ptr<energyManagament> &_em)
      : em{_em}
  {
    name = "Infrared";
    id = sensorID::INFRARED;

    if (em)
      em->insertConsumption(this->getName(), INFRARED_ENERGY_CON_RATE, true);
  };

  void read() override
  {
    distance = 0;
  };
  double getValue() const override
  {
    return distance;
  };

  void setRunning(bool value) override
  {
    runStatus = value;
    if (em)
      em->changeConsumptionRunningStatus(this->getName(), this->isRunning());
  };

private:
  double distance;

  std::shared_ptr<energyManagament> em;
};

class timeOfFlight : public sensorInterface
{
public:
  explicit timeOfFlight(const std::shared_ptr<energyManagament> &_em)
      : em{_em}
  {
    name = "Time-of-Flight";
    id = sensorID::TIME_OF_FLIGHT;

    if (em)
      em->insertConsumption(this->getName(), TIME_OF_FLIGHT_CON_RATE, true);
  };

  void read() override
  {
    distance = 0;
  };
  double getValue() const override
  {
    return distance;
  };
  void setRunning(bool value) override
  {
    runStatus = value;
    if (em)
      em->changeConsumptionRunningStatus(this->getName(), this->isRunning());
  };

private:
  double distance;

  std::shared_ptr<energyManagament> em;
};

#endif // SENSORS_H
