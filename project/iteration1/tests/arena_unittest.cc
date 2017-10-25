/* STUDENTS:  DO NOT EDIT THIS FILE.  INSTEAD, MODIFY YOUR OWN PROJECT
 * CODE TO FIT THE SPECIFICATION GIVEN BY THE TESTS IN THIS FILE.
 *
 * If you DO modify it, we overwrite it with a fresh version from our repo
 * when grading, so you can't use it to fudge the tests anyway.
 *
 * This file is used by the CS3081W auto-grading system.
 *
 * Please note, the assessment tests for grading, will use the same include
 * files, class names, and function names for accessing students' code that you
 * find in this file.  So students, if you write your code so that it passes
 * these feedback tests, you can be assured that the auto-grader will at least
 * be able to properly link with your code.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "../src/arena_params.h"
#include "../src/event_collision.h"
#include "../src/robot.h"
#include "../src/arena.h"
#include "../src/color.h"

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
#ifdef PRIORITY1_TESTS

/************************************************************************
* SETUP
*************************************************************************/
class ArenaTest : public ::testing::Test {
 protected:
   virtual void SetUp() {
     // Initialize default start values for various arena entities

     rparams.battery_max_charge = 100.0;
     rparams.angle_delta = 10;
     rparams.collision_delta = 1;
     rparams.radius = 20.0;
     rparams.pos = Position(500, 500);
     rparams.color = csci3081::Color(0, 0, 255, 255); /* blue */
     aparams.robot = rparams;

     aparams.recharge_station.radius = 20.0;
     aparams.recharge_station.pos = {500, 300};
     aparams.recharge_station.color = csci3081::Color(0, 128, 128, 255); /* green */

     aparams.home_base.radius = 20.0;
     aparams.home_base.pos = {400, 400};
     aparams.home_base.color = csci3081::Color(255, 0, 0, 255); /* red */

     aparams.obstacles[0].radius = 30.0;
     aparams.obstacles[0].pos = {200, 200};
     aparams.obstacles[0].color = csci3081::Color(255, 255, 255, 255); /* white */

     aparams.n_obstacles = 1;
     aparams.x_dim = 1024;
     aparams.y_dim = 768;
   }
   csci3081::robot_params rparams;
   csci3081::arena_params aparams;
 };

TEST_F(ArenaTest, Constructor) {

};

TEST_F(ArenaTest, CheckObstacleCollision) {
  // Position Robot to collide with obstacle
  rparams.pos = Position(240, 200);
  aparams.robot = rparams;
  csci3081::Arena arena(&aparams);
  csci3081::Robot * robot = arena.robot();

  // Robot leftside collision at x-axis
  double heading = robot->heading_angle();
  arena.AdvanceTime();
  arena.AdvanceTime();
  EXPECT_NE(robot->heading_angle(), heading) <<
    "FAIL: Robot did not register collision with obstacle.";
};

TEST_F(ArenaTest, CheckRechargeCollision) {
  // Position Robot to collide with obstacle
  rparams.pos = Position(530, 300);
  aparams.robot = rparams;
  csci3081::Arena arena(&aparams);
  csci3081::Robot * robot = arena.robot();

  // Robot leftside collision at x-axis
  robot->speed(2);
  double heading = robot->heading_angle();
  arena.AdvanceTime();
  arena.AdvanceTime();
  EXPECT_NE(robot->heading_angle(), heading) <<
    "FAIL: Robot did not register collision with recharge station.";
};

TEST_F(ArenaTest, CheckWallCollision) {
  // Position Robot to collide with wall
  rparams.pos = Position(
    aparams.x_dim-rparams.radius, aparams.y_dim-rparams.radius);
  aparams.robot = rparams;
  csci3081::Arena arena(&aparams);
  csci3081::Robot * robot = arena.robot();

  // Robot leftside collision at x-axis
  robot->speed(2);
  double heading = robot->heading_angle();
  arena.AdvanceTime();
  arena.AdvanceTime();
  EXPECT_NE(robot->heading_angle(), heading) <<
    "FAIL: Robot did not register collision with wall.";
};

#endif /* ARENA_TEST */
