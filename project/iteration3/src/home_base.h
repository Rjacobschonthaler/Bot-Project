/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

  #ifndef PROJECT_ITERATION3_SRC_HOME_BASE_H_
  #define PROJECT_ITERATION3_SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/robot_motion_behavior.h"
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief A mobile entity that bounces around the arena without AI that
  * causes a robot to become a superbot upon colliding with it.
  */
class HomeBase : public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  void TimestepUpdate(unsigned int dt);
  void Accept(EventCollision * e) {sensor_touch_.Accept(e);}
  void Reset(void);

  double get_heading_angle(void) const {
    return motion_handler_.get_heading_angle(); }
  void set_heading_angle(double ha) { motion_handler_.set_heading_angle(ha); }

  std::string get_name(void) const { return "Home Base"; }

  // Not used, leftovers from inheriting from ArenaMobileEntity
  double get_speed(void) { return motion_handler_.get_speed(); }
  void set_speed(double sp) { motion_handler_.set_speed(sp); }

 private:
  RobotMotionBehavior motion_behavior_;
  RobotMotionHandler motion_handler_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);
#endif  // PROJECT_ITERATION3_SRC_HOME_BASE_H_
