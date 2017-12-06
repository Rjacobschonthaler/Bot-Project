/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include <algorithm>
#include "src/sensor_proximity.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorProximity::Accept(EventProximity * e, Position pos, double radius) {
  // Calculate the distance between the centers of each entity
  double sx = pos.x;
  double ex = e->get_pos().x;
  double sy = pos.y;
  double ey = e->get_pos().y;

  double dist = std::sqrt(
    std::pow(sx - ex, 2) + std::pow(sy - ey, 2));

  /*
   * If the the range of the sensor + the radius of the robot is less than
   * the distance to the entity - that entity's radius, return -1.
  */
  if (range+radius < dist-e->get_radius()) {
    set_activated(false);
    return -1;
  }
  else {
    // Find the point closest to robot
    double heading_to_robot = atan2(sy-ey, sx-ex)*180/3.14-180;

    // Find heading to point closest to robot

    // If heading to closest point is within heading_angle +- .5xrange, good

    // Else determine if either side of range goes within radius from entity


  }
}

void SensorProximity::Reset(void) {
  set_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
