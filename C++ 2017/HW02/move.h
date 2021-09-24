/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 21.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the movement definitions                            */
/*--------------------------------------------------------------------------*/

#ifndef HW1_MOVE_H
#define HW1_MOVE_H

#include <iostream>
#include <string.h>
#include "board.h"
#include "check.h"
#include "saveAndLoad.h"

using namespace std;

char getMove(int size, string& fileName); // Gets the letter from user to make move and return that.

// Calls getMove for the letter, getPosition for the index and updates the board.
// Checks all possibilities.
int makeMove(int size , char **board, string& fileName, char players);
int player1(int size, char **board, string& fileName, char players); // Turn of player 1 -> calls makeMove
int player2(int size, char **board, string& fileName, char players); // Turn of player 2 -> calls makeMove
void playTogether(int size, char **board, char players, string& fileName); // Who will play the game? -> user2user or user2computer
int computer(int size, char **board, char playerCharacter, string& fileName, char players); // Play with computer
int getPosition(char character, int size); // Converts the letter to index for first position.
int getLocation(char **board, int size, int position); // Returns the last move's location
void playerComputer(char **board, int size, int move); // Decides behavior of computer

#endif //HW1_MOVE_H
