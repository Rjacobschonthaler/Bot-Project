// Google Test Framework
#include <gtest/gtest.h>
// Project code from the ../src directory
#include "../src/Duck.h"
//#include <iostream>
#include <string.h>

// Initial Test for Rubber Duck display.  YayYay
TEST(RubberDuckTest,display){
  RubberDuck rubberduckie;
  string except_str="I am a Rubber Duck.";
  EXPECT_EQ(except_str,rubberduckie.display()) << "FAIL: display" ;
}

// Initial Test for Rubber Duck constructor.  YayYay
TEST(RubberDuckTest,constructor){
  RubberDuck rubberduckie;
  string except_str="Cannot fly.";
  EXPECT_EQ(except_str,rubberduckie.performFly()) <<"FAIL: performFly";

  except_str="Quack at 2 decibels.";
  EXPECT_EQ(except_str,rubberduckie.performQuack()) <<"FAIL: performQuack";

  FlyWithRocket rocket;
  rubberduckie.setFlyBehavior(&rocket);
  except_str="Fly with wings at speed of 20 mph.";
  EXPECT_EQ(except_str,rubberduckie.performFly()) <<"FAIL: setFlyBehaviorFly";

  Mute m;
  rubberduckie.setQuackBehavior(&m);
  except_str="Cannot talk.";
  EXPECT_EQ(except_str,rubberduckie.performQuack()) <<"FAIL: setQuackBehavior";
}
