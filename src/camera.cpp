#include "camera.h"


void camera::takePhotos()
{
  if (!runStatus)
    return;

  if (em)
    {
      em->changeConsumptionLevel(this->getName(), CAMERA_TAKING_PHOTOS_ENERGY_CON_RATE);
      em->changeConsumptionRunningStatus(this->getName(), true);
    }

  //taking photos
}

void camera::processPhotos()
{
  if (!runStatus)
    return;

  if (em)
    {
      em->changeConsumptionLevel(this->getName(), CAMERA_PROCESS_PHOTOS_ENERGY_CON_RATE);
      em->changeConsumptionRunningStatus(this->getName(), true);
    }

  //some process
  processStatus = true;
  countProcessed++;
}

unsigned int camera::getCountProcessed() const
{
  return countProcessed;
}

bool camera::getProcessStatus() const
{
  return processStatus;
}

void camera::setProcessStatus(bool value)
{
  processStatus = value;
}

std::ostream& operator<<(std::ostream& os, const camera& cam)
{
  os << "{ " << cam.getName() << " Running State:" << cam.isRunning() << " Processing Status:" << cam.getProcessStatus() << " Count of Processed:" << cam.getCountProcessed() << "}" << std::endl;

  return os;
}
