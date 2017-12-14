/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_
#define PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_

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
 /**
  * @brief Perform whatever updates are needed for a particular entity after 1
  * timestep (updating position, changing color, etc.).
  */
class EventProximity : public EventBaseClass {
 public:
  EventProximity();
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

#endif  // PROJECT_ITERATION3_SRC_EVENT_PROXIMITY_H_
