/**
 * @file motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <assert.h>
#include <iostream>
#include "src/motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Change a mobile entity's heading_angle
 *
 * @param a mobile entity's sensor_touch_.
 */

void MotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.get_activated()) {
    if (st.get_angle_of_contact() > 0) {
      st.set_angle_of_contact(st.get_angle_of_contact()-360);
    }
    heading_angle_ = -st.get_angle_of_contact();
  }
}

NAMESPACE_END(csci3081);
