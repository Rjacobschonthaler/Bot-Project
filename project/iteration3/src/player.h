/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_PLAYER_H_
#define PROJECT_ITERATION1_SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/robot_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  void ResetBattery(void);
  void Reset(void);
  void HeadingAngleInc(void) { heading_angle_ += angle_delta_; }
  void HeadingAngleDec(void) { heading_angle_ -= angle_delta_; }
  void TimestepUpdate(unsigned int dt);
  void Accept(EventRecharge * e);
  void Accept(EventCollision * e);
  void EventCmd(enum event_commands cmd);

  void set_freeze_time(void) {freeze_time_ = freeze_time_max_;}
  double battery_level(void) { return battery_.get_level(); }
  double get_heading_angle(void) const { return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }
  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }
  int id(void) const { return id_; }
  std::string get_name(void) const {
    return "Player" + std::to_string(id());
  }

  // R. Jacob Schonthaler created this to show the battery level below robot
  std::string string_battery_level() const {
    return std::to_string(battery_.get_level()); }

 private:
  static unsigned int next_id_;

  int freeze_time_max_ = 50;
  int freeze_time_;
  int id_;
  double heading_angle_;
  double angle_delta_;
  RobotBattery battery_;
  PlayerMotionHandler motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_PLAYER_H_
