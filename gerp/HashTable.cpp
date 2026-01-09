/*
 *  HashTable.cpp
 *
 *  Purpose: This file implements the HashTable class
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
 */

#include <functional>
#include <cctype>
#include <iostream>
#include <string>

#include "HashTable.h"
#include "IndexingStructs.h"
#include "FSTree.h"
#include "DirNode.h"


// ----------------------  Constructor/Destructor  ---------------------------

/*
 * name:      HashTable
 * purpose:   Constructor for HashTable class; creates a new empty hash table
 * arguments: none
 * returns:   none
 * effects:   none
 */
HashTable::HashTable() {
    currentTableSize = 50;
    numItemsInTable  = 0;

    valueTable = new vector<vector<Value>>;
    for (int i = 0; i < currentTableSize; i++) {
        std::vector<Value> emptyList; 
        valueTable->push_back(emptyList);
    }
}

/*
 * name:      ~HashTable
 * purpose:   Destructor for HashTable class; deletes the hash table
 * arguments: none
 * returns:   none
 * effects:   none
 */
HashTable::~HashTable() {
    delete valueTable;
    valueTable = nullptr;
    output.close();
}

// ---------------------------  public functions  -------------------------

/*
 * name:      getTableSize
 * purpose:   Returns the size of the hash table
 * arguments: none
 * returns:   The value of currentTableSize
 * effects:   none
 */
int HashTable::getTableSize() {
    return currentTableSize;
}

/*
 * name:      insert
 * purpose:   Inserts a single instance of a word into the hash table
 * arguments: word: a string storing the word to be inserted into the table
 *            new_line: a pre-filled Line that represents an instance of the
                        word
 * returns:   none
 * effects:   An element is added to the hash table; if the load factor of the
 *            hash table is higher than 0.75, it is expanded before being
              added to
 */
void HashTable::insert(string word, Line *new_line) {
    while (getLoadFactor() > 0.75) {
        expand();
    }
    
    // makes sure all variations of the word get hashed to the same bucket
    // so that it is easy to implement case insenstive search
    int bucket_index = generateHashIndex(word);

    bool inserted = false;
    
    // checking through every word in the bucket for collisions
    for (int i = 0; i < valueTable->at(bucket_index).size(); i++) {
        // check if the word is already in the bucket and act accordingly
        if (valueTable->at(bucket_index).at(i).word == word) {
            valueTable->at(bucket_index).at(i).locations.push_back(new_line);
            inserted = true;
        }
    }
    
    if (not inserted) {
        Value new_val;
        new_val.word = word;
        new_val.locations.push_back(new_line);
        valueTable->at(bucket_index).push_back(new_val);
        numItemsInTable++;
    }
}

/*
 * name:      search
 * purpose:   Searches the bucket at the index for the given word
 * arguments: The word to be searched for and a boolean stating whether to do
 *            a sensitive or insensitive search.
 * returns:   none
 * effects:   prints to console
 */
void HashTable::search(string word, bool sensitive) {
    int index = generateHashIndex(word);
    bool found = false;
    if (sensitive) {
        for (int i = 0; i < valueTable->at(index).size(); i++) {
            string currentWord = valueTable->at(index).at(i).word;
            if (currentWord == word) {
                print_sensitive(valueTable->at(index).at(i));
                return;
            }
        }
    } else {
        vector<Line*> repeated_lines;
        for (int i = 0; i < valueTable->at(index).size(); i++) {
            string currentWord = valueTable->at(index).at(i).word;
            if (makeLower(currentWord) == makeLower(word)) {
                found = true;
                print_insensitive(valueTable->at(index).at(i), repeated_lines);
            }
        }
    }
    if (not found) {
        not_found_output(sensitive, word);
    }
}

/*
 * name:      not_found_output
 * purpose:   A convenient utility to output the not found output with
 *            an additional helpful message if the search was specified as
 *            sensitive
 * arguments: A boolean storing whether the search was sensitive and a string
 *            storing the query that was inputted
 * returns:   none
 * effects:   prints to console
 */
void HashTable::not_found_output(bool sensitive, string query) {
    if (sensitive) {
        output << query << " Not Found. Try with @insensitive or @i."
               << endl;
    } else {
        output << query << " Not Found." << endl;
    }
}

