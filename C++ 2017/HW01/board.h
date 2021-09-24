/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 19.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the board definitions                               */
/*--------------------------------------------------------------------------*/
#ifndef HW1_BOARD_H
#define HW1_BOARD_H


int boardSize(); // Get the size of board from user.
char** initializeBoard(int size); // First look at the game board
int updateBoard(char **board, int size, char character, int position);  // Updates board after every move.
char playerTo(); // Ask the game will be played among whom
void printLetterBoard(int size); // Prints letter border
void printBoard(char **board, int size); // Prints all board
int checkAllBoard(char **board, int size);  // Checks the whether the board is full or not


#endif //HW1_BOARD_H
