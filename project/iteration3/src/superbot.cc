/**
 * @file superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
 #include <algorithm>

#include "src/superbot.h"
#include "src/robot_motion_behavior.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Superbot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Superbot::Superbot(const struct superbot_params* const params) :
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
  motion_handler_.set_speed(0);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Superbot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Superbot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void Superbot::Accept(EventDistressCall * ed, EventTypeEmit * et, EventProximity * ep) {
  int help_needed = sensor_distress_.Accept(ed, get_pos(), get_radius());
  enum entity_types type = sensor_type_.Accept(et);
  double distance = sensor_proximity_.Accept(ep, get_pos(), get_radius());
}

void Superbot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  Position pos = reset_pos_;
  set_pos(pos);
  set_speed(0);
} /* Reset() */

NAMESPACE_END(csci3081);
