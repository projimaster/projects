/*
 *  unit_tests.h
 *  Justin Projansky (jproja01)
 *  2/18/25
 *
 *  CS 15 PR 1
 *
 *  This file's purpose is to test all member functions of the Passenger,
 *  PassengerQueue, and MetroSim classes to ensure everything works as intended.
 *
 */

#include <cassert>
#include <sstream>
#include <iostream>
 
#include "Passenger.h"
#include "PassengerQueue.h"
#include "MetroSim.h"

// Tests creation of a Passenger
// Also tests printing a Passenger's info
void passenger_constructor() {
    Passenger test_passenger(1, 2, 3);
    
    std::ostringstream outfile;
    test_passenger.print(outfile);

    assert(outfile.str() == "[1, 2->3]");
}

// Tests a Passenger's getID function
// Should return first number in constructor (1)
void passenger_getId() {
    Passenger test_passenger(1, 2, 3);
    assert(test_passenger.getId() == 1);
}

// Tests a Passenger's getStartingStation function
// Should return second number in constructor (2)
void passenger_getStartingStation() {
    Passenger test_passenger(1, 2, 3);
    assert(test_passenger.getStartingStation() == 2);
}

// Tests a Passenger's getEndingStation function
// Should return third number in constructor (3)
void passenger_getEndingStation() {
    Passenger test_passenger(1, 2, 3);
    assert(test_passenger.getEndingStation() == 3);
}


// Tests creation of an empty PassengerQueue
// Size should be 0 since no passengers are in the queue
void passengerqueue_constructor() {
    PassengerQueue test_queue;
    
    std::ostringstream outfile;
    test_queue.print(outfile);

    assert(test_queue.size() == 0);
    assert(outfile.str() == "");
}

// Tests adding Passengers to the PassengerQueue
// Afterwards, size should be 3 and string should be
// in order of passengers inserted
void enqueue_test() {
    PassengerQueue test_queue;
    Passenger test_passenger1(1, 2, 3);
    Passenger test_passenger2(2, 3, 4);
    Passenger test_passenger3(3, 4, 5);
    test_queue.enqueue(test_passenger1);
    test_queue.enqueue(test_passenger2);
    test_queue.enqueue(test_passenger3);
    
    std::ostringstream outfile;
    test_queue.print(outfile);

    assert(test_queue.size() == 3);
    assert(outfile.str() == "[1, 2->3][2, 3->4][3, 4->5]");
}

// Tests checking the first element of a PassengerQueue
// Should return the data of the first element inserted
void first_elem() {
    PassengerQueue test_queue;
    
    Passenger passenger1(1, 2, 3);
    Passenger passenger2(2, 3, 4);
    Passenger passenger3(3, 4, 5);

    test_queue.enqueue(passenger1);
    test_queue.enqueue(passenger2);
    test_queue.enqueue(passenger3);

    std::ostringstream outfile;
    test_queue.front().print(outfile);

    assert(outfile.str() == "[1, 2->3]");
}

// Tests removing elements  of a PassengerQueue
// Size should be 1 and the output should only be from the last passenger
void dequeue_test() {
    PassengerQueue test_queue;
    
    Passenger passenger1(1, 2, 3);
    Passenger passenger2(2, 3, 4);
    Passenger passenger3(3, 4, 5);

    test_queue.enqueue(passenger1);
    test_queue.enqueue(passenger2);
    test_queue.enqueue(passenger3);

    test_queue.dequeue();
    test_queue.dequeue();

    std::ostringstream outfile;
    test_queue.print(outfile);

    assert(test_queue.size() == 1);
    assert(outfile.str() == "[3, 4->5]");
}

// Tests creation of a MetroSim
void metrosim_maker() {
    MetroSim test_train;
    assert(test_train.getTrainPos() == 0);
    assert(test_train.getIdNext() == 1);
}

// Tests getTrainPos and getIdNext
void metrosim_getters() {
    MetroSim test_train;
    assert(test_train.getTrainPos() == 0);

    test_train.addStation("test station");
    test_train.addStation("another station");
    test_train.add_passenger(0, 1);
    // train.metro_move(ostream &file_output);

    assert(test_train.getIdNext() == 2);
    // assert(test_train.getTrainPos() == 1);
}