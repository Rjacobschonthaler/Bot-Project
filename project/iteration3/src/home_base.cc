/**
 * @file home_base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <math.h>
#include <time.h>
#include <cstdlib>

#include "src/home_base.h"
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
HomeBase::HomeBase(const struct home_base_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color) {
    motion_handler_ = RobotMotionHandler();
    motion_behavior_ = RobotMotionBehavior();
    unsigned int seed = time(NULL);
    motion_handler_.set_heading_angle(rand_r(&seed)%360);
    motion_handler_.set_speed(5);
    set_pos(params->pos);
    sensor_touch_ = SensorTouch();
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Update heading_angle if sensor_touch_ is activated and/or random
  * chance occurs. Update position.
  */
void HomeBase::TimestepUpdate(uint dt) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);
  double positive_heading = fmod(motion_handler_.get_heading_angle(), 360);
  if (positive_heading < 0) {
    positive_heading += 360;
  }
  motion_handler_.set_heading_angle(positive_heading);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);

  // Random change of direction
  unsigned int seed = time(NULL);
  if (rand_r(&seed)%20 == 0) {
    seed = time(NULL);
    motion_handler_.set_heading_angle(rand_r(&seed)%360);
  }
} /* TimestepUpdate() */

/**
 * @brief Resets HomeBase to hardcoded position and random direction and resets
 * sensor_touch_
 */

void HomeBase::Reset(void) {
  unsigned int seed = time(NULL);
  motion_handler_.Reset();
  motion_handler_.set_heading_angle(rand_r(&seed)%360);
  set_pos(Position(400, 400));
  sensor_touch_.Reset();
}

NAMESPACE_END(csci3081);
