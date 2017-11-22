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
RobotMotionHandler::RobotMotionHandler() {
  set_heading_angle(0);
  set_speed(0);
  set_max_speed(10);
}

void RobotMotionHandler::Reset(void) {
  set_heading_angle(45);
  set_speed(5);
  set_max_speed(10);
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/


NAMESPACE_END(csci3081);
