/**
 * @file robot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
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

  if (sensor_touch_.get_activated()) {
    // This line causes the bug of a stopped robot if set to lower than 3 when
    // bouncing off obstacles ocassionally.
    set_speed(3);
  }
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Robot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

void Robot::Accept(EventDistressCall * ed, EventTypeEmit * et, EventProximity * ep) {
  int help = sensor_distress_.Accept(ed, get_pos(), get_radius());
  // enum entity_types type = sensor_type_.Accept(et, get_pos(), get_radius());
  double distance = sensor_proximity_.Accept(ep, get_pos(), get_radius());
}

void Robot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  Position pos = Position(500, 500);
  set_pos(pos);
} /* Reset() */

NAMESPACE_END(csci3081);
