/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_COLLISION_H_
#define PROJECT_ITERATION1_SRC_EVENT_COLLISION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class EventCollision : public EventBaseClass {
 public:
  EventCollision();
  void EmitMessage(void);
  bool get_collided() { return collided_; }
  void set_collided(bool c) { collided_ = c; }
  Position get_point_of_contact() { return point_of_contact_; }
  void set_point_of_contact(Position p) { point_of_contact_ = p; }
  double get_angle_of_contact() { return angle_of_contact_; }
  void set_angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  bool collided_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_COLLISION_H_
