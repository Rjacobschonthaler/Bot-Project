/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_PROXIMITY_H_
#define PROJECT_ITERATION1_SRC_EVENT_PROXIMITY_H_

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
class EventProximity : public EventBaseClass {
 public:
  EventProximity();
  void EmitMessage(void);

  Position get_pos() {return pos_;}
  void set_pos(Position p) {pos_ = p;}

 private:
   Position pos_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_PROXIMITY_H_
