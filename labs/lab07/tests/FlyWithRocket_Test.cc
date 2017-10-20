// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/FlyBehavior.h"
#include <string.h>

TEST(FlyWithRocketTest, fly) {
  FlyWithRocket my_rocket;
  string expect_str="Fly with wings at speed of 20 mph.";
  EXPECT_EQ(expect_str,my_rocket.fly())<< "FAIL: fly";
}
