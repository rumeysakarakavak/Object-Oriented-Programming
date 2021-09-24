/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the implementations of the                          */
/* functions of the derived CLASS                                           */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "ConnectFourDiag.h"

using namespace std;

//decltype for lowercase characters
decltype('a') lowerCaseCharacter;

namespace game{

    // no parameter constructor for ConnectFour class
    ConnectFourDiag::ConnectFourDiag(): ConnectFourAbstract() {
    }

    // two parameter constructor for ConnectFour class
    // gets height and width, allocates the memory according to them
    ConnectFourDiag::ConnectFourDiag(int widthBoard, int heightBoard) : ConnectFourAbstract(widthBoard, heightBoard) {
    }

    // Checks the diagonal line like that -> '\'
    int ConnectFourDiag::diagonalCheck(char character) {
        int characterCount = 0;
        int returnValue = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();

        // look all board and if 4 same characters diagonal return 1;
        // x or o player is won.
        for (int i = 0; i < widthOfBoard; ++i) {
            for (int j = 0; j < heightBoard ; ++j) {
                int l = j;
                int m = i;
                int k = 0;
                while (k < 4 and l < heightBoard and m < widthOfBoard){
                    if (gameCells[l][m].getStatusOfCell() == character) {
                        ++characterCount;
                        ++l;
                        ++m;
                        if (characterCount == 4){
                            returnValue = 1;
                            for (int n = 0; n < characterCount; ++n) {
                                // if there is a winner, convert character to lowercase
                                lowerCaseCharacter = lowerCase(character);
                                gameCells[j + n][i + n].setStatusOfCell(lowerCaseCharacter);
                            }

                            k = 3;
                        }
                    }
                    ++k;
                }
                // if all same break the loop
                if (characterCount == 4){
                    returnValue = 1;
                    i = widthOfBoard;
                    j = heightBoard;
                }
                else{
                    characterCount = 0;
                }
            }
            characterCount = 0;
        }
        return  returnValue;
    }

// Checks the diagonal line like that -> '/'
    int ConnectFourDiag::reverseDiagonalCheck(char character) {
        int characterCount = 1;
        int returnValue = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();

        // look all board and if 4 same characters diagonal return 1;
        // x or o player is won.
        for (int i = 0; i < widthOfBoard; ++i) {
            for (int j = 0; j < heightBoard ; ++j) {
                int l = j;
                int m = i;
                int k = 0;
                while (k < 4 and l < heightBoard and m >= 0){
                    if (gameCells[l][m].getStatusOfCell() == character) {
                        ++characterCount;
                        ++l;
                        --m;
                        if (characterCount == 4){
                            returnValue = 1;
                            for (int n = 0; n < characterCount; ++n) {
                                // if there is a winner, convert character to lowercase
                                lowerCaseCharacter = lowerCase(character);
                                gameCells[j + n][i - n].setStatusOfCell(lowerCaseCharacter);
                            }

                            k =  3;
                        }
                    }
                    ++k;
                }
                // if all same break the loop
                if (characterCount == 4){
                    returnValue = 1;
                    i = widthOfBoard;
                    j = heightBoard;
                }
                else{
                    characterCount = 0;
                }
            }
            characterCount = 0;
        }
        return  returnValue;
    }

    // Calls the diagonal check functions.
    // Override the checkAll method in the base class
    int ConnectFourDiag::checkAll(char character) {
        int returnValue = 0;
        returnValue += diagonalCheck(character);
        returnValue += reverseDiagonalCheck(character);
        return returnValue;
    }

}