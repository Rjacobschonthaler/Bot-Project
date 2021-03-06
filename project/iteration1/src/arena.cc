/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/robot.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
 /**
  * @brief This is the place where arena entities interact with eachother.
  */
Arena::Arena(const struct arena_params* const params) :
  x_dim_(params->x_dim), y_dim_(params->y_dim),
  robot_(new Robot(&params->robot)),
  n_robots_(1),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  robot_->set_heading_angle(37);
  entities_.push_back(robot_);
  mobile_entities_.push_back(robot_);

  // R. Jacob Schonthaler added this so that Home Base would bounce
  mobile_entities_.push_back(home_base_);

  entities_.push_back(recharge_station_);

  entities_.push_back(home_base_);

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */

  // R. Jacob Schonthaler added this for game completion
  gameover_ = false;
}

Arena::~Arena(void) {
  for (auto ent : entities_) {
    delete ent;
  } /* for(ent..) */
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /**
  * @brief Resets arena and called by pressing the reset button
  */
void Arena::Reset(void) {
  for (auto ent : entities_) {
    ent->Reset();
  } /* for(ent..) */
  set_gameover(false);
} /* reset() */

std::vector<Obstacle*> Arena::obstacles(void) {
  std::vector<Obstacle*> res;
  for (auto ent : entities_) {
    Obstacle* o = dynamic_cast<Obstacle*>(ent);
    if (o) {
      res.push_back(o);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

/**
 * @brief Calls AdvanceTime to update the arena.
 */
void Arena::AdvanceTime(void) {
  // std::cout << "Advancing simulation time by 1 timestep\n";
  UpdateEntitiesTimestep();
} /* AdvanceTime() */

/**
 * @brief Updates mobile_entity positions, checks for win or loss, and checks for collisions.
 */
void Arena::UpdateEntitiesTimestep(void) {
  /*
   * First, update the position of all entities, according to their current
   * velocities.
   */
  for (auto ent : entities_) {
    ent->TimestepUpdate(1);
  } /* for(ent..) */

  /*
   * Next, check if the robot has run out of battery
   */
  if (robot_->battery_level() <= 0) {
    // R. Jacob Schonthaler added This for game completion
    std::cout << "You Lose!" << std::endl;
    set_gameover(true);
  }

  /*
   * Next, check if the robot has collided with the recharge station or the home
   * base. These need to be before the general collisions, which can move the
   * robot away from these "obstacles" before the "collisions" have been
   * properly processed.
   */

  EventCollision ec;
  CheckForEntityCollision(robot_, home_base_, &ec, robot_->get_collision_delta());
  if (ec.get_collided()) {
    // R. Jacob Schonthaler added this for game completion
      std::cout << "You Win!" << std::endl;
      set_gameover(true);
  }

  /**
   * @brief Check if the robot has collided with recharge station.
   */

  CheckForEntityCollision(robot_, recharge_station_,
    &ec, robot_->get_collision_delta());
  if (ec.get_collided()) {
    EventRecharge er;
    // er.EmitMessage();
    robot_->Accept(&er);
  }

  /*
   * Finally, some pairs of entities may now be close enough to be considered
   * colliding, send collision events as necessary.
   *
   * When something collides with an immobile entity, the immobile entity does
   * not move (duh), so no need to send it a collision event.
   */
  for (auto ent : mobile_entities_) {
    // Check if it is out of bounds. If so, use that as point of contact.
    assert(ent->is_mobile());
    CheckForEntityOutOfBounds(ent, &ec);

    // If not at wall, check if colliding with any other entities (not itself)
    if (!ec.get_collided()) {
      for (size_t i = 0; i < entities_.size(); ++i) {
        if (entities_[i] == ent) {
          continue;
        }
        CheckForEntityCollision(ent, entities_[i], &ec, ent->get_collision_delta());
        if (ec.get_collided()) {
          break;
        }
      } /* for(i..) */
    } /* else */
    ent->Accept(&ec);
  } /* for(ent..) */
} /* UpdateEntities() */

// fixed jittering at walls
void Arena::CheckForEntityOutOfBounds(const ArenaMobileEntity * const ent,
  EventCollision * event) {
  /**
   * R. Jacob Schonaler added bouncing off of left and right walls
   * and checking of heading to fix jittering along the walls. Jittering
   * by cancelling the collision if the heading of the mobile_arena_entity
   * is directed away from the wall.
   */
  double heading = ent->get_heading_angle();
  if (ent->get_pos().x+ ent->get_radius() >= x_dim_ &&
  ((heading > 0 && (heading < 90 || heading > 270))
  || (heading < 0 && (heading > -90 || heading < -270)))) {
    // Right Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(x_dim_, ent->get_pos().y));
    event->set_angle_of_contact(ent->get_heading_angle()-180);
  } else if (ent->get_pos().x- ent->get_radius() <= 0 &&
  ((heading > 0 && (heading > 90 && heading < 270))
  || (heading < 0 && (heading < -90 && heading > -270)))) {
    event->set_collided(true);
    event->set_point_of_contact(Position(0, ent->get_pos().y));
    event->set_angle_of_contact(ent->get_heading_angle()+180);
  } else if (ent->get_pos().y+ ent->get_radius() >= y_dim_ &&
  ((heading > 0 && heading < 180)
  || (heading < -180 && heading > -360))) {
    // Bottom Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(ent->get_pos().x, y_dim_));
    event->set_angle_of_contact(ent->get_heading_angle());
  } else if (ent->get_pos().y - ent->get_radius() <= 0 &&
  ((heading > 180 && heading < 360)
  || (heading < 0 && heading > -180))) {
    // Top Wall
    event->set_collided(true);
    event->set_point_of_contact(Position(0, y_dim_));
    event->set_angle_of_contact(ent->get_heading_angle());
  } else {
    event->set_collided(false);
  }
} /* entity_out_of_bounds() */

void Arena::CheckForEntityCollision(const ArenaMobileEntity* const ent1,
  const ArenaEntity* const ent2,
  EventCollision * event,
  double collision_delta) {
  /* Note: this assumes circular entities */
  double ent1_x = ent1->get_pos().x;
  double ent1_y = ent1->get_pos().y;
  double ent2_x = ent2->get_pos().x;
  double ent2_y = ent2->get_pos().y;
  double dist = std::sqrt(
    std::pow(ent2_x - ent1_x, 2) + std::pow(ent2_y - ent1_y, 2));
  if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
    event->set_collided(false);
  } else {
    // Populate the collision event.
    // R. Jacob Schonthaler populated this.
    // Collided is true
    event->set_collided(true);

    // Angle of contact is angle to that point of contact
    /**
     * The mobile entity always bounces off the obstacle in the opposite
     * direction from the heading to the center of the obstacle.
     */
    double heading_to_obstacle = atan2(ent2_y-ent1_y, ent2_x-ent1_x)*180/3.14;
    double desired_heading = heading_to_obstacle-180;
    event->set_angle_of_contact(-desired_heading);

    // Point of contact is point along perimeter of ent1
    double ratio = ent1->get_radius()/ent2->get_radius();
    double collision_x = ent1_x+ratio*(ent1_x-ent2_x);
    double collision_y = ent1_y+ratio*(ent1_y-ent2_y);
    event->set_point_of_contact(Position(collision_x, collision_y));
    /// >>>>>>> FILL THIS IN
  }
} /* entities_have_collided() */

/**
 * @brief Sends command robot to change heading_angle or speed.
 */

void Arena::Accept(EventKeypress * e) {
  robot_->EventCmd(e->get_command());
  // e->EmitMessage();
}

NAMESPACE_END(csci3081);
