/**
 * @file arena_immobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_ARENA_IMMOBILE_ENTITY_H_
#define PROJECT_ITERATION3_SRC_ARENA_IMMOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Base class for obstacles and recharge station
  */
class ArenaImmobileEntity : public ArenaEntity {
 public:
  ArenaImmobileEntity(double radius, const Position& pos,
                    const Color& color) :
      ArenaEntity(radius, pos, color) {}

  bool is_mobile(void) { return false; }
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_ARENA_IMMOBILE_ENTITY_H_
