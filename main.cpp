/*
File: main.cpp
By: Grace Nguyen
Date: 05 November 3033

Purpose: use a hash table to create a dictionary
*/


#include <iostream>
#include "table.h"


// fuction prototype
void userMenu();
std::string getUserInput(bool getWord);


int main() {
    userMenu();
} // end main


// userMenu() def
void userMenu() {
    Table dict("Dictionary.txt");

    // user menu
    bool keepGoing = true;
    while(keepGoing) {
        std::string userInput;

        std::cout << "\n\n********** Spell Checker **********\n1) Check for a Word\n2. Get all for a Letter\n0) Quit\nChoose an option: ";
        std::cin >> userInput;

        if(userInput == "0"){
            keepGoing = false;
        }else if(userInput == "1"){
            std::string wordInput = getUserInput(true);
            bool inputExists = dict.checkInput(wordInput);
        }else if(userInput == "2"){
            std::string charInput = getUserInput(false);
            dict.printAllLetter(charInput);
        }else{
            std::cout << "Invalid input. Try again!\n";
        } // end if-else

    } // end while
} // end userMenu


std::string getUserInput(bool getWord) {
    // get user input for a word if getWord == true
    // else, get user input for a character
    std::string input;

    if(getWord == true) {
        std::cout << "\n_____\n\nInput a word: ";
    }else{
        std::cout << "\n_____\n\nInput a char: ";
    } // end if-else

    // get user input; allow for inputs with spaces
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // allow for spaces in input
    std::getline(std::cin, input, '\n');

    // return only the first char if user inputs a word for char input
    if(getWord == false) {
        input = input[0];
    } // end if

    return(input);

} // end getUserInput