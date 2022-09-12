#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <memory>
#include "energymanagament.h"

constexpr double CAMERA_TAKING_PHOTOS_ENERGY_CON_RATE = 0.0001;
constexpr double CAMERA_PROCESS_PHOTOS_ENERGY_CON_RATE = 0.001;

class camera
{
public:
explicit camera(const std::shared_ptr<energyManagament> &_em):
em {_em}
{


  if (em)
    em->insertConsumption(this->getName(), CAMERA_TAKING_PHOTOS_ENERGY_CON_RATE, false);
}
void setRunning(bool value)
{
  runStatus = value;

  if (runStatus)
    em->changeConsumptionRunningStatus(this->getName(), true);
  else
    em->changeConsumptionRunningStatus(this->getName(), false);
};

bool isRunning() const
{
  return runStatus;
};

std::string getName() const
{
  return name;
};

void takePhotos() const;
void processPhotos();

unsigned int getCountProcessed() const;

bool getProcessStatus() const;
void setProcessStatus(bool value);

friend std::ostream& operator<<(std::ostream& os, const camera& em);
private:
const std::string name = "Camera";
bool runStatus = false;
bool processStatus = false;
std::shared_ptr<energyManagament> em;

unsigned int countProcessed{ 0 };
};
#endif // CAMERA_H
