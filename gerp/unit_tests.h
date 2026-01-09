/*
 *  unit_tests.h
 *  Part of CS15 project gerp
 *
 *  Purpose: Works in conjunction with the unit_test framework to run unit
 *           tests on the functions we provide
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/12/25
 */

#include <iostream>
#include <string>
#include <cassert>
#include <fstream>

#include "Gerp.h"
#include "HashTable.h"
#include "IndexingStructs.h"
#include "processing.h"


// =====================================================================
// =                              phase 1                              =
// =                (testing the functions in processing)              =
// =====================================================================

// --------------------  stripNonAlphaNum  -----------------------------

void strip_single_char() {
    std::string str = "*";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "");
}

void strip_short() {
    std::string str = "$%testing#$";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "testing");
}

void strip_long() {
    std::string str = "$%*@#$*&*helloworld:)hello!#$*@#$&@#$";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "helloworld:)hello");
}

void strip_empty() {
    std::string str = "$%*@#$*&*@#$%&@#$*@#$&@#$";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "");
}

void strip_empty_2() {
    std::string str = "";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "");
}

void strip_normal() {
    std::string str = "Hello";
    std::string stripped = stripNonAlphaNum(str);
    assert(stripped == "Hello");
}


// --------------------  traverseDirectory  -----------------------------

void traversing_tiny() {
    traverseDirectory("/comp/15/files/proj-gerp-test-dirs/tinyData");
}

void traversing_not_tall() {
    traverseDirectory("/comp/15/files/proj-gerp-test-dirs/smallGutenberg");
}

void traversing_medium() {
    traverseDirectory("/comp/15/files/proj-gerp-test-dirs/mediumGutenberg");
}




// =======================================================================
// =                            Phase 2                                  =
// =======================================================================

// =========================  HashTable  =================================

// ---------------------  Changing Output File  ---------------------------

ofstream output;

// FUNCTION TO TEST:
// switches an output file
void setOutputFile(string filename) {
    if (output.is_open()) {
        output.close();
    }
    output.open(filename);

}

// switches the file held by the ofstream output to various filenames
void switchThatOutputFile() {
    setOutputFile("fileSwitcher1.test");
    output << "This is a test" << endl;
    setOutputFile("fileSwitcher2.test");
    output << "Do not be alarmed" << endl;
    output.close();
    setOutputFile("fileSwitcher3.test");
    output << ":)" << endl;
    output.close();
}

// -------------------  Making a string lowercase  --------------------------

// FUNCTION TO TEST:
// makes a string entirely lowercase
string makeLower(string word) {
    string lowercaseWord = word;
    int size = word.size();
    for (int i = 0; i < size; i++) {
        lowercaseWord[i] = tolower(lowercaseWord[i]);
    }
    return lowercaseWord;
}

// Tests the makeLower function with the alphabet
void convert_to_lower_alphabet() {
    assert(makeLower("ABCDEFGHIJKLMNOPQRSTUVWXYZ")
           == "abcdefghijklmnopqrstuvwxyz");
}

// Tests the makeLower function with a random alphanumeric string
void convert_to_lower_alphanumeric() {
    assert(makeLower("AIUY3498Sfg345987AG") == "aiuy3498sfg345987ag");
}

