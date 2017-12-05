/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_entity_type.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

SensorEntityType::SensorEntityType() {
  range_ = 100;
  set_activated(false);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

enum entity_types SensorEntityType::Accept(EventTypeEmit * e) {
  return e->get_type();
}

void SensorEntityType::Reset(void) {
  set_activated(false);
  set_range(100);
} /* reset() */

NAMESPACE_END(csci3081);
