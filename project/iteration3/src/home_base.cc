/**
 * @file home_base.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/home_base.h"
#include <time.h>
#include <cstdlib>
#include <math.h>
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
    unsigned int seed = time(NULL);
    heading_angle_ = rand_r(&seed)%360;
    collision_delta_ = params->collision_delta;
    pos_ = params->pos;
    speed_ = 5;
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
  // If sensor activated change heading.
  if (sensor_touch_.get_activated()) {
    if (sensor_touch_.get_angle_of_contact() < 0) {
      sensor_touch_.set_angle_of_contact(sensor_touch_.get_angle_of_contact()+360);
    }
    if (sensor_touch_.get_angle_of_contact() > 0) {
      sensor_touch_.set_angle_of_contact(sensor_touch_.get_angle_of_contact()-360);
    }
    heading_angle_ = -sensor_touch_.get_angle_of_contact();
  }

  // Update the position
  double x = get_pos().x+cos(heading_angle_*M_PI/180.0)*speed_*dt;
  double y = get_pos().y+sin(heading_angle_*M_PI/180.0)*speed_*dt;
  set_pos(Position(x, y));

  // Random change of direction
  unsigned int seed = time(NULL);
  if (rand_r(&seed)%20 == 0) {
    seed = time(NULL);
    heading_angle_ = rand_r(&seed)%360;
  }
} /* TimestepUpdate() */

/**
 * @brief Resets HomeBase to hardcoded position and random direction and resets
 * sensor_touch_
 */

void HomeBase::Reset(void) {
  unsigned int seed = time(NULL);
  heading_angle_ = rand_r(&seed)%360;
  set_pos(Position(400, 400));
  sensor_touch_.Reset();
}

NAMESPACE_END(csci3081);
