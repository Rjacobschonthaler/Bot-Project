/**
 * @file sensor_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_
#define PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/sensor.h"
#include "src/common.h"
#include "src/position.h"
#include "src/robot.h"
#include "src/event_distress_call.h"

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
class SensorDistress : public Sensor {
 public:
  SensorDistress();

  /**
   * @brief
   *
   */

  int Accept(EventDistressCall * e);

  /**
   * @brief Reset the distress sensor to its newly constructed state.
   */
  void Reset(void);

  double get_range() {return range_;}
  void set_range(double r) {range_ = r;}
  Robot get_robot() {return *robot_;}
  void set_robot(Robot * r) {robot_ = r;}

 private:
  // bool activated_;
  double range_;
  Robot * robot_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION1_SRC_SENSOR_DISTRESS_H_
