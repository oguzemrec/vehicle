#include "movement.h"
#include "memory.h"


movement::movement(const std::shared_ptr<energyManagament> &_em)
:em{_em}
{

  tracks.emplace_back(std::make_unique<track>(1, trackDirection::DIR_SIDE));
  tracks.emplace_back(std::make_unique<track>(2, trackDirection::DIR_SIDE));
  tracks.emplace_back(std::make_unique<track>(3, trackDirection::DIR_FRONT));
  tracks.emplace_back(std::make_unique<track>(4, trackDirection::DIR_FRONT));

  if (em)
    for (auto const& t: tracks)
      em->insertConsumption(t->getName(), 0, 0);
}

void movement::move(unsigned int id, unsigned int speed) const
{
  const auto& t = tracks.at(id-1);

  t->setSpeed(speed);

  if (em)
    {
      t->setRunningState(true);
      em->changeConsumptionLevel(t->getName(), TRACK_ENERGY_CON_RATE * speed);
      em->changeConsumptionRunningStatus(t->getName(), true);
    }
}

void movement::move(unsigned int speed)
{
  for (auto const& t: tracks)
    {
      t->setSpeed(speed);
      t->setRunningState(true);
      em->changeConsumptionLevel(t->getName(), TRACK_ENERGY_CON_RATE * speed);
      em->changeConsumptionRunningStatus(t->getName(), true);
    }
}

void movement::stop(unsigned int id) const
{
  const auto& t = tracks.at(id-1);

  t->setSpeed(0);

  if (em)
    {
      t->setRunningState(false);
      em->changeConsumptionLevel(t->getName(), 0);
      em->changeConsumptionRunningStatus(t->getName(), false);
    }
}

void movement::stop()
{
  for (auto const& t: tracks)
    {
      t->setSpeed(0);
      t->setRunningState(false);
      em->changeConsumptionLevel(t->getName(), 0);
      em->changeConsumptionRunningStatus(t->getName(), false);
    }
}

track::track(unsigned int _id, trackDirection _dir)
: id{_id},
dir{_dir}
{

  name = "Track" + std::to_string(this->id);
}

unsigned int track::getSpeed() const
{
  return speed;
}

void track::setSpeed(unsigned int value)
{
  if (value <= 0)
    {
      speed = 0;
      return;
    }
  speed = value;
  double duty = PWM_RESOLUTION / speed;

  motor.setPWMDutyCycle(duty);
}

std::ostream& operator<<(std::ostream& os, const movement& mv)
{
  for (auto const& t: mv.tracks)
    {
      os << "{ " << t->getName() << ": Speed:" << t->getSpeed() << " Running State:" << t->getRunningState() << "}" << std::endl;
    }

  return os;
}

