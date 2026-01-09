/*
 *  Passenger.h
 *  Justin Projansky (jproja01)
 *  2/10/25
 *
 *  This class is for a passenger on a train. Each passenger has an ID, a
 *  station they get on the train at, and a station they depart the train at.
 *
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>
#include <fstream>
#include <string>

class Passenger {
   public:
    Passenger(int id, int startingStation, int endingStation);
    int getId();
    int getStartingStation();
    int getEndingStation();
    void print(std::ostream &output);

   private:
    int id;
    int startingStation;
    int endingStation;
};

#endif

