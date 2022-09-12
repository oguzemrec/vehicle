#ifndef ENERGYMANAGAMENT_H
#define ENERGYMANAGAMENT_H

#include <thread>
#include <chrono>
#include <iostream>
#include <map>

class energyManagament
{
public:
energyManagament();

void insertConsumption(const std::string& name, double consumptionLevel, bool runningState);
void changeConsumptionLevel(const std::string& name, double consumptionLevel);
void changeConsumptionRunningStatus(const std::string& name, bool runningState);

double getBatteryLevel() const;

friend std::ostream& operator<<(std::ostream& os, const energyManagament& em);

private:

std::mutex batterLevelMutex;  // protects batteryLevel data

double batteryLevel{ 80 };

constexpr void accumulateEnergyLevel(double value);
const double sunEnergyPerc = 0.1; //sun panels generated energy percantage for per second
const double windEnergyPerc = 0.01; //propellar generated energy percantage for per second

std::map<std::string, std::pair<double, bool> > consumptionMap; //Name, <energyConsLevel, runningState>
};


#endif // ENERGYMANAGAMENT_H
