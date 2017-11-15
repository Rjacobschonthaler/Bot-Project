/**
 * @file event_type_emit.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_TYPE_EMIT_H_
#define PROJECT_ITERATION1_SRC_EVENT_TYPE_EMIT_H_

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
class EventTypeEmit : public EventBaseClass {
 public:
  EventTypeEmit();
  void EmitMessage(void);

  ArenaEntity* get_entity() {return entity_;}
  void set_entity(ArenaEntity * e) {entity_ = e;}

 private:
   ArenaEntity * entity_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_TYPE_EMIT_H_
