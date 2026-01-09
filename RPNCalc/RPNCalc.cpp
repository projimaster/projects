/*
 *  DatumStack.h
 *  Justin Projansky (jproja01)
 *  2/26/25
 *
 *  This class implements the RPNCalc class.
 */

// These includes are necessary for got_int( )
#include <string>
#include <cstdio>

#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

#include "RPNCalc.h"
#include "parser.h"
#include "Datum.h"

using namespace std;

/*
 * Name: got_int 
 * Purpose:    determines whether a string contains an encoding of an
 *             integer value and loads said integer into an integer
 *             variable whose address has been passed to this function.
 *             An integer encoding contains an optional sign and
 *             a sequence of digits.  Extraneous whitespace is
 *             ignored.
 * Parameters: s contains a string that might encode an integer.
 *             resultp contains the address of an integer variable to
 *             store the integer from s in, should the conversion
 *             succeed.
 *             can be parsed from said string
 * Returns:    true if an integer was successfully parsed from the
 *             provided string;
 *             false otherwise (s did not contain a valid integer
 *             encoding)
 * Effects:    *resultp will be set the integer value encoded by s
 *             on success; otherwise it is undetermined (may be set
 *             if there are extra characters after digits)
 *
 * Author: Mark A. Sheldon, Tufts University, Fall 2016
 * Note to students: you do not have to modify this comment!
 */
bool got_int(string s, int *resultp)
{
    char extra;  /* Holds first non-whitespace character after integer */
                 /* Should not match anything:  want "3." to fail      */
    return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

RPNCalc::RPNCalc() {
    datum_stack.clear();
}

// Name:      run
// Purpose:   Starts the calculator by receiving a command and running the
//            query loop
// Arguments: none
// Returns:   none
// Effects:   Receives a command from the user and loops the query loop while
//            the command isn't "quit"
void RPNCalc::run() {
    string command;
    cin >> command;

    while ((command != "quit") and not(cin.eof())) {
        try {
            query_loop(command, cin);
        } catch (const std::runtime_error &e) {
            cerr << e.what() << endl;
        }
        cin >> command;
    }

    cerr << "Thank you for using CalcYouLater." << endl;
}

// Name:      query_loop
// Purpose:   Adds a user-inputted int to the stack
// Arguments: A string containing the user-inputted command and the
//            input stream
// Returns:   none
// Effects:   Loops through all possible functions and executes one if it
//            matches the command.
void RPNCalc::query_loop(string command, istream &input) {
    int num;
    if (command == "exec") {
        exec();
    } else if (command == "file") {
        file();
    } else if (command == "if") {
        if_com();
    } else if (command == "{") {
        add_string(input);
    } else if (command == "#t" or command == "#f") {
        add_bool(command);
    } else if (got_int(command, &num)) {
        add_number(num);
    } else if (command == "not") {
        not_com();
    } else if (command == "print") {
        print();
    } else if (command == "clear") {
        datum_stack.clear();
    } else if (command == "drop") {
        datum_stack.pop();
    } else if (command == "dup") {
        dup();
    } else if (command == "swap") {
        swap();
    } else if (command == "+") {
        addition();
    } else if (command == "-") {
        subtraction();
    } else if (command == "*") {
        multiplication();
    } else if (command == "/") {
        division();
    } else if (command == "mod") {
        mod();
    } else if (command == "<") {
        less_than();
    } else if (command == ">") {
        greater_than();
    } else if (command == "<=") {
        less_or_equal();
    } else if (command == ">=") {
        greater_or_equal();
    } else if (command == "==") {
        equal();
    } else {
        cerr << command << ": unimplemented" << endl;
    }
}

// Name:      add_number
// Purpose:   Adds a user-inputted int to the stack
// Arguments: The int variable to be added to the stack
// Returns:   none
// Effects:   Pushes a datum containing the user-inputted int onto the stack
void RPNCalc::add_number(int num) {
    datum_stack.push(Datum(num));
}

// Name:      add_bool
// Purpose:   Adds a user-inputted boolean to the stack
// Arguments: A string containing the boolean to be added to the stack
// Returns:   none
// Effects:   Pushes a datum containing the user-inputted boolean onto the
//            stack
void RPNCalc::add_bool(string s) {
    if (s == "#t") {
        datum_stack.push(Datum(true));
    } else {
        datum_stack.push(Datum(false));
    }
}

// Name:      add_string
// Purpose:   Adds an rstring to the stack
// Arguments: The input stream
// Returns:   none
// Effects:   Creates a datum containing the user-inputted string and pushes
//            it onto the stack.
void RPNCalc::add_string(istream &input) {
    string new_string = parseRString(input);
    datum_stack.push(Datum(new_string));
}

// Name:      not
// Purpose:   Flips the boolean at the top of the stack
// Arguments: none
// Returns:   none
// Effects:   Pops the top datum on the stack and pushes another datum
//            containing the opposite boolean value onto the stack
void RPNCalc::not_com() {
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else if (not(datum_stack.top().isBool())) {
        datum_stack.pop();
        throw std::runtime_error("Error: datum_not_bool");
    } else if (datum_stack.top().getBool()) {
        datum_stack.pop();
        datum_stack.push(Datum(false));
    } else {
        datum_stack.pop();
        datum_stack.push(Datum(true));
    }
}

// Name:      print
// Purpose:   Prints the top two elements of the stack
// Arguments: none
// Returns:   none
// Effects:   Outputs the information of the top datum on the stack
void RPNCalc::print() {
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else if (datum_stack.top().isInt()) {
        cout << datum_stack.top().getInt() << endl;
    } else if (datum_stack.top().isBool()) {
        if (datum_stack.top().getBool()) {
            cout << "#t" << endl;
        } else {
            cout << "#f" << endl;
        }
    } else {
        cout << datum_stack.top().getRString() << endl;
    }
}

// Name:      dup
// Purpose:   Duplicates the top two elements of the stack
// Arguments: none
// Returns:   none
// Effects:   Another datum containing the top datum's information is pushed
//            onto the stack
void RPNCalc::dup() {
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    }
    Datum new_datum = datum_stack.top();
    datum_stack.push(new_datum);
}

