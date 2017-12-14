/**
 * @file event_distress_call.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_
#define PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Holds a pointer to an entity so that a robot or superbot can
  * determine if it is distress.
  */
class EventDistressCall : public EventBaseClass {
 public:
  EventDistressCall();
  void EmitMessage(void);

  ArenaEntity* get_ent() {return ent_;}
  void set_ent(ArenaEntity* e) {ent_ = e;}

 private:
  ArenaEntity* ent_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_DISTRESS_CALL_H_
