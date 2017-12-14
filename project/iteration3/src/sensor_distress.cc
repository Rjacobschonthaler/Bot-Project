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
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*
  * @brief Determines if the entity in question is within the range of the
  * sensor and if it's a frozen robot. If both are true, it returns ; else it
  * returns 0.
  */
int SensorDistress::Accept(EventDistressCall * e, Position pos, double radius) {
  // Check if the sensor has already been activated
  if (get_activated()) {
    return 1;
  } else {
    // Calculate the distance between the centers of each entity
    double sx = pos.x;
    double ex = e->get_ent()->get_pos().x;
    double sy = pos.y;
    double ey = e->get_ent()->get_pos().y;

    // If x and y values are the same, e contains this robot
    if (sx == ex && sy == ey) {
      return 0;
    }

    double dist = std::sqrt(
      std::pow(sx - ex, 2) + std::pow(sy - ey, 2));

    Robot* r = dynamic_cast<Robot*>(e->get_ent());

    /*
     * If the the range of the sensor + the radius of the robot is greater than
     * the distance to the entity - that entity's radius, set activated.
    */
    if (range_+radius >= dist-e->get_ent()->get_radius() && r &&
    r->get_speed() == 0) {
      return 1;
    } else {
      return 0;
    }
  }
}

void SensorDistress::Reset(void) {
  set_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
