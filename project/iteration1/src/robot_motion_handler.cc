/**
 * @file robot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
RobotMotionHandler::RobotMotionHandler() :
  heading_angle_(0),
  speed_(0),
  max_speed_(10) {
}

void RobotMotionHandler::Reset(void)
{
  heading_angle_=45;
  speed_=5;
  max_speed_=10;
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 //I defined Accept
void RobotMotionHandler::AcceptCommand(enum event_commands cmd)
{
  int change=20;
  switch (cmd) {
  //COM_TURN_LEFT
  case 0:
    if(heading_angle_-change<0)
    {
      heading_angle_=heading_angle_-change+360;
    }
    else
    {
      heading_angle_-=change;
    }
  break;
  //COM_TURN_RIGHT
  case 1:
    if(heading_angle_+change>359)
    {
      heading_angle_=heading_angle_+change-360;
    }
    else
    {
      heading_angle_+=change;
    }
    break;
  //COM_FORWARD
  case 2:
    if(speed_ < max_speed_)
    {
      speed_+=1;
    }
  break;
  //COM_SLOW
  case 3:
    if(speed_ > 1)
    {
      speed_-=1;
    }
  break;
  default:
    std::cerr << "FATAL: bad actuator command" << std::endl;
    assert(0);
  } /* switch() */
} /* accept_command() */

void RobotMotionHandler::UpdateVelocity(SensorTouch st) {
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
  }
}

NAMESPACE_END(csci3081);
