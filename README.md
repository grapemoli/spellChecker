# Spell-Checking & Word Suggestion

## Goal:
Given a user input, return if the word is valid (in the table), or not. In the case that the user misspells the word, provide a word suggestion.

## User Instructions:
For ease, a makefile is provided. After making use of the makefile, run the program by the 'make run' command.

The user will be taken to a menu screen.

If the user inputs 0, the program ends.

If the user inputs 1, the user will be asked to input a word. The user can input a string if they'd like. This program attempts to handle spaces and lowercase/uppercase letters.

There are three cases that can happen after the user inputs a word:
1) the input, after ridding of all spaces and forced to lowercase, exists in the table. In this case, the user will be told that the word exists, and the time for the search to occur is printed. The user is returned to the main menu.
2) the input, after ridding of all spaces and forced to lowercase, does not directly exist in the table, but a similar match was found. The user is asked if this match is what they attempted to type. If 'yes' is inputted, the user is printed the time the search took to occur is printed. The user returns to the main menu. If 'no' is inputted, the user will be printed all entries in the table that start with the first two letters. The user is returned to the main menu.
3) the input, after ridding of all spaces and forced to lowercase, does not directly exist in the table and no 'similar' matches were found. The user is informed that their input could not be found and is returned to the main menu.
