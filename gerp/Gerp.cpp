/*
 *  Gerp.cpp
 *
 *  Purpose: This file implements the Gerp class.
 *  
 *  Authors: Justin Projansky (jproj01), Joon Heo (jheo03)
 *  Date: 4/21/25
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Gerp.h"
#include "HashTable.h"
#include "IndexingStructs.h"
#include "FSTree.h"
#include "DirNode.h"


/*
 * name:      index
 * purpose:   Traverses the given directory and adds all found words to the
 *            hash table.
 * arguments: The name of the directory to index
 * returns:   none
 * effects:   Adds all words in the files of the directory to the hash table,
 *            stores every line of every file to be accessed later.
 */
void Gerp::index(std::string index_directory) {
    traverseDirectory(index_directory);
}

/*
 * name:      query_loop 
 * purpose:   Handles user input from the console in a loop
 * arguments: output_file: string storing the name of the file to output to
 * returns:   none
 * effects:   Calls helper functions that implement the actions requested by
              the user
 */
void Gerp::query_loop(string output_file) {
    cout << "Query? ";
    string query;
    cin >> query;
    hash_table.setOutputFile(output_file);

    while (cin and query != "@q" and query != "@quit") {
        if (query == "@i" or query == "@insensitive") {
            cin >> query;
            string stripped_query = stripNonAlphaNum(query);
            word_search(stripped_query, false);
        } else if (query == "@f") {
            cin >> query;
            hash_table.setOutputFile(query);
        } else {
            string stripped_query = stripNonAlphaNum(query);
            word_search(stripped_query, true);
        }
        cout << "Query? ";
        cin >> query;
    }
    cout << "Goodbye! Thank you and have a nice day." << endl;
    recycle();
    return;
}

/*
 * name:      word_search 
 * purpose:   Searches the index for the given word
 * arguments: The word to be searched for in the directory and a boolean
 *            stating whether to do a sensitive or insensitive search
 * returns:   none
 * effects:   Outputs all  instances of the given string in the provided
 *            directory based on the given sensitive/insensitive criteria
 */
void Gerp::word_search(string query, bool sensitive) {
    if (query != "") {
        hash_table.search(query, sensitive);
    } else {
        hash_table.not_found_output(sensitive, query);
    }
}

/*
 * name:      stripNonAlphaNum
 * purpose:   Takes a string and removes all leading/trailing non-alphanumeric
 *            characters.
 * arguments: An input string
 * returns:   The input string without any leading/trailing non-alphanumeric
 *            characters.
 * effects:   none
 */
string Gerp::stripNonAlphaNum(std::string input) {
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
    
/*
 * name:      traverseDirectory
 * purpose:   Takes a directory as an argument and prints the full paths of all
 *            files accessible from that directory.
 * arguments: The name of a directory
 * returns:   none
 * effects:   Prints the paths of every file accessible from the given
 *            directory.
 */
void Gerp::traverseDirectory(std::string directory) {
    FSTree new_tree(directory);
    DirNode *root = new_tree.getRoot();
    recursiveTraversing(root, "");
}

/*
 * name:      recursiveTraversing
 * purpose:   Recursively traverses the files and subdirectories in the root
 *            directory, calling read_file for every file found.
 * arguments: A node of a file and a string containing the path so far
 * returns:   none
 * effects:   Prints the path of the given node.
 */
void Gerp::recursiveTraversing(DirNode *node, string path) {
    if (path != "") {
        path += "/";
    }
    path += node->getName();
    
    if (node->hasFiles()) {
        for (int i = 0; i < node->numFiles(); i++) {
            string new_path = path + "/" + node->getFile(i);
            read_file(new_path);
        }
    }

    if (node->hasSubDir()) {
        for (int i = 0; i < node->numSubDirs(); i++) {
            recursiveTraversing(node->getSubDir(i), path);
        }
    }
}

/*
 * name:      read_file
 * purpose:   Adds all words from a given file to a hash table
 * arguments: The name of the file to be searched
 * returns:   none
 * effects:   Adds all words from the file to the hash table
 */
void Gerp::read_file(string path) {
    File *new_file = new File;
    new_file->path = path;
    allFiles.push_back(new_file);

    ifstream infile;
    open_or_die(infile, path);

    string line;
    int count = 0;
    while (getline(infile, line)) {
        count++;
        new_file->lines.push_back(line);
        read_line(line, count, new_file);
    }
    infile.close();
}

/*
 * name:      read_line
 * purpose:   Adds all words from a given line
 * arguments: The contents of the line being searched, the line's number, and a
 *            pointer to the line's home file.
 * returns:   none
 * effects:   Adds all words from the line to the hash table
 */
void Gerp::read_line(string line, int line_num, File *file_p) {
    Line *new_line = new Line;
    new_line->home_file = file_p;
    new_line->line_num = line_num;
    allLines.push_back(new_line);

    std::istringstream iss(line);
    string word;

    vector<string> repeats;
    while (iss >> word) {
        string better_word = stripNonAlphaNum(word);
        bool is_repeated = false;
        for (int i = 0; i < repeats.size(); i++) {
            if (repeats.at(i) == better_word) {
                is_repeated = true;
            }
        }
        if (not(is_repeated) and better_word != "") {
            repeats.push_back(better_word);
            hash_table.insert(better_word, new_line);
        }
    }
}

/*
 * name:      recycle 
 * purpose:   Recycles all lines and files allocated on the heap
 * arguments: none
 * returns:   none
 * effects:   Deletes the data allocated on the heap
 */
void Gerp::recycle() {
    for (int i = 0; i < allLines.size(); i++) {
        delete allLines.at(i);
    }
    
    for (int i = 0; i < allFiles.size(); i++) {
        delete allFiles.at(i);
    }
}