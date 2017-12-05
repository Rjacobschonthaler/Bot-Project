/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

  #ifndef PROJECT_ITERATION1_SRC_HOME_BASE_H_
  #define PROJECT_ITERATION1_SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class HomeBase : public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  void TimestepUpdate(unsigned int dt);
  void Accept(EventCollision * e) {sensor_touch_.Accept(e);}
  void Reset(void);

  double get_heading_angle(void) const { return heading_angle_; }
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  std::string get_name(void) const { return "Home Base"; }

  // Not used, leftovers from inheriting from ArenaMobileEntity
  double get_speed(void) { return speed_; }
  void set_speed(double sp) { speed_ = sp; }
  void Accept(EventRecharge * e) {}

 private:
  double heading_angle_;
  double collision_delta_;
  double speed_;
  Position pos_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);
#endif  // PROJECT_ITERATION1_SRC_HOME_BASE_H_
