/*
 *  IndexingStructs.h
 *
 *  Purpose: Provides three structs that are used to index the files the
 *           program needs to process:
 *              - File: stores the filepath as a string and all the lines in
 *                      the text in a vector of strings
 *              - Line: stores a pointer to its associated File and the line
 *                      number in the file at which the line appears
 *              - Value: the actual word that will be stored in the hash
 *                       table; contains the word as a string and a vector
 *                       of Lines in which the word appears
 *          Also provides the open_or_die function, which checks if a file
 *          can be opened. 
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
*/

#include <string>
#include <vector>

#ifndef INDEXINGSTRUCTS_H_
#define INDEXINGSTRUCTS_H_

struct File {
    std::string path;
    std::vector<std::string> lines;
};

struct Line {
    File *home_file;
    int line_num;
};

struct Value {
    std::string word;
    std::vector<Line*> locations;
};


// Name:      open_or_die
// Purpose:   Open a file and ensure no errors arise from this
// Arguments: An unknown streamtype and the name of a file
// Returns:   none
// Effects:   Opens a text file and returns an error if the file could not be
//            opened, and stops the program if the given file is empty.
template<typename streamtype>
void open_or_die(streamtype &stream, const std::string &inputFile) {
    stream.open(inputFile);
    if (not(stream.is_open())) {
        std::string err_string = "Unable to open file " + inputFile;
        throw std::runtime_error(err_string);
    }
}

#endif