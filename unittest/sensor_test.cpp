#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/sensors.h"
#include "../src/spi.h"
#include <memory>

using namespace ::testing;

class spiMock : public spi
{

public:
    MOCK_METHOD(uint16_t, read, (int channel), (const,override));
};

class sensorTestF : public Test
{
public:
    std::unique_ptr<sensors> sensor;
    spiMock _spi;
    virtual void SetUp() override
    {
        sensor = std::make_unique<sensors>();
    }
};


TEST_F(sensorTestF, does_read_value_return_0)
{
  EXPECT_CALL(_spi, read(_)).WillOnce(Return(1));

  EXPECT_THAT(sensor->readSpi(_spi, 1), Eq(1u));

}
