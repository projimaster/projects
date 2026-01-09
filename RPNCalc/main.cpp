/*
 *  main.cpp
 *  Justin Projansky (jproja01)
 *  3/3/25
 *
 *  This program acts as a calculator using reverse polish notation, where the
 *  user can input numbers, booleans, and strings while performing different
 *  functions on these variables.
 *
 *  Implementation Details:
 *      - Mainly utilizes Datum objects to hold information and perform
            commands
 *      - Uses a DatumStack class to keep track of these Datum objects
 * 
 *  Credit: open_or_die() function in RPNCalc.cpp from
 *          isprime.cpp on CS15 website
 * 
 */

#include <iostream>
#include <fstream>
#include <string>

#include "RPNCalc.h"

using namespace std;

int main() {
    RPNCalc new_calc;
    new_calc.run();

    return 0;
 }