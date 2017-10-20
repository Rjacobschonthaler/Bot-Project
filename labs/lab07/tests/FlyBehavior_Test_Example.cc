// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/FlyBehavior.h"
#include <string.h>

TEST(FlyBehaviorTest, fly) {
  FlyBehavior my_flybehavior;
  string expect_str="Generic Flying at 5 mph.";
  EXPECT_EQ(expect_str,my_flybehavior.fly())<< "FAIL: fly function!";
}
