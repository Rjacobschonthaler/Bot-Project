/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include <algorithm>

#include "src/robot.h"
#include "src/robot_motion_behavior.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Robot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Robot::Robot(const struct robot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  reset_pos_(params->pos),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_distress_(),
  sensor_type_(),
  sensor_proximity_(),
  id_(-1) {
  motion_handler_.set_heading_angle(270);
  motion_handler_.set_speed(5);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Robot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void Robot::Accept(EventDistressCall * ed, EventTypeEmit * et, EventProximity * ep) {
  int help = sensor_distress_.Accept(ed, get_pos(), get_radius());
  enum entity_types type = sensor_type_.Accept(et);
  double distance = sensor_proximity_.Accept(ep, get_pos(), get_radius());

  // Code to determine if player collided with robot
  double px = ep->get_pos().x;
  double py = ep->get_pos().y;
  double rx = get_pos().x;
  double ry = get_pos().y;
  double dist = std::sqrt(std::pow(rx - px, 2) + std::pow(ry - py, 2));
  if (type == kPlayer && sensor_touch_.get_activated() &&
    dist <= get_radius()+ep->get_radius()) {
    set_speed(0);
  }
}

void Robot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  Position pos = reset_pos_;
  set_pos(pos);
} /* Reset() */

NAMESPACE_END(csci3081);
