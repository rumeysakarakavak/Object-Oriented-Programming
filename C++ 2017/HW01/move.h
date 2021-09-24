/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 21.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the movement definitions                            */
/*--------------------------------------------------------------------------*/

#ifndef HW1_MOVE_H
#define HW1_MOVE_H

char getMove(int size); // Gets the letter from user to make move and return that.

// Calls getMove for the letter, getPosition for the index and updates the board.
// Checks all possibilities.
int makeMove(int size , char **board);
int player1(int size, char **board); // Turn of player 1 -> calls makeMove
int player2(int size, char **board); // Turn of player 2 -> calls makeMove
void playTogether(int size, char **board, char players); // Who will play the game? -> user2user or user2computer
int computer(int size, char **board, char playerCharacter); // Play with computer
int getPosition(char character, int size); // Converts the letter to index for first position.
int getLocation(char **board, int size, int position); // Returns the last move's location
void playerComputer(char **board, int size, int move); // Decides behavior of computer

#endif //HW1_MOVE_H
