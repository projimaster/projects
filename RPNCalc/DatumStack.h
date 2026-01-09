/*
 *  DatumStack.h
 *  Justin Projansky (jproja01)
 *  2/26/25
 *
 *  This class is for storing a stack of Datum objects.
 *  This stack utilizes a vector to function and uses public member
 *  functions to modify the data.
 */

#ifndef __DATUMSTACK_H__
#define __DATUMSTACK_H__

#include "Datum.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
  
class DatumStack {
public:
    // Constructors
    DatumStack();
    DatumStack(Datum data[], int size);

    // Stack Functions
    bool isEmpty();
    void clear();
    int size();
    Datum top();
    void pop();
    void push(const Datum &datum);
  
private:
    std::vector<Datum> datum_list;
};
  
#endif
  