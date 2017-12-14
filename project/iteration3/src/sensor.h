/**
 * @file sensor.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_SENSOR_H_
#define PROJECT_ITERATION3_SRC_SENSOR_H_

/**
 * @brief A base class for sensors to inherit from.
 */

class Sensor {
 public:
  bool get_activated(void) { return activated_; }
  void set_activated(bool value) { activated_ = value; }

 private:
  bool activated_;
};

#endif   // PROJECT_ITERATION3_SRC_SENSOR_H_
