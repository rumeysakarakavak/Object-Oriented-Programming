/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 19.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This homework is the game of Connect Four                              */
/*   The game of Connect Four is played by two players                      */
/*   (computer-user or user1-user2) on a two dimensional board (2D array)   */
/*   with rectangular cells.                                                */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "board.h"
#include "move.h"


int main() {

    char **board = {};
    int size = boardSize();  // get board size
    char players = playerTo(); // PVP or PVC
    board = initializeBoard(size); // Create board
    playTogether(size, board, players); // Play
    printLetterBoard(size); // Print all
    printBoard(board,size);

    return 0;
}