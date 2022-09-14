#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/sensors.h"
#include <memory>

using namespace ::testing;


class sensorTestF : public Test
{
public:
    std::unique_ptr<temperature> _temperature;
    virtual void SetUp() override
    {
        _temperature = std::make_unique<temperature>(sensorID::IN_TEMPERATURE);
    }
};


TEST_F(sensorTestF, set_value_10_read_10)
{
  _temperature->setValue(10);

  EXPECT_THAT(_temperature->getValue(), Eq(10u));

}
