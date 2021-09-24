/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 22.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the check functions implementations                 */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "check.h"
// Checks the top and down.
int verticalCheck(char **board, int size, char character) {
    int characterCount = 0;
    int returnValue = 0;

    for (int i = 0 ; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(board[j][i] == character){
                characterCount ++;
                if (characterCount == 4){
                    returnValue = 1;
                    for (int k = 0; k < characterCount; ++k) {
                        board[j - k][i] = static_cast<char>(int(character) + 32);
                    }
                    i = size;
                    j = size;
                }
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return returnValue;
}
// Checks left and right
int horizontalCheck(char **board, int size, char character) {
    int characterCount = 0;
    int returnValue = 0;

    for (int i = 0 ; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
                if(board[i][j] == character){
                    characterCount ++;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int k = 0; k < characterCount; ++k) {
                            board[i][j - k] = static_cast<char>(int(character) + 32);
                        }
                        i = size;
                        j = size;
                    }
                }
                else{
                    characterCount = 0;
                }
        }
        characterCount = 0;
    }
    return returnValue;
}

// Checks the diagonal line like that -> /
int diagonalCheck(char **board, int size, char character) {
    int characterCount = 0;
    int returnValue = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size ; ++j) {
            int l = j;
            int m = i;
            int k = 0;
            while (k < 4 and l < size and m < size){
                if (board[l][m] == character) {
                    ++characterCount;
                    ++l;
                    ++m;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int n = 0; n < characterCount; ++n) {
                            board[j + n][i + n] = static_cast<char>(int(character) + 32);
                        }

                        k = 3;
                    }
                }
                ++k;
            }
            if (characterCount == 4){
                returnValue = 1;
                i = size;
                j = size;
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return  returnValue;
}
// Checks the diagonal line like that -> '\'
int reverseDiagonalCheck(char **board, int size, char character) {
    int characterCount = 1;
    int returnValue = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size ; ++j) {
                int l = j;
                int m = i;
                int k = 0;
                while (k < 4 and l < size and m >= 0){
                    if (board[l][m] == character) {
                        ++characterCount;
                        ++l;
                        --m;
                        if (characterCount == 4){
                            returnValue = 1;
                            for (int n = 0; n < characterCount; ++n) {
                                board[j + n][i - n] = static_cast<char>(int(character) + 32);
                            }

                            k =  3;
                        }
                    }
                    ++k;
                }
                if (characterCount == 4){
                    returnValue = 1;
                    i = size;
                    j = size;
                }
                else{
                    characterCount = 0;
                }
            }
        characterCount = 0;
        }
    return  returnValue;
}
// Calls the all check functions.
int checkAll(char **board, int size, char character) {

    int returnValue = 0;
    returnValue += horizontalCheck(board, size, character);
    returnValue += verticalCheck(board, size, character);
    returnValue += diagonalCheck(board, size, character);
    returnValue += reverseDiagonalCheck(board, size, character);

    return returnValue;
}

