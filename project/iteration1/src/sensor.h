/**
 * @file sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_SENSOR_H_
#define PROJECT_ITERATION1_SRC_SENSOR_H_

/**
 * @brief A base class for snesors to inherit from. Currently, the only sensor
 * is SensorTouch.
 */

class Sensor {
 public:
  bool activated(void) { return activated_; }
  void activated(bool value) { activated_ = value; }

 private:
  bool activated_;
};

#endif   // PROJECT_ITERATION1_SRC_SENSOR_H_
