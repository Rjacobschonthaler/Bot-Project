/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/sensor_distress.h"

#ifdef SENSOR_DISTRESS_TEST

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorDistress, Sanity) {
  csci3081::SensorDistress sd;

  bool val = std::is_base_of<csci3081::BaseSensor, csci3081::SensorDistress>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(sd.get_activated(), false);
  EXPECT_EQ(sd.get_range(), 50);
}

Test(SensorDistress, Getters) {
  csci3081::SensorDistress sd;

  EXPECT_EQ(sd.get_range(), 50);
  EXPECT_EQ(&sd.get_robot(), NULL);
}

Test(SensorDistress, Setters) {
  csci3081::SensorDistress sd;

  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  sd.set_robot(&r);
  sd.set_range(100);

  EXPECT_EQ(sd.get_range(), 100);
  EXPECT_EQ(&sd.get_robot(), &r);
}

TEST(SensorDistress, Reset) {
  csci3081::SensorDistress sd;

  sd.activated(true);
  sd.set_range(100);
  EXPECT_EQ(sd.activated(), true);
  EXPECT_EQ(sd.get_range(), 100);

  sd.Reset();
  EXPECT_EQ(sd.activated(), false);
  EXPECT_EQ(sd.get_range(), 50);
}

TEST(SensorDistress, Accept) {
  csci3081::SensorDistress sd;
  csci3081::EventDistressCall dc;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  // Set pos in event
  dc.set_pos(Position(100, 125));

  // Set sensor
  sd.set_robot(&r);
  sd.set_range(50);

  // Test for inside range
  EXPECT_EQ(sd.Accept(&e), 1);

  // Change pos in event to be out of range
  dc.set_pos(Position(100, 200));
  EXPECT_EQ(sd.Accept(&e), 0)

  // Set pos to be on the border of range
  de.set_pos(Position(100, 150));
  EXPECT_EQ(sd.Accept(&e), 0);
}

#endif /* SENSOR_DISTRESS_TEST */
