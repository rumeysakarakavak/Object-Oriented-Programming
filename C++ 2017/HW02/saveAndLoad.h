/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 3.10.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the file function definitions                       */
/*--------------------------------------------------------------------------*/

#ifndef HW2_SAVEANDLOAD_H
#define HW2_SAVEANDLOAD_H

#include <iostream>
#include <fstream>
#include <string>
#include "board.h"

using namespace std;

// opens a file and writes the latest version of the board.
void saveFile(const string &fileName, char **board, int size, char players);
// Reads the file and loads the status of board.
char** loadFile(const string &fileName, char **newBoard);
// Parses command line.
string parseCommandLine(string& filename);

#endif //HW2_SAVEANDLOAD_H
