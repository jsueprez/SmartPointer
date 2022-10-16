#include "gtest/gtest.h"
#include "dummyLib.h"

class TestingDummyLib : public ::testing::Test
{
public:
  void SetUp()
  {
  }

  void TearDown()
  {
  }

  DummyLib object;
  int i1 = 2;
  int i2 = 3;
};

TEST_F(TestingDummyLib, dummySum)
{
  EXPECT_EQ(object.dummySum(i1, i2), 5);
}
