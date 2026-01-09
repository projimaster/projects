/*
 *  main.cpp
 *  Justin Projansky (jproja01)
 *  2/16/25
 *
 *  This program simulates a metro system where passengers wait at stations,
 *  board trains, and travel to their destinations.
 *
 *  Implementation Details:
 *      - Uses vectors and a queue-based system to manage passenger boarding
 *      - Trains hold passengers and move between stations
 *      - Memory is dynamically allocated for passengers and managed
 *          using pointers
 * 
 *  Credit: open_or_die() function from isprime.cpp on CS15 website
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "MetroSim.h"

using namespace std;

void read_stations(string file_name, MetroSim *train);

template<typename streamtype>
void open_or_die(streamtype &stream, string file_name);

int main(int argc, char *argv[]) {
    // Ensure that there are 3 or 4 command line arguments
    if (not ((argc == 3) or (argc == 4))) {
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]";
        cerr << endl;
        exit(EXIT_FAILURE);
    }

    // Read station file contents
    MetroSim train;
    read_stations(argv[1], &train);

    // Run the simulation, determining if a command text file is used or if
    // commands will be inserted through the terminal
    ofstream outstream;
    open_or_die(outstream, argv[2]);
    if (argc == 3) {
        train.query_loop(cin, cout, outstream);
    } else {
        ifstream instream;
        open_or_die(instream, argv[3]);
        train.query_loop(instream, cout, outstream);
        instream.close();
    }
    outstream.close();

    return 0;
}

// Name:      read_stations
// Purpose:   Record the stations in the text file and add them to the MetroSim
// Arguments: The name of the station text file and a pointer to the MetroSim
// Returns:   none
// Effects:   Fills the station list and the train list in the MetroSim with
//            the stations from the text file
void read_stations(string file_name, MetroSim *train) {
    // Open the text file
    ifstream infile;
    open_or_die(infile, file_name);

    // Loop through the file line-by-line and add each station's information
    // to the lists in MetroSim
    string station_name;
    std::getline(infile, station_name);
    while (not infile.eof()) {
        train->addStation(station_name);
        std::getline(infile, station_name);
    }

    // Close the file
    infile.close();
}

// Name:      open_or_die
// Purpose:   Open a file and ensure no errors arise from this
// Arguments: An unknown streamtype and the name of a file
// Returns:   none
// Effects:   Opens a text file and returns an error if the file could not be
//            opened
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open()) {
        cerr << "Error: could not open file " + file_name << endl;
        exit(EXIT_FAILURE);
    }
}