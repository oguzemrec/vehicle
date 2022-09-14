#include "energymanagament.h"

energyManagament::energyManagament()
{
  std::thread batteryManagament(&energyManagament::run, this);
  batteryManagament.detach();
}

[[noreturn]] void energyManagament::run()
{
  while (true)
  {
    std::unique_lock lock(batterLevelMutex);

    accumulateEnergyLevel(sunEnergyPerc + windEnergyPerc);

    for (const auto &[name, consumption] : consumptionMap)
    {
      if (consumption.second)
      {
        batteryLevel -= consumption.first;
      }
      if (batteryLevel < 0)
        batteryLevel = 0;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(250));
  }
}

void energyManagament::insertConsumption(const std::string &name, double consumptionLevel, bool runningState)
{
  std::pair<double, bool> p1{consumptionLevel, runningState};

  consumptionMap.try_emplace(name, std::move(p1));
}

void energyManagament::changeConsumptionLevel(const std::string &name, double consumptionLevel)
{
  consumptionMap[name].first = consumptionLevel;
}

void energyManagament::changeConsumptionRunningStatus(const std::string &name, bool runningState)
{
  consumptionMap[name].second = runningState;
}

double energyManagament::getBatteryLevel() const
{
  return batteryLevel;
}

constexpr void energyManagament::accumulateEnergyLevel(double value)
{
  if (batteryLevel + value >= 100)
    batteryLevel = 100;
  else
    batteryLevel += value;
}

std::ostream &operator<<(std::ostream &os, const energyManagament &em)
{
  os << "Battery Level: " << em.getBatteryLevel() << std::endl
     << "Battery Constuption Map: " << std::endl;

  for (const auto &[name, consumption] : em.consumptionMap)
  {
    if (consumption.second)
      os << name << ": " << consumption.first << std::endl;
  }

  return os;
}
