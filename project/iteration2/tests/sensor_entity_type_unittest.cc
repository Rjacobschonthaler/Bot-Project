/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/sensor_entity_type.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/recharge_station.h"
#include "src/robot.h"

#ifdef SENSOR_ENTITY_TYPE_TEST

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorEntityType, Sanity) {
  csci3081::SensorEntityType se;

  bool val = std::is_base_of<csci3081::BaseSensor, csci3081::SensorEntityType>::value;
  EXPECT_TRUE(val);
  EXPECT_EQ(se.get_activated(), false);
  EXPECT_EQ(se.get_range(), 50);
  EXPECT_EQ(se.get_robot(), NULL);
}

Test(SensorEntityType, Getters) {
  csci3081::SensorEntityType se;

  EXPECT_EQ(se.get_range(), 50);
  EXPECT_EQ(&sd.get_robot(), NULL);
}

Test(SensorEntityType, Setters) {
  csci3081::SensorEntityType se;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  se.set_robot(&r);
  se.set_range(100);

  EXPECT_EQ(se.get_range(), 100);
  EXPECT_EQ(&se.get_robot(), &r);
}

TEST(SensorEntityType, Reset) {
  csci3081::SensorEntityType se;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);

  csci3081::Robot(rparams) r;

  se.activated(true);
  se.set_range(100);
  se.set_robot(&r);

  se.Reset();
  EXPECT_EQ(se.activated(), false);
  EXPECT_EQ(se.get_range(), 50);
  EXPECT_EQ(se.get_robot(), NULL);
}

TEST(SensorEntityType, Accept) {
  csci3081::SensorEntityType se;
  csci3081::EventEntityType e;
  csci3081::robot_params rparams;

  // Build rparams
  rparams.battery_max_charge = 100;
  rparams.angle_delta = 20;
  rparams.collision_delta = 1;
  rparams.radius = 20;
  rparams.pos = csci3081::Position(100, 100);
  rparams.color = csci3081::Color(0, 0, 0, 255);
  csci3081::Robot(rparams) r

  csci3081::Obstacle(20, const Position(100, 125), const Color(0, 0, 0, 255)) o;

  csci3081::RechargeStation(20, const Position(100, 125), const Color(0, 0, 0, 255)) re;

  csci3081::home_base_params params;
  params.radius = 20;
  params.pos = csci3081::Position(100, 125);
  params.color = csci3081::Color(0, 0, 0, 255);
  csci3081::HomeBase(params) h;



  // Set sensor
  sp.set_robot(&r);

  e.set_entity(o);
  EXPECT_EQ(se.Accept(&e), kObstacle);

  e.set_entity(re);
  EXPECT_EQ(se.Accept(&e), kRechargeStation);

  e.set_entity(h);
  EXPECT_EQ(se.Accept(&e), kHomeBase);

  rparams.pos = csci3081::Position(100, 125);
  csci3081::Robot(rparams) r0;

  e.set_entity(r0);
  EXPECT_EQ(se.Accept(&e), kObstacle);

  csci3081::Obstacle(20, const Position(100, 25), const Color(0, 0, 0, 255)) o0;
  e.set_entity(o0);
  EXPECT_EQ(se.Accept(&e), NULL);

  csci3081::Obstacle(20, const Position(100, 50), const Color(0, 0, 0, 255)) o1;
  e.set_entity(o1);
  EXPECT_EQ(se.Accept(&e), kObstacle);
}

#endif /* SENSOR_ENTITY_TYPE_TEST */
