/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include <algorithm>
#include "src/sensor_distress.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorDistress::Accept(EventDistressCall * e, Position pos, double radius) {
  // Check if the sensor has already been activated
  if (get_activated()) {
    return 1;
  } else {
    // Calculate the distance between the centers of each entity
    double sx = pos.x;
    double ex = e->get_pos().x;
    double sy = pos.y;
    double ey = e->get_pos().y;

    double dist = std::sqrt(
      std::pow(sx - ex, 2) + std::pow(sy - ey, 2));

    /*
     * If the the range of the sensor + the radius of the robot is greater than
     * the distance to the entity - that entity's radius, set activated.
    */
    if (range+radius >= dist-e->get_radius()) {
      set_activated(true);
      return 1;
    }
    else {
      return 0;
    }
  }
}

void SensorDistress::Reset(void) {
  set_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
