/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"
#include "src/position.h"

#include <iostream>
#include <fstream>
#include <string>

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(int argc, char * argv[]) {
  // Essential call to initiate the graphics window
  csci3081::InitGraphics();

  csci3081::robot_params rparams;
  csci3081::arena_params aparams;
  int obstacle_count = 0;

  // Read from config all the parameters
  std::ifstream configfile;

  // Drop the program name
  //argc--;
  //argv++;

  configfile.open(argv[1]);
  assert(configfile.is_open()); // Make sure file is open
  std::string line;
  char command[100];

  while (getline(configfile, line)) {
    // Lines starting with # are comments in config.txt
    if(line[0] == '#') {
      continue;
    }
    // Get name of object
    sscanf(line.c_str(), "%s ", command);
    std::string cmd=command;

    if (cmd == "obstacle") {
      // Read in variables
      float rad, x, y;
      int r, g, b, a;
      sscanf(line.c_str(), "obstacle %f %f %f %d %d %d %d",
        &rad, &x, &y, &r, &g, &b, &a);

      // Create obstacle in aparams
      aparams.obstacles[obstacle_count].radius = rad;
      aparams.obstacles[obstacle_count].pos = {x, y};
      aparams.obstacles[obstacle_count].color = csci3081::Color(r, g, b, a);
      obstacle_count++;
    }
    else if (cmd == "robot") {
      // Read in variables
      float bat_max_charge, ang_delta, rad, x, y;
      int col_delta, r, g, b, a;
      sscanf(line.c_str(), "robot %f %f %d %f %f %f %d %d %d %d",
        &bat_max_charge, &ang_delta, &col_delta, &rad, &x, &y, &r, &g, &b, &a);

      // Create robot in rparams
      rparams.battery_max_charge = bat_max_charge;
      rparams.angle_delta = ang_delta;
      rparams.collision_delta = col_delta;
      rparams.radius = rad;
      rparams.pos = csci3081::Position(x, y);
      rparams.color = csci3081::Color(r, g, b, a);

      // Add rparams to aparams
      aparams.robot = rparams;
    }
    else if (cmd == "recharge_station") {
      // Read in variables
      float rad, x, y;
      int r, g, b, a;
      sscanf(line.c_str(), "recharge_station %f %f %f %d %d %d %d",
        &rad, &x, &y, &r, &g, &b, &a);

      // Create recharge_station in aparams
      aparams.recharge_station.radius = rad;
      aparams.recharge_station.pos = {x, y};
      aparams.recharge_station.color = csci3081::Color(r, g, b, a);
    }
    else if (cmd == "home_base") {
      // Read in variables
      float rad, x, y;
      int r, g, b, a;
      sscanf(line.c_str(), "home_base %f %f %f %d %d %d %d",
        &rad, &x, &y, &r, &g, &b, &a);

      // Create home_base in aparams
      aparams.home_base.radius = rad;
      aparams.home_base.pos = {x, y};
      aparams.home_base.color = csci3081::Color(r, g, b, a);
    }
    else if (cmd == "arena") {
      // Read in variables
      int n_obstacles, x_dim, y_dim;
      sscanf(line.c_str(), "arena %d %d %d", &n_obstacles, &x_dim, &y_dim);

      // Add variables to aparams
      aparams.n_obstacles = n_obstacles;
      aparams.x_dim = x_dim;
      aparams.y_dim = y_dim;
    }
    else {
      printf("command not found in line:\n\t%s\n", line);
    }
  }

  // Start up the graphics (which creates the arena).
  // Run will enter the nanogui::mainloop()
  csci3081::GraphicsArenaViewer *app =
  new csci3081::GraphicsArenaViewer(&aparams);
  app->Run();
  csci3081::ShutdownGraphics();
  return 0;
}
