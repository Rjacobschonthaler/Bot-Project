/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_entity_type.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/player.h"
#include "src/recharge_station.h"
#include "src/robot.h"
#include "src/superbot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

SensorEntityType::SensorEntityType() {
  range_ = 50;
  set_activated(false);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
 /*
  * @brief Translates an entity into an entity_type if within the sensor's
  * range.
  */
enum entity_types SensorEntityType::Accept(EventTypeEmit * e) {
  Superbot* s = dynamic_cast<Superbot*>(e->get_ent());
  if (s) {
    return kSuperBot;
  }
  Robot* r = dynamic_cast<Robot*>(e->get_ent());
  if (r) {
    return kRobot;
  }
  Player* p = dynamic_cast<Player*>(e->get_ent());
  if (p) {
    return kPlayer;
  }
  HomeBase* h = dynamic_cast<HomeBase*>(e->get_ent());
  if (h) {
    return kHomeBase;
  }
  RechargeStation* re = dynamic_cast<RechargeStation*>(e->get_ent());
  if (re) {
    return kRechargeStation;
  }
  Obstacle* o = dynamic_cast<Obstacle*>(e->get_ent());
  if (o) {
    return kObstacle;
  }
  return kNothing;
}

void SensorEntityType::Reset(void) {
  set_activated(false);
  set_range(50);
} /* reset() */

NAMESPACE_END(csci3081);
