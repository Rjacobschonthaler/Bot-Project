//Created by R. Jacob Schonthaler 9/15/17

#include <iostream>
#include <string>
#include "DecoyDuck.h"

using std::cout;
using std::endl;
using std::string;

DecoyDuck::DecoyDuck() : Duck(){}

string DecoyDuck::getDescription()
{
  string descriptionText = "a plastic decoy duck";
  return descriptionText;
}

void DecoyDuck::performQuack()
{
  cout << "..." << endl;
}