/*
 * name:      setOutputFile
 * purpose:   Set the output file variable of HashTable to a new output file
 * arguments: The name of the new output file
 * returns:   none
 * effects:   the output file of the ofstream output is changed
 */
void HashTable::setOutputFile(string filename) {
    if (output.is_open()) {
        output.close();
    }
    open_or_die(output, filename);
}

/*
 * name:      makeLowercase
 * purpose:   Turns the word given into its fully lowercase version
 * arguments: word: The string to be made lowercase
 * returns:   The given string in fully lowercase
 * effects:   none
 */
string HashTable::makeLower(string word) {
    string lowercaseWord = word;
    int size = word.size();
    for (int i = 0; i < size; i++) {
        lowercaseWord[i] = tolower(lowercaseWord[i]);
    }
    return lowercaseWord;
}


// ======================  private functions  ============================

/*
 * name:      print_sensitive
 * purpose:   Prints all the details for a given Value struct
 * arguments: val: a Value
 * returns:   none
 * effects:   prints to console
 */
 void HashTable::print_sensitive(Value val) {
    for (int i = 0; i < val.locations.size(); i++) {
        Line *thisLocation = val.locations.at(i);
        File *thisFile = thisLocation->home_file;
        string filePath = thisFile->path;

        int line_num = val.locations.at(i)->line_num;
        string text = val.locations.at(i)->home_file->lines.at(line_num - 1);
        output << filePath << ":" << line_num << ": " << text << endl;
    }
}

/*
 * name:      print_insensitive
 * purpose:   Prints all the details for a given Value struct while making sure
 *            no line is printed twice
 * arguments: val: a Value, repeated: a vector containing all lines printed
 *                                    so far
 * returns:   none
 * effects:   prints to console
 */
void HashTable::print_insensitive(Value val, vector<Line*> &repeats) {
    for (int i = 0; i < val.locations.size(); i++) {
        Line *thisLocation = val.locations.at(i);

        bool repeated = false;
        for (int j = 0; j < repeats.size(); j++) {
            if (thisLocation == repeats.at(j)) {
                repeated = true;
            }
        }
        
        if (not(repeated)) {
            File *thisFile = thisLocation->home_file;
            string filePath = thisFile->path;
            int line_num = val.locations.at(i)->line_num;
            int act_num = line_num - 1;
            string text = val.locations.at(i)->home_file->lines.at(act_num);
            output << filePath << ":" << line_num << ": " << text << endl;
            repeats.push_back(thisLocation);
        }
    }
}

/*
 * name:      getLoadFactor
 * purpose:   Calculates the load factor of the hash table
 * arguments: none
 * returns:   a float between 0 and 1 storing the load factor
 * effects:   none
 */
float HashTable::getLoadFactor() {
    return (float) numItemsInTable / (float) currentTableSize;
}

/*
 * name:      generateHashIndex
 * purpose:   Generates a valid index in the hash table by hashing the given
 *            word
 * arguments: word: The string to be hashed in the hash table
 * returns:   The index where the word should be stored in the hash table
 * effects:   none
 */
int HashTable::generateHashIndex(string word) {
    string lowercaseWord = makeLower(word);
    return hash(lowercaseWord) % currentTableSize;
}

/*
 * name:      expand
 * purpose:   Expands the hash table to accommodate more elements
 * arguments: none
 * returns:   none
 * effects:   Resizes the valueTable to be twice as large and rehashes all the
 *            elements that were in it
 */
void HashTable::expand() {
    // Save old table and old size
    vector<vector<Value>> *oldTable = valueTable;
    int oldSize = currentTableSize;

    // Make the new table with an expanded size
    currentTableSize = oldSize * 2 + 2;
    valueTable = new vector<vector<Value>>;

    // Initialize the new table with empty buckets
    for (int i = 0; i < currentTableSize; i++) {
        std::vector<Value> emptyList; 
        valueTable->push_back(emptyList);
    }
    numItemsInTable = 0;

    // Rehash and re-insert all values from the hash table into the new table
    for (int i = 0; i < oldSize; i++) {
        for (int j = 0; j < oldTable->at(i).size(); j++) {
            string word = oldTable->at(i).at(j).word;
            Value val = oldTable->at(i).at(j);
            
            int newIndex = generateHashIndex(word);
            valueTable->at(newIndex).push_back(val);
            numItemsInTable++;
        }
    }

    delete oldTable;
}