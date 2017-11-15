/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_PROXIMITY_H_
#define PROJECT_ITERATION1_SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/sensor.h"
#include "src/common.h"
#include "src/position.h"
#include "src/robot.h"
#include "src/event_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief
 *
 */
class SensorProximity : public Sensor {
 public:
  SensorProximity();

  /**
   * @brief
   *
   */

  void Accept(EventProximity * e);

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

  double get_range() {return range_;}
  double get_field_of_view() {return field_of_view_;}
  Robot get_robot() {return *robot_;}
  void set_range(double r) {range_ = r;}
  void set_field_of_view(double a) {field_of_view_ = a;}
  void set_robot(Robot * r) {robot_ = r;}


 private:
  // bool activated_;
  double range_;
  double field_of_view_;
  Robot * robot_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION1_SRC_SENSOR_PROXIMITY_H_
