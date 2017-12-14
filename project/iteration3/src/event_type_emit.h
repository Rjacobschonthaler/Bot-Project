/**
 * @file event_type_emit.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_
#define PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_

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
  * @brief Contains a pointer to the entity to determine what type it is.
  */
class EventTypeEmit : public EventBaseClass {
 public:
  EventTypeEmit();
  void EmitMessage(void);

  void set_ent(ArenaEntity* t) {ent_ = t;}
  ArenaEntity* get_ent() {return ent_;}

 private:
  ArenaEntity* ent_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_TYPE_EMIT_H_
