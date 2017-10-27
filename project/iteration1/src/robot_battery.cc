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
double RobotBattery::Deplete(Position old_pos, Position new_pos, double dt)
{
  //I defined battery depletion
  int x_dif=new_pos.x-old_pos.x;
  int y_dif=new_pos.y-old_pos.y;
  int dif=sqrt(x_dif*x_dif+y_dif*y_dif);
  charge_=charge_-0.02*dif*dt;
  return charge_;
} /* deplete() */

void RobotBattery::Accept(EventCollision * e) {
  charge_=charge_-20;
}

NAMESPACE_END(csci3081);
