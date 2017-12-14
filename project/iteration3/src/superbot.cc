/**
 * @file superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/superbot.h"
#include "src/robot_motion_behavior.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Superbot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Superbot::Superbot(const struct superbot_params* const params) :
  ArenaMobileEntity(params->radius, params->collision_delta,
    params->pos, params->color),
  reset_pos_(params->pos),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_distress_(),
  sensor_type_(),
  sensor_proximity_(),
  id_(-1) {
  motion_handler_.set_heading_angle(270);
  motion_handler_.set_speed(0);
  id_ = next_id_++;
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*
  * @brief Updates the superbot.
  */
void Superbot::TimestepUpdate(uint dt) {
  Position old_pos = get_pos();

  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);
} /* TimestepUpdate() */

// Pass along a collision event (from arena) to the touch sensor.
// This method provides a framework in which sensors can get different
// types of information from different sources.
void Superbot::Accept(EventCollision * e) {
  sensor_touch_.Accept(e);
}

/**
 * @brief Determines how to adjust the superbot's speed and heading according
 * to the entity in question. The superbot avoids all entities except for the
 * player and a frozen rbobot.
 */
void Superbot::Accept(
  EventDistressCall * ed, EventTypeEmit * et, EventProximity * ep) {
  // Collect info from sensors
  int help_needed = sensor_distress_.Accept(ed, get_pos(), get_radius());
  enum entity_types type = sensor_type_.Accept(et);
  double distance = sensor_proximity_.Accept(
    ep, get_pos(), get_radius(), get_heading_angle());

  // Check if entity = this robot
  double rx = get_pos().x;
  double ex = ed->get_ent()->get_pos().x;
  double ry = get_pos().y;
  double ey = ed->get_ent()->get_pos().y;

  // Nothing happens if robot is frozen or the ent passed is this robot
  if (get_speed() != 0 && (rx != ex || ry != ey)) {
    // If robot senses help or home base
    if ((help_needed == 1  && type == kRobot) || type == kPlayer) {
      // std::cout<<"Help sensed"<<std::endl;
      set_speed(5);
    } else {
      // Reset speed if distance = -1
      if (distance == -1) {
        set_speed(5);
      } else {
        // std::cout<<"Running prox"<<std::endl;
        // Proximity sensed something, adjust course

        // Find heading to obstacle
        double heading_to_obstacle = atan2(ep->get_pos().y-get_pos().y,
        ep->get_pos().x-get_pos().x)*180/3.14;

        heading_to_obstacle = fmod(heading_to_obstacle, 360);
        if (heading_to_obstacle < 0) {
          heading_to_obstacle += 360;
        }

        // Side is determines if the adjustment to the heading is left of right
        int side;
        if (heading_to_obstacle > get_heading_angle()) {
          side = -1;
        } else {
          side = 1;
        }

        // Find the a fraction of range left before impact
        double till_impact = distance/sensor_proximity_.get_range();


        if (till_impact >= 0.8) {
          set_speed(4);
          set_heading_angle(get_heading_angle() + side * 5);
        } else if (till_impact >= 0.6) {
          set_speed(3);
          set_heading_angle(get_heading_angle() + side * 10);
        } else if (till_impact >= 0.4) {
          set_speed(2);
          set_heading_angle(get_heading_angle() + side * 20);
        } else if (till_impact >= 0.2) {
          set_speed(1);
          set_heading_angle(get_heading_angle() + side * 40);
        } else {
          set_speed(1);
          set_heading_angle(get_heading_angle() + side * 80);
        }
      } /* End if proxy sensed something */
    } /* End if distress sensed */
  } /* End speed != 0 */
}

void Superbot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  Position pos = reset_pos_;
  set_pos(pos);
  set_speed(0);
} /* Reset() */

NAMESPACE_END(csci3081);
