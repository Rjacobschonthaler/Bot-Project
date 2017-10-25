/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/home_base.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
HomeBase::HomeBase(const struct home_base_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta, params->pos, params->color)
  {
    heading_angle_=45;
    collision_delta_=params->collision_delta;
    pos_=params->pos;
    speed_=0;
  }

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void HomeBase::TimestepUpdate(uint dt)
{
  pos_.x += cos(heading_angle_*M_PI/180.0)*speed_*dt;
  pos_.y += sin(heading_angle_*M_PI/180.0)*speed_*dt;
} /* TimestepUpdate() */

void HomeBase::Reset(void)
{
  heading_angle_=45;
  pos_.x=400;
  pos_.y=400;
}

NAMESPACE_END(csci3081);
