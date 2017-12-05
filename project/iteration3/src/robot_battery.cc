/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include "src/robot_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Calculate the new battery level based on the current linear/angular speed.
  *
  * @param linear_vel The current linear speed, in m/s.
  * @param angular_vel The current angular speed, in rad/s.
  *
  * @return The updated battery level.
  */
// R. Jacob Schonthaler defined battery depletion
double RobotBattery::Deplete(Position old_pos, Position new_pos, double dt) {
  int x_dif = new_pos.x-old_pos.x;
  int y_dif = new_pos.y-old_pos.y;
  int dif = sqrt(x_dif*x_dif+y_dif*y_dif);
  charge_ = charge_-0.02*dif*dt-kBASE_DEPLETION;
  return charge_;
} /* deplete() */

/**
 * @brief Lose 20 charge for running into wall or obstacle
 */
void RobotBattery::Accept(EventCollision * e) {
  charge_ = charge_ - 20;
}

NAMESPACE_END(csci3081);
