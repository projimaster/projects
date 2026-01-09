/*
 *  PassengerQueue.h
 *  Justin Projansky (jproja01)
 *  2/10/25
 *
 *  This class is for a queue of passengers on a train waiting to leave.
 *  This queue utilizes a vector behind the scenes and uses public member
 *  functions modify the data in this private vector.
 *
 */

 #ifndef __PASSENGERQUEUE_H__
 #define __PASSENGERQUEUE_H__
 
 #include "Passenger.h"
 
 #include <iostream>
 #include <fstream>
 #include <string>
 #include <vector>
 
 class PassengerQueue {
    public:
     Passenger front();
     void dequeue();
     void enqueue(const Passenger &passenger);
     int size();
     void print(std::ostream &output);
 
    private:
     std::vector<Passenger> passenger_list;
 };
 
 #endif
 
 