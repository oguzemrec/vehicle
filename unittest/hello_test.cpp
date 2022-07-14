#include "gmock/gmock.h"
#include "../hello.h"


using namespace ::testing;

class AHello: public Test {
public:
   hello h;
};


TEST_F(AHello, return7Function) {
   ASSERT_THAT(h.return7(), Eq(7u));
}
TEST_F(AHello, return7Function2) {
   ASSERT_THAT(h.return7(), Eq(2u));
}
