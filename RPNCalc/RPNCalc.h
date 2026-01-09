/*
 *  RPNCalc.h
 *  Justin Projansky (jproja01)
 *  3/2/25
 *
 *  This class is for the calculator itself. It keeps track of multiple
 *  Datum objects on a private DatumStack, as well as any functions that can
 *  be run on the stack's contents.
 */

#ifndef __RPNCalc_H__
#define __RPNCalc_H__
 
#include "Datum.h"
#include "DatumStack.h"
  
#include <iostream>
#include <fstream>
#include <string>

   
class RPNCalc {
public:
    RPNCalc();
    void run();

    // Note: Temporarly made these public in order to run unit tests on them
    // DatumStack datum_stack;
    // void query_loop(std::string command, std::istream &input);

private:
    DatumStack datum_stack;

    // Query Loop Function
    void query_loop(std::string command, std::istream &input);

    // Command Functions
    void add_number(int num);
    void add_bool(std::string s);
    void add_string(std::istream &input);
    void not_com();
    void print();
    void dup();
    void swap();

    // Operator Functions
    void addition();
    void subtraction();
    void multiplication();
    void division();
    void mod();

    void less_than();
    void greater_than();
    void less_or_equal();
    void greater_or_equal();
    void equal();

    // Complicated Command Functions
    void exec();
    void file();
    void if_com();
    void if_helper(std::string type, Datum datum);
};
   
#endif
   