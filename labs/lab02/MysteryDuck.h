//Created by R. Jacob Schonthaler 9/15/17

#ifndef LAB02_MysteryDUCK_H_
#define LAB02_MysteryDUCK_H_

#include <string>
#include "Duck.h"

using std::string;

class MysteryDuck : public Duck {
private:
    string description;
    string sound;
public:
    MysteryDuck(string des, string sou);
    string getDescription();
    void performQuack();
};

#endif
