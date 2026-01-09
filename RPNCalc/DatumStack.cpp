/*
 *  DatumStack.cpp
 *  Justin Projansky (jproja01)
 *  3/3/25
 *
 *  This file implements the DatumStack class.
 *
 */

#include "DatumStack.h"

#include <iostream>
#include <fstream>
#include <string>
 
using namespace std;
 
// Name:      DatumStack default constructor
// Purpose:   Initializes an empty stack
// Arguments: none
// Returns:   none
// Effects:   none
DatumStack::DatumStack() {}

// Name:      DatumStack array constructor
// Purpose:   Initializes a stack with the array's contents and size
// Arguments: An array of Datums and an int containing the size of the array
// Returns:   none
// Effects:   Creates a DatumStack with the contents of the given array
DatumStack::DatumStack(Datum data[], int size) {
    for (int i = 0; i < size; i++) {
        push(data[i]);
    }
}

// Name:      isEmpty
// Purpose:   Checks if the current DatumStack is empty (has no elements)
// Arguments: none
// Returns:   Returns true if the stack is empty and false otherwise
// Effects:   none
bool DatumStack::isEmpty() {
    return (datum_list.size() == 0);
}

// Name:      clear
// Purpose:   Clears all elements off the stack
// Arguments: none
// Returns:   none
// Effects:   Removes all elements from the DatumStack's datum_list
void DatumStack::clear() {
    int size = datum_list.size();
    if (size == 0) {
        return;
    } else {
        for (int i = 0; i < size; i++) {
            pop();
        }
    }
}

// Name:      size
// Purpose:   Returns the size of the stack
// Arguments: none
// Returns:   The number of elements in the stack
// Effects:   none
int DatumStack::size() {
    return datum_list.size();
}

// Name:      top
// Purpose:   Returns the element (passenger) at the front of the queue
// Arguments: none
// Returns:   The passenger at the front of the list
// Effects:   none
Datum DatumStack::top() {
    if (isEmpty()) {
        throw runtime_error("Error: empty_stack");
    } else {
        return datum_list.back();
    }
}

// Name:      pop
// Purpose:   Removes the element (Datum) at the top of the stack
// Arguments: none
// Returns:   none
// Effects:   Deletes the Datum at the top of the stack
void DatumStack::pop() {
    if (isEmpty()) {
        throw runtime_error("Error: empty_stack");
    } else {
        datum_list.pop_back();
    }
}

// Name:      push
// Purpose:   Inserts a new element (Datum) at the top of the stack
// Arguments: none
// Returns:   none
// Effects:   Adds a Datum to the top of the stack
void DatumStack::push(const Datum &datum) {
    datum_list.push_back(datum);
}