# Spell-Checking & Word Suggestion

## Goal:
Given a user input, return if the word is valid (in the table), or not. In the case that the user misspells the word, provide a word suggestion.

## User Instructions:
For ease, a makefile is provided. After making use of the makefile, run the program by the 'make run' command.

The user will be taken to a menu screen.
1. If the user inputs 0, the program ends.

2. If the user inputs 1, the user will be asked to input a word. The user can input a string if they'd like. This program attempts to handle spaces and lowercase/uppercase letters. From here, there are three cases that can happen.
- Case One: user word exists. The user is told the word exists and are printed the algorithm time in milliseconds. The user is also printed all words that start with the same first two letters.
- Case Two: user word does not exist but a similar word exists. The alogorithm time and similar word is outputted, and the user is asked if this is what they meant. If the user responds "yes," then all the words that have the first same two letters as the 'correct' spelling is outputted.
- Case Three: user word does not exist and not similar word exists. The user is told no similar word exists and they are printed the algorothm time in miliseconds.

3. If the user inputs 2, the user will be asked to input a character. The program will accept a word or phrase, but only the first character will be read. All hashed entries that start with the same letter is outputted (if applicable), and the algorithm time is outputted.

