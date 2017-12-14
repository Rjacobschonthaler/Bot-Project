/**
 * @file actuator_entity_type.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_
#define PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
enum entity_types {
  kRobot,
  kSuperBot,
  kPlayer,
  kHomeBase,
  kRechargeStation,
  kObstacle,
  kWall,
  kNothing
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_ENTITY_TYPE_H_
