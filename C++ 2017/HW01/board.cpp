/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 19.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the board functions implementations                 */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "board.h"
#include "check.h"

// Get the size of board from user.
int boardSize() {

    std :: cout << "Enter the board n size \nIt must be from 4 to 20 and even" << std :: endl;
    int nSize;
    std :: cin >> nSize;
    while ((!(nSize >= 4 && nSize <= 20) || nSize % 2 == 1)){
        std :: cout << "Please enter from 4 to 20 and even" << std :: endl;
        std :: cin.clear();
        std :: cin.ignore(512, '\n');
        std :: cin >> nSize;

    }
    return  nSize;
}
// First look at the game board
char** initializeBoard(int size) {
    // game board maker
    auto **gameBoard = (char **) malloc((size) * sizeof(char*));
    for (int i=0; i<size ; i++)
        gameBoard[i] = (char *)malloc((size) * sizeof(char*));

    // game board initializer
    printLetterBoard(size);
    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size; ++j) {
            gameBoard[i][j] = '.';
            std::cout << gameBoard[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    return gameBoard;
}
// Ask the game will be played among whom
char playerTo() {
    std :: cout << "For PvP :P\nFor PvC :C"<< std :: endl;
    char players;
    std :: cin >> players;
    while(players != 'P' && players != 'p' && players != 'C' && players != 'c'){
        std :: cout << "Please enter P or C" << std :: endl;
        std :: cin >> players;
    }
    return players;
}
// Updates board after every move.
int updateBoard(char **board, int size, char character, int position) {

    int columnPosition = position % size;
    auto rowPosition = static_cast<int> (position / size);
    int illegalMove = 0;

    if (board[rowPosition][columnPosition] == 'X' || board[rowPosition][columnPosition] == 'O') {
        while (rowPosition >= 0 && board[rowPosition][columnPosition] != '.') {
            rowPosition--;
            if (rowPosition < 0) {
                std::cout << "Illegal move\nTry another one!" << std::endl;
                illegalMove = 1;
            }
        }
        if (illegalMove != 1) { board[rowPosition][columnPosition] = character; };
    }
    else if (board[rowPosition][columnPosition] == '.') {
        board[rowPosition][columnPosition] = character;
    }

    if (illegalMove != 1) {
        printLetterBoard(size);
        printBoard(board,size);
    }
    return illegalMove;
}
// Prints letter border
void printLetterBoard(int size){

    char letterBoard[size];
    int firstLetter = 'A';
    for (int i = 0; i < size ; ++i) {
        letterBoard[i] = static_cast<char>(firstLetter);
        firstLetter ++;
        std :: cout << letterBoard[i]<< "  ";
    }
    std :: cout << std :: endl;
}
// Prints all board
void printBoard(char **board, int size) {

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
// Checks the whether the board is full or not
int checkAllBoard(char **board, int size) {

    int full = 0;
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(board[i][j] != '.'){
                ++count;
            }
        }
    }
    if(count == size * size){
        full = 1;
        std :: cout << "Scoreless" << std :: endl;
    }
    return full;
}

