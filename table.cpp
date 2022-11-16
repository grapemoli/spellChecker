/*
File: Table.cpp
By: Grace Nguyen
Date: 05 November 2022

Purpose: implement a hash table 
*/


#include "table.h"
#include "TimeInterval.h"


/* 
    CONSTRUCTOR
*/
Table::Table(std::string file) {
    // initialize table to contain 26 empty vectors 
    for(int i = 0; i < 26; i++) {
        std::vector<std::string> temp;
        this->table.push_back(temp);
    } // end for

    // create hashtable
    setTable(file);
} // end constructor


/*
    ACCESS METHODS
*/
std::vector<std::vector<std::string>> Table::getTable() {
    return(this->table);
} // end getTable

void Table::setTable(std::string file) {
    // read file, hash each string in table
    std::stringstream ss;
    std::string currentLine;

    // open file and read
    std::ifstream inFile;
    inFile.open(file);

    while(std::getline(inFile, currentLine)) {
        // just in case: double clear sstream
        ss.clear();
        ss.str("");
        ss.str(currentLine);

        // hash value into table
        hashString(currentLine);
    } // end while

    // close file connection
    inFile.close();
} // end setTable


/*
    HASHING METHOD
*/
void Table::hashString(std::string input) {
    // hash function: ASCII of first letter - 97
    int hashIndex = tolower(input[0]) - 97;

    // clean up string (precautionary measure)
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end()); // no white space
    input.erase(std::remove(input.begin(), input.end(), '\n'), input.end()); // not \n
    input.erase(std::remove(input.begin(), input.end(), '\r'), input.end()); // no carriage returns

    // hash into table
    this->table[hashIndex].push_back(input);
} // end hashString


/*
    SPELL-CHECKING METHODS
*/
int Table::getWordIndex(std::string input) {
    // returns -1 if the input does not match with any table entries 

    // clean the input by:
    // 1. forcing input to be lowercase
    std::transform(input.begin(), input.end(), input.begin(), ::tolower);
    
    // 2. stripping input of white spaces
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // get hashing index of the input, compare input to vector elements
    int hashIndex = tolower(input[0]) - 97;
    std::vector<std::string> tempVector = this->table[hashIndex];
    int wordIndex = -1;
    
    for(int i = 0; i < tempVector.size(); i++) {
        // precautionary measure: compare lowercased-current element
        std::string currentElement = tempVector[i];
        std::transform(currentElement.begin(), currentElement.end(), currentElement.begin(), ::tolower);

        if(input == currentElement) {
            wordIndex = i;       
        } // end if
    } // end for

    return(wordIndex);
} // end wordIndex

void Table::charMatch(std::string input, std::string currentEntry, int* counter) {
    // returns 1 if the first characters match; return 0 elsewhere
    // base case: we have reached the end of the input and currentEntry string
    if(input != "" && currentEntry != "") {
        if(input[0] == currentEntry[0]) {
            input.erase(0,1);
            currentEntry.erase(0,1);
            charMatch(input, currentEntry, counter);
            (*counter)++;
        }else{
            // check if we should move forward the currentEntry or the input:
            /*  LOGIC:
                if we can find the first char of currentEntry in input, 
                then remove the appearance of the char in input and currentEntry, and move on.
            */
            if(input.find(currentEntry[0]) != std::string::npos) {
                int inputIndex = input.find(currentEntry[0]);
                input.erase(inputIndex, inputIndex+1);
                currentEntry.erase(0,1);
                (*counter)++;
            }else{
                if(currentEntry.find(input[0]) != std::string::npos) {
                    currentEntry.erase(0,1);
                }else{ 
                    // first char of each string is unique to that respective string. move on.
                    currentEntry.erase(0,1);
                    input.erase(0,1);
                } // end if-else
            } // end if-else
            charMatch(input, currentEntry, counter);
        } // end if-else
    } // end if
} // end charMatch

void Table::wrongChar(std::string input, std::string currentEntry, int* counter) {
    // base case: input is empty
    if(input != "") {
        // if you cannot find input letter in current entry, it's a 'wrong char'
        // decrease from counter (a 'punishment' system)
        if(currentEntry.find(input[0]) == std::string::npos) {
            (*counter)--;
        } // end if-else

        input.erase(0,1);
        wrongChar(input, currentEntry, counter);
    } // end if
} // end wrongChar

