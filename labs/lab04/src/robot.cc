//R. Jacob Schonthaler 9/29/17
//Definition for robot functions

#include "src/robot.h"
#include <string>
using namespace std;

Robot::Robot()
{
  radius=50;
  colorx=0;
  colory=0;
  colorz=0;
  posx=0;
  posy=0;
  velocity_x=1;
  velocity_y=1;
}

Robot::Robot(double r, int x, int y, int z, double px, double py, double vx, double vy)
{
  radius=r;
  colorx=x;
  colory=y;
  colorz=z;
  posx=px;
  posy=py;
  velocity_x=vx;
  velocity_y=vy;
}

double Robot::get_radius() {return radius;}

int Robot::get_colorx() {return colorx;}

int Robot::get_colory() {return colory;}

int Robot::get_colorz() {return colorz;}

double Robot::get_posx() {return posx;}

double Robot::get_posy() {return posy;}

double Robot::get_velocity_x() {return velocity_x;}

double Robot::get_velocity_y() {return velocity_y;}

void Robot::set_radius(double r) {radius=r;}

void Robot::set_color(int x, int y, int z) {colorx=x; colory=y; colorz=z;}

void Robot::set_posx(double x) {posx=x;}

void Robot::set_posy(double y) {posy=y;}

void Robot::set_velocity_x(double x) {velocity_x=x;}

void Robot::set_velocity_y(double y) {velocity_y=y;}
