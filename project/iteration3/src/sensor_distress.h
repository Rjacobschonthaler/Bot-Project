/**
 * @file sensor_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_
#define PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/sensor.h"
#include "src/common.h"
#include "src/position.h"
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
 * @brief A sensor that determines if there is a distressed robot near the
 * owner entity.
 */
class SensorDistress : public Sensor {
 public:
  SensorDistress() {range_ = 50;}

  /**
   * @brief Detemines if there is a nearby distressed robot.
   *
   */

  int Accept(EventDistressCall * e, Position pos, double radius);

  /**
   * @brief Reset the distress sensor to its newly constructed state.
   */
  void Reset(void);

  double get_range() {return range_;}
  void set_range(double r) {range_ = r;}

 private:
  // bool activated_;
  double range_;
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION3_SRC_SENSOR_DISTRESS_H_