// Name:      swap
// Purpose:   Swaps the top two elements of the stack
// Arguments: none
// Returns:   none
// Effects:   Changes the position of the top two datums on the stack
void RPNCalc::swap() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }
    
    datum_stack.push(Datum(datum_1));
    datum_stack.push(Datum(datum_2));
}

// Name:      addition
// Purpose:   Find the sum of the top two datums on the stack.
// Arguments: none
// Returns:   none
// Effects:   Pops top two datums off the stack, and pushes the result of the
//            operation on the two datums onto the stack.
void RPNCalc::addition() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2.getInt() + datum_1.getInt()));
}

// Name:      subtraction
// Purpose:   Find the difference between the second-to-top datum and the
//            top datum
// Arguments: none
// Returns:   none
// Effects:   Pops top two datums off the stack, and pushes the result of the
//            operation on the two datums onto the stack.
void RPNCalc::subtraction() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2.getInt() - datum_1.getInt()));
}

// Name:      multiplication
// Purpose:   Find the product of the top two datums on the stack.
// Arguments: none
// Returns:   none
// Effects:   Pops top two datums off the stack, and pushes the result of the
//            operation on the two datums onto the stack.
void RPNCalc::multiplication() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2.getInt() * datum_1.getInt()));
}

// Name:      division
// Purpose:   Divides the second-to-top datum on the stack by the top datum
// Arguments: none
// Returns:   none
// Effects:   Pops top two datums off the stack, and pushes the result of the
//            operation on the two datums onto the stack
void RPNCalc::division() {
    Datum datum_1(-1);
    Datum datum_2(-1);

    datum_1 = datum_stack.top();
    datum_stack.pop();

    datum_2 = datum_stack.top();
    datum_stack.pop();

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2.getInt() / datum_1.getInt()));
}

// Name:      mod
// Purpose:   Find the remainder of the second-to-top datum divided by the
//            top datum
// Arguments: none
// Returns:   none
// Effects:   Pops top two datums off the stack, and pushes the result of the
//            operation on the two datums onto the stack.
void RPNCalc::mod() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2.getInt() % datum_1.getInt()));
}

// Name:      less_than
// Purpose:   Checks if the second-to-top datum's int value is less than
//            that of the top datum
// Arguments: none
// Returns:   none
// Effects:   Top 2 datums are popped off of the stack, a datum containing the
//            boolean value of the operation is pushed onto the stack.
void RPNCalc::less_than() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    datum_stack.push(Datum(datum_2 < datum_1));
}

// Name:      greater_than
// Purpose:   Checks if the second-to-top datum's int value is greater than
//            that of the top datum
// Arguments: none
// Returns:   none
// Effects:   Top 2 datums are popped off of the stack, a datum containing the
//            boolean value of the operation is pushed onto the stack.
void RPNCalc::greater_than() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    bool boolean = (not(datum_2 < datum_1)) and (not(datum_2 == datum_1));
    datum_stack.push(Datum(boolean));
}

// Name:      less_or_equal
// Purpose:   Checks if the second-to-top datum's int value is less than or
//            equal to that of the top datum
// Arguments: none
// Returns:   none
// Effects:   Top 2 datums are popped off of the stack, a datum containing the
//            boolean value of the operation is pushed onto the stack.
void RPNCalc::less_or_equal() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    bool boolean = (datum_2 < datum_1) or (datum_2 == datum_1);
    datum_stack.push(Datum(boolean));
}

