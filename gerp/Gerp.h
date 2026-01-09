/*
 *  Gerp.h
 *
 *  Purpose: Interface of the Gerp class. This class indexes the subdirectories
 *           and files present in the directory provided by the user and
 *           implements the functionality to search through the files for
 *           individual words.
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
*/

#ifndef GERP_H_
#define GERP_H_


#include <iostream>
#include <string>
#include "HashTable.h"
#include "FSTree.h"
#include "DirNode.h"
#include "IndexingStructs.h"

class Gerp {
public:
    void index(std::string index_directory);
    void query_loop(std::string output_file);
private:
    HashTable hash_table;

    void word_search(string the_word, bool sensitive);

    string stripNonAlphaNum(std::string input);
    
    void traverseDirectory(std::string directory);
    void recursiveTraversing(DirNode *root, string path);

    void read_file(std::string path);
    void read_line(std::string line, int line_num, File *file_p);

    void recycle();

    vector <Line*> allLines;
    vector <File*> allFiles;
};

#endif