/**
 * @file actuator_commands.h
 *
 * @copyright 2017 John Harwell, All rights reserved.
 *
 */

#ifndef PROJECT_ITERATION1_SRC_EVENT_COMMANDS_H_
#define PROJECT_ITERATION1_SRC_EVENT_COMMANDS_H_

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
// R. Jacob Schonthaler added COM_SLOW
enum event_commands {
  COM_TURN_LEFT,
  COM_TURN_RIGHT,
  COM_FORWARD,
  COM_SLOW
};
NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_EVENT_COMMANDS_H_
