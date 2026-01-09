/*
 *  parser.h
 *  Justin Projansky (jproja01)
 *  3/3/25
 *
 *  This file implements the parseRString function
 */

#include <string>
#include <iostream>

#include "parser.h"

using namespace std;

// Name:      parseRString
// Purpose:   Read in user-inputted string from the input stream and create a
//            readable, manipulatable string out of it.
// Arguments: The input stream
// Returns:   The final parsed string
// Effects:   Reads in all user-inputted data between two curly braces
string parseRString(istream &input) {
    string final_string = "{";
    int bracket_counter = 1;

    while (bracket_counter != 0) {
        string c;
        input >> c;
        if (c == "{") {
            bracket_counter = bracket_counter + 1;
        } else if (c == "}") {
            bracket_counter = bracket_counter - 1;
        }
        final_string = final_string + " " + c;
    }

    return final_string;
}
