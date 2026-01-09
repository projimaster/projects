/*
 *  unit_tests.h
 *  Justin Projansky (jproja01)
 *  2/26/25
 *
 *  CS 15 PR 2
 *
 *  This file's purpose is to test all member functions of the DatumStack
 *  and RPNCalc classes.
 *
 */

#include <cassert>
#include <sstream>
#include <iostream>
 
#include "Datum.h"
#include "DatumStack.h"
#include "parser.h"
#include "RPNCalc.h"
 
// Tests creation of a DatumStack
void datum_constructor() {
    DatumStack new_stack;
    assert(new_stack.size() == 0);
}
 
// Tests creation of a DatumStack with the array constructor
void datum_constructor_2() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    assert(new_stack.top().getInt() == 6);
    assert(new_stack.size() == 3);
}

// Tests the DatumStack's isEmpty function on an empty stack
void isEmpty_empty() {
    DatumStack new_stack;
    assert(new_stack.isEmpty());
}

// Tests the DatumStack's isEmpty function on a full stack
void isEmpty_full() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    assert(not(new_stack.isEmpty()));
}

// Tests the clear function on an empty stack
void clear_empty() {
    DatumStack new_stack;
    new_stack.clear();

    assert(new_stack.size() == 0);
}

// Tests the clear function on a full stack
void clear_full() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    new_stack.clear();

    assert(new_stack.size() == 0);
}

// Tests the top function on an empty stack
void top_empty() {
    DatumStack new_stack;

    // Var to track whether runtime_error is thrown
    bool runtime_error_thrown = false;

    // Var to track any error messages raised
    std::string error_message = "";

    try {
        new_stack.top();
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    
    assert(new_stack.size() == 0);
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// Tests the top function on a full stack
void top_full() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    assert(new_stack.top().getInt() == 6);
}

// Tests the pop function on an empty stack
void pop_empty() {
    DatumStack new_stack;

    // Var to track whether runtime_error is thrown
    bool runtime_error_thrown = false;

    // Var to track any error messages raised
    std::string error_message = "";
    
    try {
        new_stack.pop();
    } catch (const std::runtime_error &e) {
        runtime_error_thrown = true;
        error_message = e.what();
    }
    
    assert(new_stack.size() == 0);
    assert(runtime_error_thrown);
    assert(error_message == "empty_stack");
}

// Tests the pop function on a full stack
void pop_full() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    new_stack.pop();
    new_stack.pop();

    assert(new_stack.size() == 1);
    assert(new_stack.top().getInt() == 5);
}

// Tests the push function on an empty stack
void push_empty() {
    DatumStack new_stack;

    Datum new_datum = Datum(7);
    new_stack.push(new_datum);

    assert(new_stack.size() == 1);
    assert(new_stack.top().getInt() == 7);
}

// Tests the push function on a full stack
void push_full() {
    Datum data[3] = { Datum(5), Datum(true), Datum(6) };
    DatumStack new_stack(data, 3);

    Datum new_datum = Datum(7);
    new_stack.push(new_datum);

    assert(new_stack.size() == 4);
    assert(new_stack.top().getInt() == 7);
}


// // Tests the add_number function on an empty stack
// void add_num_empty() {
//     RPNCalc test_calc;
//     test_calc.query_loop("2", std::cin);

//     assert(test_calc.datum_stack.top().getInt() == 2);
// }

// // Tests the add_number function on a full stack
// void add_num_full() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     test_calc.query_loop("2", std::cin);

//     assert(test_calc.datum_stack.top().getInt() == 2);
//     assert(test_calc.datum_stack.size() == 5);
// }

// // Tests the add_bool function on an empty stack
// void add_bool_empty() {
//     RPNCalc test_calc;
    
//     test_calc.query_loop("#t", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.query_loop("#f", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }

// // Tests the add_bool function on a full stack
// void add_bool_full() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     test_calc.query_loop("#t", std::cin);
//     assert(test_calc.datum_stack.top().getBool());
//     assert(test_calc.datum_stack.size() == 5);

//     test_calc.query_loop("#f", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
//     assert(test_calc.datum_stack.size() == 6);
// }

// // Tests the add_string function on an empty stack
// void add_string_empty() {
//     RPNCalc test_calc;

//     std::istringstream inputStream (" hi }");
//     test_calc.query_loop("{", inputStream);

