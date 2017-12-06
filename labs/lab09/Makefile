CXX = g++
CXXFLAGS = -Wall -c -std=c++11

all: Dep

Dep: main.o Customer.o Movie.o Rental.o
	$(CXX) -o lab09.out main.o Customer.o Movie.o Rental.o

Customer.o: Customer.h Customer.cpp
	$(CXX) $(CXXFLAGS) Customer.cpp

Movie.o: Movie.h Movie.cpp
	$(CXX) $(CXXFLAGS) Movie.cpp

Rental.o: Rental.h Rental.cpp
	$(CXX) $(CXXFLAGS) Rental.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm *.o *.out
