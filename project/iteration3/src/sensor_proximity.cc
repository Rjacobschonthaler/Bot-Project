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
 /*
  * @brief Returns the distance to the closest point of an entity in
  * question if it is within the sensor's range. Else it returns -1.
  */
double SensorProximity::Accept(EventProximity * e, Position pos, double radius,
                                double heading) {
  // Calculate the distance between the centers of each entity
  double sx = pos.x;
  double ex = e->get_pos().x;
  double sy = pos.y;
  double ey = e->get_pos().y;

  if (sx == ex && sy == ey) {
    return -1;
  }

  double dist = std::sqrt(
    std::pow(sx - ex, 2) + std::pow(sy - ey, 2));

  /*
   * If the the range of the sensor + the radius of the robot is less than
   * the distance to the entity - that entity's radius, return -1.
  */
  if (range_+radius < dist-e->get_radius()) {
    set_activated(false);
    return -1;
  } else {
    // Find the heading of each side of sensor
    double left_heading = heading - field_of_view_/2;
    double right_heading = heading + field_of_view_/2;

    // Find heading to entity point
    double heading_to_obstacle = atan2(ey-sy, ex-sx)*180/3.14;
    heading_to_obstacle = fmod(heading_to_obstacle, 360);
    if (heading_to_obstacle < 0) {
      heading_to_obstacle += 360;
    }

    // If heading between left and right, return dist - both radii
    if (heading_to_obstacle > left_heading
        && heading_to_obstacle < right_heading) {
      return dist - radius - e->get_radius();
    } else {
      /*
       * Loop through the points on  each side of the sensor and check if
       * it is with the radius of the entity.
      */
      for (double i = 0; i < range_; i++) {
        Position point = get_point(left_heading, radius+i, pos);
        dist = std::sqrt(std::pow(point.x-ex, 2) + std::pow(point.y-ey, 2));
        if (dist < e->get_radius()) {
          return i;
        }
        point = get_point(right_heading, radius+i, pos);
        dist = std::sqrt(std::pow(point.x-ex, 2) + std::pow(point.y-ey, 2));
        if (dist < e->get_radius()) {
          return i;
        }
        return -1;
      }
    }
  }
}

Position SensorProximity::get_point(double heading, double dist, Position pos) {
  int x, y;
  if (heading >= 0 && heading < 90) {
    x = pos.x + cos(heading)*(dist);
    y = pos.y + sin(heading)*(dist);
    return Position(x, y);
  } else if (heading >= 90 && heading < 180) {
    heading -= 90;
    x = pos.x - sin(heading)*(dist);
    y = pos.y + cos(heading)*(dist);
    return Position(x, y);
  } else if (heading >= 180 && heading < 270) {
    heading -= 180;
    x = pos.x - cos(heading)*(dist);
    y = pos.y - sin(heading)*(dist);
    return Position(x, y);
  } else {
    heading -= 270;
    x = pos.x + sin(heading)*(dist);
    y = pos.y - cos(heading)*(dist);
    return Position(x, y);
  }
}

void SensorProximity::Reset(void) {
  set_activated(false);
} /* reset() */

NAMESPACE_END(csci3081);
