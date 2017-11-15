/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/sensor_proximity.h"

#ifdef SENSOR_PROXIMITY_TEST

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorProximity, Sanity) {
  csci3081::SensorProximity sp;

  bool val = std::is_base_of<csci3081::BaseSensor, csci3081::SensorProximity>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(sp.get_activated(), false);
  EXPECT_EQ(sp.get_range(), 50);
  EXPECT_EQ(sp.get_field_of_view(), 90);
  EXPECT_EQ(sp.get_robot(), NULL);
}

Test(SensorProximity, Getters) {
  csci3081::SensorProximity sp;

  EXPECT_EQ(sp.get_range(), 50);
  EXPECT_EQ(sp.get_field_of_view(), 90);
  EXPECT_EQ(&sd.get_robot(), NULL);
}

Test(SensorProximity, Setters) {
  csci3081::SensorProximity sp;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  sp.set_robot(&r);
  sp.set_range(100);
  sp.set_field_of_view(360);

  EXPECT_EQ(sd.get_range(), 100);
  EXPECT_EQ(&sd.get_robot(), &r);
  EXPECT_EQ(sd.get_field_of_view(), 360);
}

TEST(SensorProximity, Reset) {
  csci3081::SensorProximity sp;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  sp.activated(true);
  sp.set_range(100);
  sp.set_field_of_view(360);
  sp.set_robot(&r);

  sp.Reset();
  EXPECT_EQ(sp.activated(), false);
  EXPECT_EQ(sp.get_range(), 50);
  EXPECT_EQ(sp.get_field_of_view(), 90);
  EXPECT_EQ(sp.get_robot(), NULL);
}

TEST(SensorProximity, Accept) {
  csci3081::SensorProximity sp;
  csci3081::EventProximity e;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;
  r.set_heading_angle(90)

  // Set pos in event
  e.set_pos(Position(100, 125));

  // Set sensor
  sp.set_robot(&r);

  // Test for inside range and in correct zone
  EXPECT_EQ(sp.Accept(&e), 25);

  // Set pos was within range but incorrect zone
  e.set_pos(Position(100, 75));
  EXPECT_EQ(sp.Accept(&e), -1);

  // Change pos in event to be out of range
  e.set_pos(Position(100, 200));
  EXPECT_EQ(sp.Accept(&e), -1)

  // Set pos to be on the border of range
  e.set_pos(Position(100, 150));
  EXPECT_EQ(sp.Accept(&e), 50);
}

#endif /* SENSOR_PROXIMITY_TEST */
