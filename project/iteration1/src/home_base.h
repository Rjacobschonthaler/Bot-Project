/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_mobile_entity.h"
//Mobile attempt

//#include "src/arena_immobile_entity.h"
//Immobile
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
class HomeBase : public ArenaMobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params);
  void TimestepUpdate(unsigned int dt);
  void Accept(EventRecharge * e) {}
  void Accept(EventCollision * e) {}
  void Reset(void);

  double heading_angle(void) const { return heading_angle_; }
  void heading_angle(double ha) { heading_angle_=ha; }
  double speed(void) { return speed_; }
  void speed(double sp) { speed_=sp; }
  Position pos() const { return pos_; }
  void pos(Position pos) { pos_ = pos; }

  std::string name(void) const { return "Home Base"; }

private:

 double heading_angle_;
 double collision_delta_;
 double speed_;
 Position pos_;
};
//Mobile attempt
/*
class HomeBase: public ArenaImmobileEntity {
 public:
  explicit HomeBase(const struct home_base_params* const params) :
    ArenaImmobileEntity(params->radius, params->pos, params->color) {
  }
  std::string name(void) const { return "Home Base"; }
};*/

NAMESPACE_END(csci3081);

#endif /* SRC_HOME_BASE_H_ */
