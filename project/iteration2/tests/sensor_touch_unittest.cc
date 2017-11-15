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
#include "../src/sensor_touch.h"

#ifdef SENSOR_TOUCH_TEST

/*******************************************************************************
 * Test Cases
 ******************************************************************************/
TEST(SensorTouch, Sanity) {
  csci3081::SensorTouch st;

  bool val = std::is_base_of<csci3081::BaseSensor, csci3081::SensorTouch>::value;
  EXPECT_TRUE(val);

  EXPECT_EQ(st.activated(), false);
  EXPECT_EQ(st.point_of_contact(), Position(0, 0));
  EXPECT_EQ(st.angle_of_contact(), 0.0);

  st.activated(true);
  st.point_of_contact(Position(1.0, 1.0));
  EXPECT_EQ(st.activated(), true);
  EXPECT_EQ(st.point_of_contact(), Position(1.0, 1.0));
}

TEST(SensorTouch, Reset) {
  csci3081::SensorTouch st;

  st.activated(true);
  st.point_of_contact(Position(1.0, 1.0));
  EXPECT_EQ(st.activated(), true);
  EXPECT_EQ(st.point_of_contact(), Position(1.0, 1.0));
  EXPECT_DOUBLE_EQ(st.angle_of_contact(), 45.0);

  st.Reset();
  EXPECT_EQ(st.angle_of_contact(), 0.0);
  EXPECT_EQ(st.point_of_contact(), Position(0, 0));
  EXPECT_EQ(st.activated(), false);
}

#endif /* SENSOR_TOUCH_TEST */
