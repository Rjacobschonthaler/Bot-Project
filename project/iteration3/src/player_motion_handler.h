/**
 * @file player_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_PLAYER_MOTION_HANDLER_H_
#define PROJECT_ITERATION1_SRC_PLAYER_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/motion_handler.h"
#include "src/player_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the player's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * PlayerMotionHandler manages the modification to the velocity based on
 * user input and collisions.
 * PlayerMotionBehavior translates velocity and position to a new position.
 * Both of these are straightforward, but the framework allows for more
 * sophisticated models of motion in which each wheel has distinct speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class PlayerMotionHandler : public MotionHandler {
 public:
  PlayerMotionHandler();

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void);

  /**
   * @brief Command from user keypress via the viewer.
   *
   * @param cmd The command.
   */
  void AcceptCommand(enum event_commands cmd);

  /*
 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
  */
};

NAMESPACE_END(csci3081);

#endif   // PROJECT_ITERATION1_SRC_PLAYER_MOTION_HANDLER_H_
