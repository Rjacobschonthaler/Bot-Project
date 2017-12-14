/**
 * @file event_keypress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_
#define PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Translates a keypress into a command to be passed to the player.
 */
class EventKeypress : public EventBaseClass {
 public:
  explicit EventKeypress(int key) : key_(key) {}

  // R. Jacob Schonthaler added get_key
  int get_key(void) {return key_;}

  // R. Jacob Schonthaler added get_command which is called in Arena.cc
  // Accept(EventKeyPress * e) to pass into player's EventCmd.
  enum event_commands get_command() {return keypress_to_cmd(get_key());}

  void EmitMessage(void) { printf("Keypress command received\n"); }

 private:
  enum event_commands keypress_to_cmd(int key);
  int key_;

  EventKeypress& operator=(const EventKeypress& other) = delete;
  EventKeypress(const EventKeypress& other) = delete;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_EVENT_KEYPRESS_H_
