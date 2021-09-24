/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 3.10.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the file functions implementations                  */
/*--------------------------------------------------------------------------*/
#include "saveAndLoad.h"

// opens a file and writes the latest version of the board.
void saveFile(const string &fileName, char **board, int size, char players){

    ofstream outputStream;
    outputStream.open(fileName);
    // file is open?
    if (!outputStream.is_open()) {
        cerr << "Input file could not be opened: " << fileName << endl;
        exit (-1);
    }
    // write the size of the board
    outputStream << size ;
    // write p or c
    outputStream << players;
    // write all board to file.
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            outputStream << board[i][j] << "  ";
        }
        outputStream << endl;
    }

    outputStream.close();
}
// Reads the file and loads the status of board.
char** loadFile(const string &fileName, char **newBoard){

    ifstream inputStream;
    int newSize = 0;
    char player = 0;
    // File is open?
    inputStream.open(fileName);
    if (!inputStream.is_open()) {
        cerr << "Input file could not be opened: " << fileName << endl;
        exit (-1);
    }
    // size of board
    inputStream >> newSize;
    // p or c for the new game
    inputStream >> player;
    // initialize board.
    newBoard = (char **) malloc((newSize) * sizeof(char*));
    for (int i=0; i< newSize + 1 ; i++)
        newBoard[i] = (char *)malloc((newSize) * sizeof(char*));

    for (int i = 1; i < newSize + 1; ++i) {
        for (int j = 0; j < newSize; ++j) {
            inputStream >> newBoard[i][j];
        }
    }
    // size of board
    newBoard[0][0] = newSize;
    // p or c for the new game
    newBoard[0][1] = player;

    // print the new board
    printLetterBoard(newSize);
    for (int i = 1; i < newSize + 1; ++i) {
        for (int j = 0; j < newSize; ++j) {
            std::cout << newBoard[i][j] << "  ";
        }
        std::cout << std::endl;
    }
    inputStream.close();
    return  newBoard;
}
// Parses command line. Returns SAVE, LOAD or A, B etc. and filename &reference
string parseCommandLine(string &fileName) {
    string command;
    cin.clear();
    getline(cin, command);

    string delimeter = " ";
    fileName = command.substr(command.find_first_of(delimeter) + 1);
    command = command.substr(0,command.find_first_of(delimeter));
    return command;
}
