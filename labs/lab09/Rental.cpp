// Rental.cpp
#include "Rental.h"

double Rental::getCharge() const {
  return _movie.getCharge(_daysRented);
}

int Rental::getFrequentRenterPoints() const {
  return _movie.getFrequentRenterPoints(_daysRented);
}
