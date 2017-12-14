/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_
#define PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /*
  * @brief A special obstacled that recharges te player upon the player
  * colliding with it.
  */ 
class RechargeStation: public Obstacle {
 public:
  RechargeStation(double radius, const Position& pos,
                  const Color& color) :
      Obstacle(radius, pos, color) {}
  std::string get_name(void) const {
    return "Recharge Station";
  }
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION3_SRC_RECHARGE_STATION_H_
