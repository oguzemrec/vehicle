#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <vector>
#include <memory>
#include  "energymanagament.h"

#define PWM_RESOLUTION 4095
#define TRACK_ENERGY_CON_RATE 0.001

enum class trackDirection {
  DIR_SIDE,
  DIR_FRONT,
  DIR_BACK,
};


struct servo {
  void setPWMDutyCycle(double duty)
  {
    dutyCycle = duty;
    //Some MCU operations
  };
  double getPWMDutyCycle()
  {
    return dutyCycle;
  }

private:
  double dutyCycle;
};

class track {
public:

track(unsigned int, trackDirection);
unsigned int getSpeed() const;
void setSpeed(unsigned int value);



std::string getName() const
{
  return name;
}

bool getRunningState() const
{
  return runningState;
}

void setRunningState(bool value)
{
  runningState = value;
}

private:
std::string name;
unsigned int id{ 0 };
servo motor;
unsigned int speed; //percentage 0-100
trackDirection dir;
bool runningState;
};

class movement
{
public:
movement(const std::shared_ptr<energyManagament> &_em);

void move(unsigned int id, unsigned int speed) const;  //for specific motor
void move(unsigned int speed) ;  //for all motors

void stop(unsigned int id) const; // for specific motor
void stop(); //for all motors

friend std::ostream& operator<<(std::ostream& os, const movement& em);

private:

std::vector<std::unique_ptr<track> > tracks;
std::shared_ptr<energyManagament> em;
};




#endif // MOVEMENT_H
