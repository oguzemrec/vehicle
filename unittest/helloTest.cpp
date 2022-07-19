#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "../src/hello.h"
#include <memory>

using namespace ::testing;

class HelloTest : public Test
{
public:
   std::unique_ptr<hello> hi;

   virtual void SetUp() override
   {
      hi = std::make_unique<hello>();
   }
};

TEST_F(HelloTest, Is3ParamSumFunctionEqualStraightSum)
{

  EXPECT_THAT(hi->sumThreeParams(4,5,6), Eq((3+5+6)));

}
TEST_F(HelloTest, return7Function2)
{
   ASSERT_THAT(hi->return7(), Eq(7u));
}
