// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/QuackBehavior.h"
#include <string.h>

#ifdef FEEDBACK_TEST_03

TEST(SqueakTest, quack) {
  Squeak my_quack;
  string expect_str="Quack at 10 decibels.";
  EXPECT_STREQ(expect_str.c_str(),my_quack.quack().c_str())<<"FAIL: constructor!";
}

#endif
