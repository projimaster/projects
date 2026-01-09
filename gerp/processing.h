#ifndef __PROCESSING_H
#define __PROCESSING_H

/*
 *  processing.h
 *  Part of CS15 project gerp
 *
 *  Purpose: This is the header file for two functions that will be used to
 *           implement gerp. stripNonAlphaNum strips all nonalphanumeric
 *           characters from both ends of a string and traverseDirectory prints
 *           prints all the files in the specified directory and in all its
 *           subdirectories.
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/12/25
 */

#include <iostream>
#include <string>
#include <cctype>
#include "DirNode.h"
#include "FSTree.h"
using namespace std;

string stripNonAlphaNum(string input);
void traverseDirectory(string directory);
void recursiveTraversing(DirNode *root, string path);

#endif