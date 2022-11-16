/*
File: table.h
By: Grace Nguyen
Date: 05 November 2022

Purpose: header guard for hash table
*/


#ifndef TABLE_H_EXISTS
#define TABLE_H_EXISTS
#include <vector>
#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include<sstream>

class Table {
    private:
        std::vector<std::vector<std::string>> table;
    public:
        // constructor
        Table(std::string file);

        // access methods
        void setTable(std::string file);
        std::vector<std::vector<std::string>> getTable();

        // hash method
        void hashString(std::string str);

        // spell-checking methods
        std::string closestMatch(std::string input);
        int getWordIndex(std::string input);
        void charMatch(std::string input, std::string currentEntry, int* counter);
        void wrongChar(std::string input, std::string currentEntry, int* counter);

        // user-input method
        bool checkInput(std::string input);
        void listMatchingTwo(std::string input);
        void printAllLetter(std::string input);
}; // end Table


#endif
