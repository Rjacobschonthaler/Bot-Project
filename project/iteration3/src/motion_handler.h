/**
 * @file robot_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_MOTION_HANDLER_H_
#define PROJECT_ITERATION1_SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/robot_params.h"
#include "src/player_params.h"
#include "src/superbot_params.h"
// When including robot params here, it works....

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The base class that player_motion_handler and robot_motion_handler
 * inherit from.
 */
class MotionHandler {
 public:
  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  virtual void Reset(void) = 0;

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);

  double get_speed() { return speed_; }
  void set_speed(double sp) {
    speed_ = sp; }

  double get_heading_angle() const { return heading_angle_;}
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  double get_max_speed() { return max_speed_; }
  void set_max_speed(double ms) { max_speed_ = ms; }

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION1_SRC_MOTION_HANDLER_H_
