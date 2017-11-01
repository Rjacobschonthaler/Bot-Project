/**
 * @file event_keypress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_keypress.h"
#include "src/graphics_arena_viewer.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
enum event_commands EventKeypress::keypress_to_cmd(int key) {
  /*
  * @todo These values are likely not universal across all OS's.
  * Write a wrapper for the various OS or see if nanogui has that
  * functionality.
  */
  switch (key) {
    // Left arrow key
    case 263:
    return COM_TURN_LEFT;
    break;
    // Right arrow key
    case 262:
    return COM_TURN_RIGHT;
    break;
    // Up arrow key
    case 265:
    return COM_FORWARD;
    break;
    // Down arrow key
    case 264:
    return COM_SLOW;
    break;
    default:
    printf("Unknown keypress: %d\n", key);
    assert(0);
  } /* switch() */
} /* keypress_to_cmd() */

NAMESPACE_END(csci3081);
