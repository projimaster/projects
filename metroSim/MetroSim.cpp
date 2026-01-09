/*
 *  MetroSim.cpp
 *  Justin Projansky (jproja01)
 *  2/16/25
 *
 *  This file implements the MetroSim class.
 *
 */

#include "MetroSim.h"

// Name:      MetroSim constructor
// Purpose:   Initializes a MetroSim with a trainPos value equal to zero and an
//            id_next value equal to one.
// Arguments: none
// Returns:   none
// Effects:   Creates a MetroSim with the provided information
MetroSim::MetroSim() {
    trainPos = 0;
    id_next = 1;
}

// Name:      query_loop
// Purpose:   Continuously asks the user queries and carries out the requested
//            tasks.
// Arguments: An input stream, an output stream to the terminal, and an output
//            stream to a text file.
// Returns:   none
// Effects:   Performs the tasks that the user inputs, and constantly asks the
//            user for new tasks
void MetroSim::query_loop(istream &input, ostream &soutput, ostream &foutput) {
    printAll(soutput);
    string query;

    // While the user hasn't quit the program, continuously ask them queries
    bool keep_going = true;
    while (keep_going) {
        soutput << "Command? ";
        input >> query;
        if (query == "m") {
            string next;
            input >> next;
            if (next == "m") {
                metro_move(foutput);
                printAll(soutput);
            } else {
                keep_going = false;
            }
        } else if (query == "p") {
            int start, end;
            input >> start >> end;
            add_passenger(start, end);
            printAll(soutput);
        } else {
            keep_going = false;
        }
    }
 
    soutput << "Thanks for playing MetroSim. Have a nice day!" << endl;
}

// Name:      metro_move
// Purpose:   Moves the train from its current station to the next station
// Arguments: An output stream to a text file
// Returns:   none
// Effects:   Picks up passengers at the current station, moves the train to
// the next station, and drops off all required passengers at that next station
void MetroSim::metro_move(ostream &foutput) {
    // Pick up all passengers at the current station
    while (stations.at(trainPos).waitlist.size() > 0) {
        int id = stations.at(trainPos).waitlist.front().getId();
        int st = stations.at(trainPos).waitlist.front().getStartingStation();
        int end = stations.at(trainPos).waitlist.front().getEndingStation();
        Passenger new_pass = Passenger(id, st, end);

        train.at(end).enqueue(new_pass);
        stations.at(trainPos).waitlist.dequeue();
    }

    // Move to the next station
    int numStations = stations.size();
    trainPos = trainPos + 1;
    if (trainPos == numStations) {
        trainPos = 0;
    }

    // Drop off all required passengers at the current station
    while (train.at(trainPos).size() > 0) {
        foutput << "Passenger " << train.at(trainPos).front().getId();
        foutput << " left train at station " << stations.at(trainPos).name;
        foutput << endl;
        train.at(trainPos).dequeue();
    }
}

// Name:      add_passenger
// Purpose:   Adds a new passenger at a specified station to the simulation
// Arguments: The indexes of the passenger's starting station and
//            ending station
// Returns:   none
// Effects:   Creates a new passenger and places them at their starting station
void MetroSim::add_passenger(int start, int end) {
    Passenger new_passenger = Passenger(id_next, start, end);
    stations.at(start).waitlist.enqueue(new_passenger);
    id_next++;
}

// Name:      addStation
// Purpose:   Adds a new station from a station text file to the simulation
// Arguments: The name of the station to be added
// Returns:   none
// Effects:   Creates a new station and places it at the end of the station
//            list in the MetroSim, and places a matching PassengerQueue at the
//            end of the train list
void MetroSim::addStation(string name) {
    Station new_station;
    new_station.name = name;
    stations.push_back(new_station);
    
    PassengerQueue new_queue;
    train.push_back(new_queue);
}

// Name:      getTrainPos
// Purpose:   Returns the train' current position (the index of the station it
//            currently resides at)
// Arguments: none
// Returns:   The MetroSim's trainPos value
// Effects:   none
int MetroSim::getTrainPos() {
    return trainPos;
}

// Name:      getIdNext
// Purpose:   Returns the id to be given to the next passenger
// Arguments: none
// Returns:   The MetroSim's id_next value
// Effects:   none
int MetroSim::getIdNext() {
    return id_next;
}

// Name:      printAll
// Purpose:   Prints all train, station, and passenger info to the terminal
// Arguments: An output stream to the terminal
// Returns:   none
// Effects:   Prints the passengers on the train and each station's information
//            to the terminal
void MetroSim::printAll(ostream &output) {
    int station_size = train.size();
    
    // Print the passengers on the train
    output << "Passengers on the train: {";
    for (int i = 0; i < station_size; i++) {
        train.at(i).print(output);
    }
    output << "}" << endl;

    // Print each station's index number, name, and waiting passengers
    for (int i = 0; i < station_size; i++) {
        if (i == trainPos) {
            output << "TRAIN: ";
        } else {
            output << "       ";
        }
        Station *curr_station = &stations.at(i);
        output << "[" << i << "] " << curr_station->name << " {";
        curr_station->waitlist.print(output);
        output << "}" << endl;
    }
}