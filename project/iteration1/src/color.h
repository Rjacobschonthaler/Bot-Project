#include <string>

struct Color
{
    Color() {red=0; yellow=0; blue=0; opacity=0;}
    Color(int r, int y, int b, int o)
    {
      red=r;
      yellow=y;
      blue=b;
      opacity=o;
    }

    int red;
    int yellow;
    int blue;
    int opacity;
};
