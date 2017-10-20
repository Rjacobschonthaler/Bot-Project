// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/Duck.h"
//#include <iostream>
#include <string.h>

// Initial Test for Mallard Duck display.  YayYay
TEST(MallardTest,display){
  Mallard my_mallard;
  string except_str="I am a Mallard.";
  EXPECT_EQ(except_str,my_mallard.display()) << "FAIL: display" ;
}

// Initial Test for Mallard Duck constructor.  YayYay
TEST(MallardTest,constructor){
  Mallard my_mallard;
  string except_str="Fly with wings at speed of 5 mph.";
  EXPECT_EQ(except_str,my_mallard.performFly()) <<"FAIL: performFly";

  except_str="Quack at 10 decibels.";
  EXPECT_EQ(except_str,my_mallard.performQuack()) <<"FAIL: performQuack";

  FlyWithRocket rocket;
  my_mallard.setFlyBehavior(&rocket);
  except_str="Fly with wings at speed of 20 mph.";
  EXPECT_EQ(except_str,my_mallard.performFly()) <<"FAIL: setFlyBehavior";

  Mute m;
  my_mallard.setQuackBehavior(&m);
  except_str="Cannot talk.";
  EXPECT_EQ(except_str,my_mallard.performQuack()) <<"FAIL: setQuackBehavior";
}
