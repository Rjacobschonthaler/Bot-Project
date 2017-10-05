/**
 * @file robot_land.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_land.h"

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// Hard coded for 2 robots moving in circular patterns
int RobotLand::get_num_robots(void) { return sizeof(robots)/sizeof(*robots); }

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
bool RobotLand::get_robot_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    *x_pos = robots[id].get_posx();
    *y_pos = robots[id].get_posy();
    return true;
  } else if (id == 1) {
    // make this robot slower
    /*double t = 0.75 * sim_time_;
    robots[id].set_posx(circle_x(t));
    robots[id].set_posy(circle_y(t));*/
    *x_pos = robots[id].get_posx();
    *y_pos = robots[id].get_posy();
    return true;
  } else {
    return false;
  }
}

// Hard coded for now...
// Once the robot class is added, this getter should call the robot getters
// Notice the use of "id" -- how will you handle this in your robot class??
bool RobotLand::get_robot_vel(int id, double *x_vel, double *y_vel) {
  if (id == 0) {

    *x_vel = robots[id].get_velocity_x();
    *y_vel = robots[id].get_velocity_y();

    return true;
  } else if (id == 1) {

    *x_vel = robots[id].get_velocity_x();
    *y_vel = robots[id].get_velocity_y();

    return true;
  } else {
    return false;
  }
}

double RobotLand::get_robot_radius(int id) { return robots[id].get_radius(); }

// Hard coded for now...  in radians
double RobotLand::get_robot_sensor_angle(int id) { return 2.0; }

// Hard coded for now...
double RobotLand::get_robot_sensor_distance(int id) {
  return 3.0 * get_robot_radius(id);
}

// Hard coded for now...
int RobotLand::get_num_obstacles() { return 1; }

// Hard coded for now...
bool RobotLand::get_obstacle_pos(int id, double *x_pos, double *y_pos) {
  if (id == 0) {
    *x_pos = 200;
    *y_pos = 300;
    return true;
  }
  return false;
}

// Hard coded for now...
double RobotLand::get_obstacle_radius(int id) { return 75; }

int RobotLand::get_robot_colorx(int id) {return robots[id].get_colorx();}

int RobotLand::get_robot_colory(int id) {return robots[id].get_colory();}

int RobotLand::get_robot_colorz(int id) {return robots[id].get_colorz();}

void RobotLand::set_robot_color(int id, int x, int y, int z) {robots[id].set_color(x, y, z);}
