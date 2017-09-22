CXX = g++
CXXFLAGS = -Wall -c -std=c++11

all: 
	$(CXX) -o lab03.out main.o Squeak.o RubberDuck.o QuackBehavior.o Quack.o MuteQuack.o MallardDuck.o Duck.o DecoyDuck.o

DecoyDuck.o: DecoyDuck.h DecoyDuck.cpp
	$(CXX) $(CXXFLAGS) DecoyDuck.cpp

Duck.o: Duck.h Duck.cpp
	$(CXX) $(CXXFLAGS) Duck.cpp

MallardDuck.o: MallardDuck.h MallardDuck.cpp
	$(CXX) $(CXXFLAGS) MallardDuck.cpp

MuteQuack.o: MuteQuack.h MuteQuack.cpp
	$(CXX) $(CXXFLAGS) MuteQuack.cpp

Quack.o: Quack.h Quack.cpp
	$(CXX) $(CXXFLAGS) Quack.cpp

QuackBehavior.o: QuackBehavior.h QuackBehavior.cpp
	$(CXX) $(CXXFLAGS) QuackBehavior.cpp

RubberDuck.o: RubberDuck.h RubberDuck.cpp
	$(CXX) $(CXXFLAGS) RubberDuck.cpp

Squeak.o: Squeak.h Squeak.cpp
	$(CXX) $(CXXFLAGS) Squeak.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm *.o *.out
