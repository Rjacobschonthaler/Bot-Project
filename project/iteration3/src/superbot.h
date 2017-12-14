/**
 * @file superbot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SUPERBOT_H_
#define PROJECT_ITERATION3_SRC_SUPERBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/sensor_distress.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/arena_mobile_entity.h"
#include "src/event_collision.h"
#include "src/event_distress_call.h"
#include "src/event_type_emit.h"
#include "src/event_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A mobile entity that operates just like a robot except that it
  * avoids the homebase and ignores the player.
  */
class Superbot : public ArenaMobileEntity {
 public:
  explicit Superbot(const struct superbot_params* const params);

  void Reset(void);
  void TimestepUpdate(unsigned int dt);
  void Accept(EventCollision * e);
  void Accept(EventDistressCall * ed, EventTypeEmit * et, EventProximity * ep);

  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  int id(void) const { return id_; }
  std::string get_name(void) const {
    return "Superbot" + std::to_string(id());
  }

 private:
  static unsigned int next_id_;

  Position reset_pos_;
  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_type_;
  SensorProximity sensor_proximity_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_SUPERBOT_H_
