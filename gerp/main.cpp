/*
 *  main.cpp
 *
 *  Purpose: Reads command line arguments from the user and uses the
 *           information to initialize and run Gerp.
 * 
 * The Gerp and HashTable classes may be used to:
 *      - Store every word from every file in a given directory to a hash table
 *      - Search for all occurances of any word in the given directory
 * 
 * Credit: open_or_die() function is from isprime.cpp on CS15 website
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
*/

#include <string>

#include "Gerp.h"
 
using namespace std;

int main(int argc, char *argv[]) {
    // Ensure that there are 3 command line arguments
    if (not(argc == 3)) {
        cerr << "Usage: ./gerp inputDirectory outputFile" << endl;
        exit(EXIT_FAILURE);
    }

    // Start indexing phase
    Gerp new_gerp;
    new_gerp.index(argv[1]);

    // Start query phase
    new_gerp.query_loop(argv[2]);

    return 0;
}