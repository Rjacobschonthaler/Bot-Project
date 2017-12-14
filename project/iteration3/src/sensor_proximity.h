/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_PROXIMITY_H_
#define PROJECT_ITERATION3_SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/sensor.h"
#include "src/common.h"
#include "src/position.h"
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
 * @brief Determines the distance to an entity in question from the owner
 * entity.
 */
class SensorProximity : public Sensor {
 public:
  SensorProximity() {
    range_ = 50; field_of_view_ = 90; x_dim_ = 1024; y_dim_ = 768;}

  /**
   * @brief Finds the distance to an entity in question within the sensor's
   * range. Else it returns -1.
   */

  double Accept(EventProximity * e, Position pos, double radius,
                double heading);

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

  double get_range() {return range_;}
  double get_field_of_view() {return field_of_view_;}
  void set_range(double r) {range_ = r;}
  void set_field_of_view(double a) {field_of_view_ = a;}


 private:
  // bool activated_;
  double range_;
  double field_of_view_;
  int x_dim_;
  int y_dim_;
  Position get_point(double heading, double dist, Position pos);
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION3_SRC_SENSOR_PROXIMITY_H_
