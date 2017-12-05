/**
 * @file player_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <iostream>
#include "src/player_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
PlayerMotionHandler::PlayerMotionHandler() {
  set_heading_angle(0);
  set_speed(0);
  set_max_speed(10);
}

void PlayerMotionHandler::Reset(void) {
  set_heading_angle(45);
  set_speed(5);
  set_max_speed(10);
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Change the heading_angle or speed of player
  *
  * @param cmd which turns out to be the index of the command in the
  * event_commands stucture.
  */
void PlayerMotionHandler::AcceptCommand(enum event_commands cmd) {
  int change = 20;
  switch (cmd) {
  // COM_TURN_LEFT
  case 0:
    if (get_heading_angle() - change < 0) {
      set_heading_angle(get_heading_angle() - change + 360);
    } else {
      set_heading_angle(get_heading_angle() - change);
    }
  break;
  // COM_TURN_RIGHT
  case 1:
    if (get_heading_angle() + change > 359) {
      set_heading_angle(get_heading_angle() + change - 360);
    } else {
      set_heading_angle(get_heading_angle() + change);
    }
    break;
  // COM_FORWARD
  case 2:
    if (get_speed() < get_max_speed()) {
      set_speed(get_speed()+1);
    }
  break;
  // COM_SLOW
  case 3:
    if (get_speed() > 0) {
      set_speed(get_speed()-1);
    }
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

NAMESPACE_END(csci3081);
