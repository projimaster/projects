#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 

# This rule builds the executable for MetroSim
MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(LDFLAGS) -o MetroSim main.o MetroSim.o PassengerQueue.o Passenger.o

# This rule builds main.o
main.o: main.cpp MetroSim.h
	$(CXX) $(CXXFLAGS) -c main.cpp

# This rule builds MetroSim.o
MetroSim.o: MetroSim.cpp MetroSim.h PassengerQueue.h Passenger.h
	$(CXX) $(CXXFLAGS) -c MetroSim.cpp

# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp

# This rule builds Passenger.o
Passenger.o: Passenger.h Passenger.cpp
	$(CXX) $(CXXFLAGS) -c Passenger.cpp


# The below rule will be used by unit_test.
unit_test: unit_test_driver.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) $^

# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out