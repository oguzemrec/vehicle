#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include "vehicle.h"

vehicle::vehicle()
{
  battery = std::make_shared<energyManagament>();

  _movement = std::make_unique<movement>(battery);

  cam = std::make_unique<camera>(battery);

  senSonar = std::make_shared<sonar>(battery);
  senTimeOfFlight = std::make_shared<timeOfFlight>(battery);
  senInfrared = std::make_shared<infrared>(battery);

  distanceSensors.emplace_back(senSonar);
  distanceSensors.emplace_back(senTimeOfFlight);
  distanceSensors.emplace_back(senInfrared);

  senOutTemperature = std::make_shared<temperature>(sensorID::OUT_TEMPERATURE);
  senInTemperature = std::make_shared<temperature>(sensorID::IN_TEMPERATURE);
  senAirPressure = std::make_shared<airPressure>(sensorID::AIR_PRESSURE);
  senHumidity = std::make_shared<humidity>(sensorID::HUMIDITY);
  senOutGas = std::make_shared<outGas>(sensorID::OUT_GAS);
  senLight = std::make_shared<light>(sensorID::LIGHT);

  envSensors.emplace_back(senOutTemperature);
  envSensors.emplace_back(senInTemperature);
  envSensors.emplace_back(senAirPressure);
  envSensors.emplace_back(senHumidity);
  envSensors.emplace_back(senOutGas);
  envSensors.emplace_back(senLight);

  std::thread stateMachine(&vehicle::run, this);
  stateMachine.join();
}

[[noreturn]] void vehicle::run()
{

  auto info = [&]()
  {
    std::cout << "Running Mode:" << static_cast<int>(mode) << std::endl;
    std::cout << *battery << std::endl
              << *_movement << std::endl
              << *cam << std::endl;

    for (auto const &s : distanceSensors)
      std::cout << *s << std::endl;

    for (auto const &s : envSensors)
      std::cout << *s << std::endl;

    std::cout << std::endl
              << std::flush;
  };

  std::mutex io_mutex; // io, etc..
  int camTakingPhotosCount{0};
  int infoCount{0};
  double batteryLevel {0};
  while (true)
  {
    std::unique_lock lock(io_mutex);
    
    batteryLevel = battery->getBatteryLevel();
    // mode checking
    if (isInBounds(batteryLevel, modeBatteryLevels::IDLE, modeBatteryLevels::NORMAL) && mode != runningModes::IDLE) // IDLE Mode
    {
      mode = runningModes::IDLE;

      // Disable distance sensors , moving and camera
      for (auto const &s : distanceSensors)
        s->setRunning(false);

      _movement->stop();

      cam->setRunning(false);
    }
    else if (isInBounds(batteryLevel, modeBatteryLevels::NORMAL, modeBatteryLevels::TURBO) && mode != runningModes::NORMAL) // Normal Mode
    {
      mode = runningModes::NORMAL;

      for (auto const &s : distanceSensors)
        s->setRunning(true);

      _movement->move(50);

      cam->setRunning(true);
    }
    else if (batteryLevel >= static_cast<double>(modeBatteryLevels::TURBO) && mode != runningModes::TURBO)
    {
      mode = runningModes::TURBO;

      for (auto const &s : distanceSensors)
        s->setRunning(true);

      _movement->move(100);

      cam->setRunning(true);
    }

    // Read Distance Sensors by one by: can't run in IDLE mode
    // Take photos or process
    if (!(runningModes::IDLE == mode))
    {
      distanceSensors.at(distanceSensorOrder)->setRunning(false);

      if (++distanceSensorOrder == 3)
        distanceSensorOrder = 0;
      distanceSensors.at(distanceSensorOrder)->setRunning(true);
      distanceSensors.at(distanceSensorOrder)->read();

      cam->takePhotos();
      camTakingPhotosCount++;
      if (camTakingPhotosCount == 100)
      {

        camTakingPhotosCount = 0;
        cam->processPhotos();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cam->setProcessStatus(false);
      }
    }

    // Read All Enviroment Sensors
    for (auto const &s : envSensors)
      s->read();

    if (infoCount++ == 100)
    {
      infoCount = 0;
      info();
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
}