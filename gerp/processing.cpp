/*
 *  processing.h
 *  Part of CS15 project gerp
 *
 *  Purpose: This file implements the functions declared in processing.h
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/12/25
 */

#include <iostream>
#include <string>
#include <cctype>
  
#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"
 
using namespace std;
 
// Name:      stripNonAlphaNum
// Purpose:   Takes a string and removes all leading/trailing non-alphanumeric
//              characters.
// Arguments: An input string
// Returns:   The input string without any leading/trailing non-alphanumeric
//              characters.
// Effects:   none
string stripNonAlphaNum(string input) {
    int start = 0;
    int end = input.length() - 1;

    while ((not isalnum(input[start])) and (start <= end)) {
        start = start + 1;
    }
    while ((not isalnum(input[end])) and (end >= start)) {
        end = end - 1;
    }
    
    return input.substr(start, end - start + 1);
}


// Name:      traverseDirectory
// Purpose:   Takes a directory as an argument and prints the full paths of all
//              files accessible from that directory.
// Arguments: The name of a directory
// Returns:   none
// Effects:   Prints the paths of every file accessible from the given
//              directory.
void traverseDirectory(string directory) {
    FSTree new_tree(directory);
    DirNode *root = new_tree.getRoot();
    recursiveTraversing(root, "");
}

// Name:      recursiveTraversing
// Purpose:   Prints the path of a file from a given directory.
// Arguments: A node of a file and a string containing the path so far
// Returns:   none
// Effects:   Prints the path of the given node.
void recursiveTraversing(DirNode *node, string path) {
    if (path != "") {
        path += "/";
    }
    path += node->getName();
    
    if (node->hasFiles()) {
        for (int i = 0; i < node->numFiles(); i++) {
            cout << path << "/" << node->getFile(i) << endl;
        }
    }

    if (node->hasSubDir()) {
        for (int i = 0; i < node->numSubDirs(); i++) {
            recursiveTraversing(node->getSubDir(i), path);
        }
    }
}