// Name:      greater_or_equal
// Purpose:   Checks if the second-to-top datum's int value is greater than or
//            equal to that of the top datum
// Arguments: none
// Returns:   none
// Effects:   Top 2 datums are popped off of the stack, a datum containing the
//            boolean value of the operation is pushed onto the stack.
void RPNCalc::greater_or_equal() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    if (not(datum_1.isInt()) or not(datum_2.isInt())) {
        throw std::runtime_error("Error: datum_not_int");
    }

    bool boolean = not(datum_2 < datum_1);
    datum_stack.push(Datum(boolean));
}

// Name:      equal
// Purpose:   Checks if the top two datums are equal
// Arguments: none
// Returns:   none
// Effects:   Top 2 datums are popped off of the stack, a datum containing the
//            boolean value of the operation is pushed onto the stack.
void RPNCalc::equal() {
    Datum datum_1(-1);
    Datum datum_2(-1);
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_1 = datum_stack.top();
        datum_stack.pop();
    }

    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else {
        datum_2 = datum_stack.top();
        datum_stack.pop();
    }

    datum_stack.push(Datum(datum_2 == datum_1));
}

// Name:      exec
// Purpose:   Read in the commands contained in the rstring at the top of
//            the stack.
// Arguments: none
// Returns:   none
// Effects:   Pops a rstring datum off of the stack and runs the commands in
//            that rstring.
void RPNCalc::exec() {
    // Check for errors
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else if (not(datum_stack.top().isRString())) {
        datum_stack.pop();
        throw std::runtime_error("Error: cannot execute non rstring");
    }

    // Get the string from the stack and open it with istringstream
    string com_string = datum_stack.top().getRString();
    datum_stack.pop();
    std::istringstream iss(com_string);

    // Read in commands from the string and run a separate command loop
    string q, skip;
    iss >> skip >> q;
    while (not(iss.eof()) and not(q == "quit") and not(q == "}")) {
        try {
            query_loop(q, iss);
        } catch (const std::runtime_error &e) {
            cerr << e.what() << endl;
        }
        iss >> q;
    }
}

// Name:      open_or_die
// Purpose:   Open a file and ensure no errors arise from this
// Arguments: An unknown streamtype and the name of a file
// Returns:   none
// Effects:   Opens a text file and returns an error if the file could not be
//            opened
template<typename streamtype>
void open_or_die(streamtype &stream, string file_name) {
    stream.open(file_name);
    if (not(stream.is_open())) {
        string err_string = "Unable to read " + file_name;
        throw std::runtime_error(err_string);
    }
}

// Name:      file
// Purpose:   Opens the file which shares the name of the top datum's rstring
//            and passes that file's contents as commands
// Arguments: none
// Returns:   none
// Effects:   Accesses a file and executes the commands in that file
void RPNCalc::file() {
    if (datum_stack.size() == 0) {
        throw std::runtime_error("Error: empty_stack");
    } else if (not(datum_stack.top().isRString())) {
        datum_stack.pop();
        throw std::runtime_error("Error: file operand not rstring");
    }

    // Get the file name and open the file
    string file_string = datum_stack.top().getRString();
    datum_stack.pop();
    std::istringstream iss(file_string);
    string file_name, skip;
    iss >> skip >> file_name;
    ifstream infile;
    open_or_die(infile, file_name);

    // Run a separate command loop for the file
    string q;
    infile >> q;
    while (not(infile.eof()) and not(q == "quit")) {
        try {
            query_loop(q, infile);
        } catch (const std::runtime_error &e) {
            cerr << e.what() << endl;
        }
        infile >> q;
    }
    infile.close();
}

// Name:      if_com
// Purpose:   Pops three datums off of the stack, the first two holding
//            rstrings and the last containing a boolean variable. The first
//            datum popped off executes when the boolean variable is false,
//            and the second executes when it's true.
// Arguments: none
// Returns:   none
// Effects:   Executes a specific rstring depending on another datum's boolean
//            value.
void RPNCalc::if_com() {
    Datum datum_1 = datum_stack.top();
    datum_stack.pop();

    Datum datum_2 = datum_stack.top();
    datum_stack.pop();

    Datum datum_3 = datum_stack.top();
    datum_stack.pop();

    if_helper("bool", datum_3);
    if_helper("rstring", datum_2);
    if_helper("rstring", datum_1);

    if (datum_3.getBool()) {
        datum_stack.push(datum_2);
        exec();
    } else {
        datum_stack.push(datum_1);
        exec();
    }
}

// Name:      if_helper
// Purpose:   Runs exec on a datum object depending on another datum object's
//            boolean value
// Arguments: Three datum objects
// Returns:   none
// Effects:   Pushes the correct datum onto the stack based on the boolean
//            of datum_3 and executes it
void RPNCalc::if_helper(string type, Datum datum) {
    bool typeRString = (type == "rstring");
    bool typeBool = (type == "bool");
    
    if (not(datum.isRString()) and typeRString) {
        throw std::runtime_error("Error: expected rstring in if branch");
    } else if (not(datum.isBool()) and typeBool) {
        throw std::runtime_error("Error: expected boolean in if test");
    }
}