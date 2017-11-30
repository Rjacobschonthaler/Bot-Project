/**
 * @file event_distress_call.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_DISTRESS_CALL_H_
#define PROJECT_ITERATION1_SRC_EVENT_DISTRESS_CALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class EventDistressCall : public EventBaseClass {
 public:
  EventDistressCall();
  void EmitMessage(void);

  Position get_pos() {return pos_;}
  void set_pos(Position p) {pos_ = p;}
  double get_radius() {return radius_;}
  void set_radius(double r) {radius_ = r;}

private:
  Position pos_;
  double radius_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_DISTRESS_CALL_H_
