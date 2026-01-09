/*
 *  MetroSim.h
 *  Justin Projansky (jproja01)
 *  2/16/25
 *
 *  This class is for the train. It keeps track of the train's position and any
 *  passengers on the train, as well as the information of each station.
 *
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class MetroSim {

public:
    // Constructor & Destructor
    MetroSim();
        
    // Query Functions
    void query_loop(istream &input, ostream &soutput, ostream &foutput);
    void metro_move(ostream &file_output);
    void add_passenger(int startingStation, int endingStation);

    // Getters
    int getTrainPos();
    int getIdNext();

    // Other Functions
    void addStation(string name);
    void printAll(ostream &output);

private:
    // Station Struct
    struct Station {
        string name;
        PassengerQueue waitlist;
    };
    
    // Important Lists
    std::vector<PassengerQueue> train;
    std::vector<Station> stations;

    // Other Items
    int trainPos;
    int id_next;
};

#endif
