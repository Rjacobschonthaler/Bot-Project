//R. Jacob Schonthaler 9/29/17
//A robot classs to hold the attributes of a robot

#include <string>
using namespace std;

class Robot
{
  private:
    double radius;
    int colorx;
    int colory;
    int colorz;
    double posx;
    double posy;
    double velocity_x;
    double velocity_y;

  public:
    Robot(void);
    Robot(double r, int x, int y, int z, double px, double py, double vx, double vy);
    double get_radius(void);
    int get_colorx(void);
    int get_colory(void);
    int get_colorz(void);
    double get_posx(void);
    double get_posy(void);
    double get_velocity_x(void);
    double get_velocity_y(void);
    void set_radius(double r);
    void set_color(int x, int y, int z);
    void set_posx(double x);
    void set_posy(double y);
    void set_velocity_x(double x);
    void set_velocity_y(double y);
};
