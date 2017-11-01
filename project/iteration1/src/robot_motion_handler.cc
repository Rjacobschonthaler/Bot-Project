/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <iostream>
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(10) {
}

void RobotMotionHandler::Reset(void) {
  heading_angle_ = 45;
  speed_ = 5;
  max_speed_ = 10;
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Change the heading_angle or speed of robot
  *
  * @param cmd which turns out to be the index of the command in the
  * event_commands stucture.
  */
void RobotMotionHandler::AcceptCommand(enum event_commands cmd) {
  int change = 20;
  switch (cmd) {
  // COM_TURN_LEFT
  case 0:
    if (heading_angle_ - change < 0) {
      heading_angle_ = heading_angle_ - change + 360;
    } else {
      heading_angle_ -= change;
    }
  break;
  // COM_TURN_RIGHT
  case 1:
    if (heading_angle_ + change > 359) {
      heading_angle_ = heading_angle_ + change - 360;
    } else {
      heading_angle_ += change;
    }
    break;
  // COM_FORWARD
  case 2:
    if (speed_ < max_speed_) {
      speed_ += 1;
    }
  break;
  // COM_SLOW
  case 3:
    if (speed_ > 0) {
      speed_ -= 1;
    }
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

/**
 * @brief Change robot's heading_angle
 *
 * @param Robot's sensor_touch_.
 */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    if (st.angle_of_contact() > 0) {
      st.angle_of_contact(st.angle_of_contact()-360);
    }
    heading_angle_ = -st.angle_of_contact();
  }
}

NAMESPACE_END(csci3081);