//     assert(test_calc.datum_stack.top().getRString() == "{ hi }");
// }

// // Tests the add_string function on a full stack
// void add_string_full() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     std::istringstream inputStream (" hi }");
//     test_calc.query_loop("{", inputStream);

//     assert(test_calc.datum_stack.top().getRString() == "{ hi }");
//     assert(test_calc.datum_stack.size() == 5);
// }

// // Tests the not_com function
// void not_com() {
//     RPNCalc test_calc;

//     test_calc.query_loop("#t", std::cin);
//     test_calc.query_loop("not", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));

//     test_calc.query_loop("#f", std::cin);
//     test_calc.query_loop("not", std::cin);
//     assert(test_calc.datum_stack.top().getBool());
// }

// // Tests the clear command
// void clear_com() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     test_calc.query_loop("clear", std::cin);
//     assert(test_calc.datum_stack.size() == 0);
// }

// // Tests the drop command
// void drop_com() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     test_calc.query_loop("drop", std::cin);
//     assert(test_calc.datum_stack.top().isBool());
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.query_loop("drop", std::cin);
//     assert(test_calc.datum_stack.top().isInt());
//     assert(test_calc.datum_stack.top().getInt() == 3);

//     test_calc.query_loop("drop", std::cin);
//     assert(test_calc.datum_stack.top().isInt());
//     assert(test_calc.datum_stack.top().getInt() == 2);
// }

// // Tests the dup function
// void dup_com() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("dup", std::cin);
//     assert(test_calc.datum_stack.size() == 2);
//     assert(test_calc.datum_stack.top().getInt() == 2);

//     test_calc.query_loop("drop", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 2);
// }

// // Tests the swap function
// void swap_com() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));

//     test_calc.query_loop("swap", std::cin);
//     assert(test_calc.datum_stack.size() == 2);
//     assert(test_calc.datum_stack.top().getInt() == 2);

//     test_calc.query_loop("drop", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 3);
// }

// // Tests the addition function
// void addition() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));

//     test_calc.query_loop("+", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 5);
// }

// // Tests the subtraction function
// void subtraction() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(3));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("-", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 1);
// }

// // Tests the multiplication function
// void multiplication() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));

//     test_calc.query_loop("*", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 6);
// }

// // Tests the division function
// void division() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("/", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 3);
// }

// // Tests the mod function
// void mod() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("mod", std::cin);
//     assert(test_calc.datum_stack.size() == 1);
//     assert(test_calc.datum_stack.top().getInt() == 0);

//     test_calc.datum_stack.push(Datum(7));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("mod", std::cin);
//     assert(test_calc.datum_stack.top().getInt() == 1);
// }

// // Tests the less_than function
// void less() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(6));

//     test_calc.query_loop("<", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("<", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }

// // Tests the greater_than function
// void greater() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(6));

//     test_calc.query_loop(">", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));

//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop(">", std::cin);
//     assert(test_calc.datum_stack.top().getBool());
// }

// // Tests the less_or_equal function
// void less_equal() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(6));

//     test_calc.query_loop("<=", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("<=", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("<=", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }

// // Tests the greater_or_equal function
// void greater_equal() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(6));

//     test_calc.query_loop(">=", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));

//     test_calc.datum_stack.push(Datum(6));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop(">=", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop(">=", std::cin);
//     assert(test_calc.datum_stack.top().getBool());
// }

// // Tests the equal function on integers
// void equal_int() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(2));

//     test_calc.query_loop("==", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(2));
//     test_calc.datum_stack.push(Datum(3));

//     test_calc.query_loop("==", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }

// // Tests the equal function on booleans
// void equal_bool() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum(true));

//     test_calc.query_loop("==", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum(true));
//     test_calc.datum_stack.push(Datum(false));

//     test_calc.query_loop("==", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }

// // Tests the equal function on strings
// void equal_string() {
//     RPNCalc test_calc;
//     test_calc.datum_stack.push(Datum("{ hi }"));
//     test_calc.datum_stack.push(Datum("{ hi }"));

//     test_calc.query_loop("==", std::cin);
//     assert(test_calc.datum_stack.top().getBool());

//     test_calc.datum_stack.push(Datum("{ hi }"));
//     test_calc.datum_stack.push(Datum("{ hello }"));

//     test_calc.query_loop("==", std::cin);
//     assert(not(test_calc.datum_stack.top().getBool()));
// }