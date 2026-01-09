/*
 *  PassengerQueue.cpp
 *  Justin Projansky (jproja01)
 *  2/10/25
 *
 *  This file implements the PassengerQueue class.
 *
 */

 #include "PassengerQueue.h"

 #include <iostream>
 #include <fstream>
 #include <string>
 
 using namespace std;
 
// Name:      front
// Purpose:   Returns the element (passenger) at the front of the queue
// Arguments: none
// Returns:   The passenger at the front of the list
// Effects:   none
Passenger PassengerQueue::front() {
    return passenger_list.front();
}

// Name:      dequeue
// Purpose:   Removes the element (passenger) at the front of the queue
// Arguments: none
// Returns:   none
// Effects:   Deletes the passenger at the front of the list
void PassengerQueue::dequeue() {
    if (not(passenger_list.empty())) {
        passenger_list.erase(passenger_list.begin());
    }
}

// Name:      enqueue
// Purpose:   Inserts a new element (passenger) at the end of the queue
// Arguments: none
// Returns:   none
// Effects:   Adds a passenger to the end of the list
void PassengerQueue::enqueue(const Passenger &passenger) {
    passenger_list.push_back(passenger);
}

// Name:      size
// Purpose:   Returns the size of the queue
// Arguments: none
// Returns:   The number of elements in the list
// Effects:   none
int PassengerQueue::size() {
    return passenger_list.size();
}

// Name:      print
// Purpose:   Prints the data (id, starting station, and ending station) of
//            every passenger in the queue.
// Arguments: none
// Returns:   none
// Effects:   Prints out each passenger's id, startingStation, and
//            endingStation variables
void PassengerQueue::print(std::ostream &output) {
    for (int i = 0; i < passenger_list.size(); i++) {
        passenger_list.at(i).print(output);
    }
}
