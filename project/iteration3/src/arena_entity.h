/**
 * @file arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef PROJECT_ITERATION1_SRC_ARENA_ENTITY_H_
#define PROJECT_ITERATION1_SRC_ARENA_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/common.h"
#include "src/color.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A base class representing an entity within the arena. All entities
 * within the arena know how to :
 *
 * 1. Update themselves each timestep (i.e. in accordance with current velocity
 *    and position).
 * 2. Reset themselves to a newly constructed state. This is so the user can
 *    click the reset button after completing a game and have things work as
 *    expected.
 *
 * Note that not all classes need to be able to do these two things.
 */
class ArenaEntity {
 public:
  ArenaEntity(double radius, const Position& pos,
              const Color& color) :
      radius_(radius), pos_(pos), color_(color) {}
  virtual ~ArenaEntity(void) {}

  /**
   * @brief Perform whatever updates are needed for a particular entity after 1
   * timestep (updating position, changing color, etc.).
   */
  virtual void TimestepUpdate(__unused uint dt) {}

  /**
   * @brief Reset the entity to its newly constructed state.
   */
  virtual void Reset(void) {}

  virtual std::string get_name(void) const = 0;

  void set_pos(const Position& pos) { pos_ = pos; }
  const Position& get_pos(void) const { return pos_; }
  const Color& get_color(void) const { return color_; }
  void set_color(const Color& color) { color_ = color; }
  virtual bool is_mobile(void) = 0;
  double get_radius(void) const { return radius_; }

 private:
  double radius_;
  Position pos_;
  Color color_;
};

NAMESPACE_END(csci3081);

#endif  // PROJECT_ITERATION1_SRC_ARENA_ENTITY_H_
