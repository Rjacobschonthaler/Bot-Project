/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

// Reloading
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/robot.h"
#include "src/event_recharge.h"
#include "src/event_distress_call.h"
#include "src/event_proximity.h"
#include "src/event_type_emit.h"

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
  player_(new Player(&params->player)),
  n_robots_(params->n_robots),
  n_obstacles_(params->n_obstacles),
  recharge_station_(new RechargeStation(params->recharge_station.radius,
    params->recharge_station.pos,
    params->recharge_station.color)),
  home_base_(new HomeBase(&params->home_base)),
  entities_(),
  mobile_entities_() {
  player_->set_heading_angle(37);
  entities_.push_back(player_);
  mobile_entities_.push_back(player_);

  // R. Jacob Schonthaler added this so that Home Base would bounce
  entities_.push_back(home_base_);
  mobile_entities_.push_back(home_base_);

  entities_.push_back(recharge_station_);

  for (size_t i = 0; i < n_obstacles_; ++i) {
    entities_.push_back(new Obstacle(
        params->obstacles[i].radius,
        params->obstacles[i].pos,
        params->obstacles[i].color));
  } /* for(i..) */

  for (size_t i = 0; i < n_robots_; ++i) {
    Robot* new_robot = new Robot(&params->robots[i]);
    entities_.push_back(new_robot);
    mobile_entities_.push_back(new_robot);
  } /* for(i..) */

  for (size_t i = 0; i < n_robots_; ++i) {
    // Create superbot and add it to the arena
    Superbot* new_superbot = new Superbot(&params->superbots[i]);
    entities_.push_back(new_superbot);
    mobile_entities_.push_back(new_superbot);
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

std::vector<Robot*> Arena::robots(void) {
  std::vector<Robot*> res;
  for (auto ent : entities_) {
    Robot* r = dynamic_cast<Robot*>(ent);
    if (r) {
      res.push_back(r);
    }
  } /* for(ent..) */
  return res;
} /* robots() */

std::vector<Superbot*> Arena::superbots(void) {
  std::vector<Superbot*> res;
  for (auto ent : entities_) {
    Superbot* r = dynamic_cast<Superbot*>(ent);
    if (r) {
      res.push_back(r);
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

  // Update robot and supberbot sensors
  EventProximity ep;
  EventDistressCall ed;
  EventTypeEmit et;
  for (size_t i = 0; i < robots().size(); i++) {
    std::cout << robots()[i]->get_name() << std::endl;
    for (size_t j = 0; j < entities_.size(); j++) {
      ep.set_pos(entities_[j]->get_pos());
      ep.set_radius(entities_[j]->get_radius());
      ed.set_ent(entities_[j]);
      et.set_ent(entities_[j]);
      robots()[i]->Accept(&ed, &et, &ep);
      superbots()[i]->Accept(&ed, &et, &ep);
    }
  }

  /*
   * Next, check if the all robots are superbots
   */

  bool all_moving = true;
  for (size_t i = 0; i < superbots().size(); i++) {
    if (all_moving && superbots()[i]->get_speed() == 0) {
      all_moving = false;
    }
  }
  if (all_moving) {
    std::cout << "You Lose!" << std::endl;
    set_gameover(true);
  }

  /*
   * Next, check if the player has frozen all the robots
   */

  bool frozen = true;
  for (size_t i = 0; i < robots().size(); i++) {
    if (frozen && robots()[i]->get_speed() != 0) {
      frozen = false;
    }
  }
  if (frozen && !all_moving) {
    std::cout << "You Win!" << std::endl;
    set_gameover(true);
  }

   /*
    * Next, check if the player has run out of battery
    */
  if (player_->battery_level() <= 0 && !get_gameover()) {
    // R. Jacob Schonthaler added this for game completion
    std::cout << "You Lose!" << std::endl;
    set_gameover(true);
  }

   /*
    * Next, check if the player has collided with the recharge station or robots
    * . These need to be before the general collisions, which can move the
    * player away from these "obstacles" before the "collisions" have been
    * properly processed.
    */

  /**
   * @brief Check if the player has collided with recharge station.
   */

  EventCollision ec;
  CheckForEntityCollision(player_, recharge_station_,
    &ec, player_->get_collision_delta());
  if (ec.get_collided()) {
    EventRecharge er;
    // er.EmitMessage();
    player_->Accept(&er);
  }

  /**
   * @brief Check if the player has collided with a robot.
   */

  for (size_t i = 0; i < robots().size(); i++) {
    CheckForEntityCollision(player_, robots()[i],
      &ec, player_->get_collision_delta());
    if (ec.get_collided()) {
      robots()[i]->set_speed(0);
    }
  }

   /**
    * @brief Check if the player has collided with a superbot.
    */

    for (size_t i = 0; i < superbots().size(); i++) {
      CheckForEntityCollision(player_, superbots()[i],
        &ec, player_->get_collision_delta());
      if (ec.get_collided()) {
        player_->set_freeze_time();
      }
    }

   /**
    * @brief Check if a robot has collided with a robot.
    */

    for (size_t i = 0; i < robots().size(); i++) {
      for (size_t j = 0; j < robots().size(); j++) {
        CheckForEntityCollision(robots()[i], robots()[j],
          &ec, robots()[i]->get_collision_delta());
        if (ec.get_collided() && i != j) {
          if (robots()[i]->get_speed() == 0) {
            robots()[i]->set_speed(5);
          }
          if (robots()[j]->get_speed() == 0) {
            robots()[j]->set_speed(5);
          }
        }
      }
    }

    /**
     * @brief Check if a superrobot has collided with a robot.
     */

     for (size_t i = 0; i < superbots().size(); i++) {
       for (size_t j = 0; j < robots().size(); j++) {
         CheckForEntityCollision(superbots()[i], robots()[j],
           &ec, robots()[i]->get_collision_delta());
         if (ec.get_collided() && robots()[j]->get_speed() == 0) {
           robots()[j]->set_speed(5);
         }
       }
     }

    /**
     * @brief Check if a robot has collided with the home base
     * and becomes a superbot.
     */

     for (size_t i = 0; i < robots().size(); i++) {
       CheckForEntityCollision(home_base_, robots()[i],
         &ec, robots()[i]->get_collision_delta());
       if (ec.get_collided()) {
         Robot* robot = robots()[i];
         Superbot* superbot = superbots()[i];
         Position pos = robot->get_pos();

         robot->set_pos(superbot->get_pos());
         superbot->set_pos(pos);

         superbot->set_heading_angle(robot->get_heading_angle());

         if (robot->get_speed() == 0) {
           superbot->set_speed(5);
         } else {
           superbot->set_speed(robot->get_speed());
           robot->set_speed(0);
         }
       }
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
        CheckForEntityCollision(
          ent, entities_[i], &ec, ent->get_collision_delta());
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
  }
} /* entities_have_collided() */

/**
 * @brief Sends command player to change heading_angle or speed.
 */

void Arena::Accept(EventKeypress * e) {
  player_->EventCmd(e->get_command());
  // e->EmitMessage();
}

NAMESPACE_END(csci3081);
