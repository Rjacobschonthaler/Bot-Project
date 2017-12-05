/**
 * @file sensor_touch.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_touch.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorTouch::SensorTouch() : point_of_contact_(0, 0) {
  set_activated(false);
  set_angle_of_contact(0);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorTouch::Accept(EventCollision * e) {
  // Determine if the sensor should be activated or inactivated.
  if (e->get_collided()) {
    set_activated(true);
    point_of_contact_ = e->get_point_of_contact();
    angle_of_contact_ = e->get_angle_of_contact();
  } else {
    set_activated(false);
  }
}

void SensorTouch::Reset(void) {
  set_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