std::string Table::closestMatch(std::string input) {
    // this algorithm finds the "closest" data entry by utilizing a 
    // detrimenting system for "wrong" letters in the passed input
    std::string closestMatch = "";
    int closestMatchDifference = 0;

    int hashIndex = tolower(input[0]) - 97;
    std::vector<std::string> tempVector = this->table[hashIndex];
    
    for(int i = 0; i < tempVector.size(); i++) {
        int wrongChars = 0; 
        int rightChars = 0;
        std::string currentEntry = tempVector[i];
        wrongChar(input, currentEntry, &wrongChars);
        charMatch(input, currentEntry, &rightChars);
        
        // only consider differences that are greater than 0!
        int difference = rightChars + wrongChars;

        if(difference > 0 && difference > closestMatchDifference) {
            closestMatchDifference = difference;
            closestMatch = currentEntry;
        } // end if
    } // end for

    return(closestMatch);
} // end closestMatch


/*
    USER-INPUT METHODS
*/
void Table::listMatchingTwo(std::string input) {
    // list all entries that have the same first two letters
    // NOT inclusive of the input!!
    std::string printedOutput = "";
    // clean input
    std::transform(input.begin(), input.end(), input.begin(), ::tolower); 
    input.erase(std::remove(input.begin(), input.end(), ' '), input.end());

    // get hashing index
    int hashIndex = tolower(input[0]) - 97;
    std::vector<std::string> tempVector = this->table[hashIndex];

    // loop through all entries, printing if second letter matches
    std::cout << "\nOther Possible Matches:\n";
    for(int i = 0; i < tempVector.size(); i++) {
        std::string currentEntry = tempVector[i];
        std::transform(currentEntry.begin(), currentEntry.end(), currentEntry.begin(), ::tolower); 

        if(currentEntry != input) { // only print if not the same word
            if(currentEntry.find(input[1]) != std::string::npos) {
                if(currentEntry.find(input[1]) == 1) {
                    printedOutput = printedOutput + "\t- " + currentEntry + "\n"; 
                } // end if
            } // end if
        } // end if
    } // end for

    if(printedOutput == "") {
        std::cout << "-no other possible matches-\n";
    }else{
        std::cout << printedOutput;
    } // end if-else
} // end listMatchingTwo

bool Table::checkInput(std::string input) {
    TimeInterval time; // timer
    time.start();
    bool inputCorrect = false; // to be returned
    int inputIndex = getWordIndex(input); // get index
    
    if(inputIndex != -1) { 
        // CASE 1: word exists in the vector
        time.stop();
        std::cout << "\nTrue. Word Exists!\nTime (ms): " << time.GetInterval() << "\n_____\n";
        inputCorrect = true;
        
        time.start();
        listMatchingTwo(input);
        time.stop();
        std::cout << "Time (ms): " << time.GetInterval() << "\n";
    }else{  
        std::string closestWord = closestMatch(input);
        time.stop();

        if(closestWord != "") {
            // CASE 2: word is misspelled
            time.stop();
            std::string rightWord;
            std::cout << "\nTime (ms): " << time.GetInterval() << "\nDid you mean '" << closestWord << "'? (yes/no) ";
            std::cin >> rightWord;
            std::transform(rightWord.begin(), rightWord.end(), rightWord.begin(), ::tolower);
            rightWord.erase(std::remove(rightWord.begin(), rightWord.end(), ' '), rightWord.end());

            if(rightWord == "yes"){
                // list all words that start with same two letters (exclusive of if the same word)
                time.start();
                listMatchingTwo(closestWord);
                time.stop();
                std::cout << "Time (ms): " << time.GetInterval() << "\n_____\n";
                inputCorrect = true;
            }else if(rightWord == "no"){
                std::cout << "Returning to menu...\n_____\n";
                inputCorrect = false;
            }else{
                std::cout << "Invalid input. Returning to main menu...\n_____\n";
            } // end if-else
        }else{
            // CASE 3: word does not exist in the vector
            std::cout << "False. No matching or similar entries!\nTime (ms): " << time.GetInterval() << "\n_____\n";
        } // end if-else
    } // end if-else
    
    return(inputCorrect);

} // end getUserInput

void Table::printAllLetter(std::string input) {
    // print all of the entries with the same first letter
    TimeInterval time;
    time.start(); // start timer
    
    int hashIndex = tolower(input[0]) - 97;
    std::vector<std::string> tempVector = this->table[hashIndex];

    std::cout << "\nAll Matches For " << input << ":\n";

    for(int i = 0; i < tempVector.size(); i++) {
        std::cout << "\t- " << tempVector[i] << "\n";
    } // end for

    time.stop(); // end timer
    std::cout << "\nTime (ms): " << time.GetInterval() << "\n";
} // end printAllLetter


