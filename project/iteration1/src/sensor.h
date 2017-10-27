
class Sensor
{
public:
  bool activated(void) { return activated_; }
  void activated(bool value) { activated_ = value; }

private:
  bool activated_;
};
