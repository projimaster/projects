/*
 *  Passenger.cpp
 *  Justin Projansky (jproja01)
 *  2/10/25
 *
 *  This file implements the Passenger class.
 *
 */

#include "Passenger.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/*
 * name:      Passenger( )
 * purpose:   This is the constructor for Passenger that initializes
 *            a Passenger object with an ID, starting station, and 
 *            ending station.
 * arguments: An integer passenger ID, an integer starting station,
 *            and an integer ending station. 
 * returns:   none
 * effects:   Constructs a Passenger with the provided information.
 * note:      Students do not have to modify this function.
 */
Passenger::Passenger(int id, int startingStation, int endingStation) {
    this->id = id;
    this->startingStation = startingStation;
    this->endingStation = endingStation;
}

/*
 * name:      getId( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ID. 
 * arguments: none
 * returns:   The Passenger's ID. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getId() { return id; }

/*
 * name:      getStartingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's starting station. 
 * arguments: none
 * returns:   The Passenger's starting station. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getStartingStation() { return startingStation; }

/*
 * name:      getEndingStation( )
 * purpose:   This is the getter (aka accessor) function that provides
 *            access to the Passenger's ending station. 
 * arguments: none
 * returns:   The Passenger's ending station. 
 * effects:   none
 * note:      Students do not have to modify this function.
 */
int Passenger::getEndingStation() { return endingStation; }

/*
 * name:      print( )
 * purpose:   This function prints the data (id, starting station, and ending
 *            station) of the passenger.
 * arguments: An ostream reference parameter
 * returns:   none
 * effects:   Prints out passenger's id, startingStation, and endingStation
 *            variables
 */
void Passenger::print(std::ostream &output) {
    output << "[" << id << ", " << startingStation << "->";
    output << endingStation << "]";
}
