/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 22.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the check definitions                               */
/*--------------------------------------------------------------------------*/
#ifndef HW1_CHECK_H
#define HW1_CHECK_H

int verticalCheck(char **board, int size, char character); // Checks the top and down.
int horizontalCheck(char **board, int size, char character); // Checks left and right
int diagonalCheck(char **board, int size, char character); // Checks the diagonal line like that -> /
int reverseDiagonalCheck(char **board, int size, char character); // Checks the diagonal line like that -> '\'
int checkAll(char **board, int size, char character); // Calls the all check functions.
#endif //HW1_CHECK_H
