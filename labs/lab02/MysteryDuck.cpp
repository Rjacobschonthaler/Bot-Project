//Created by R. Jacob Schonthaler 9/15/17

#include <iostream>
#include <string>
#include "MysteryDuck.h"

using std::cout;
using std::endl;
using std::string;

MysteryDuck::MysteryDuck(string des, string sou)
{
   description=des;
   sound=sou;
}

string MysteryDuck::getDescription()
{
  return description;
}

void MysteryDuck::performQuack()
{
  cout << sound << endl;
}

