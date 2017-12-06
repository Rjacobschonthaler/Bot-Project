#include "Movie.h"
#include "Rental.h"
#include "Customer.h"
#include<string.h>
#include <iostream>

using std::cout;
using std::endl;

int main() {
     Movie m1("The Shining", 2);
     Rental r1(m1, 2);
     Movie m2("Holes", 2);
     Rental r2(m2, 4);
     Movie m3("Cars", 0);
     Rental r3(m3, 2);
     Movie m4("Dogs", 0);
     Rental r4(m4, 3);
     Movie m5("Hello", 1);
     Rental r5(m5, 1);
     Movie m6("Yo!", 1);
     Rental r6(m6, 2);
     Customer c1("Bob");
     c1.addRental(r1);
     c1.addRental(r2);
     c1.addRental(r3);
     c1.addRental(r4);
     c1.addRental(r5);
     c1.addRental(r6);
     cout << c1.statement() << endl;
}
