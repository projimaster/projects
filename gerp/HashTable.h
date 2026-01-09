/*
 *  HashTable.h
 *
 *  Purpose: Interface of the HashTable class. This class copies the
 *           functionality of std::map but with the ability to search for
 *           case-insensitive input
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
 */

#ifndef HASHTABLE__H
#define HASHTABLE__H

#include "IndexingStructs.h"
#include "FSTree.h"
#include "DirNode.h"

#include <vector>
#include <fstream>
#include <functional>
#include <cctype>

using namespace std;

class HashTable {
public:
    HashTable();
    ~HashTable();
    
    int getTableSize();
    void insert(string word, Line *new_line);
    void search(string word, bool sensitive);
    void not_found_output(bool sensitive, string query);

    void setOutputFile(string filename);

    string makeLower(string word);

private:
    vector<vector<Value>> *valueTable;
    int currentTableSize;
    int numItemsInTable;

    hash<string> hash;

    ofstream output;

    void print_sensitive(Value val);
    void print_insensitive(Value val, vector<Line*> &repeated);

    int generateHashIndex(string word);
    float getLoadFactor();
    void expand();
};

#endif