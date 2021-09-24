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
#include "ConnectFourPlus.h"

namespace game{

    // no parameter constructor for ConnectFour class
    ConnectFourPlus::ConnectFourPlus(): ConnectFourAbstract() {
    }
    // two parameter constructor for ConnectFour class
    // gets height and width, allocates the memory according to them
    ConnectFourPlus::ConnectFourPlus(int widthBoard, int heightBoard)
                    : ConnectFourAbstract(widthBoard, heightBoard) {
    }

    // Checks the top and down.
    int ConnectFourPlus::verticalCheck(char character) {
        int characterCount = 0;
        int returnValue = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        // look all board and if 4 same characters are in a row return 1;
        // x or o player is won.
        for (int i = 0 ; i < widthOfBoard; ++i) {
            for (int j = 0; j < heightBoard; ++j) {
                if(gameCells[j][i].getStatusOfCell() == character){
                    characterCount ++;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int k = 0; k < characterCount; ++k) {
                            // if there is a winner, convert character to lowercase
                            char lowerCaseCharacter = lowerCase(character);
                            gameCells[j - k][i].setStatusOfCell(lowerCaseCharacter);
                        }
                        i = widthOfBoard;
                        j = heightBoard;
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
    int ConnectFourPlus::horizontalCheck(char character) {
        int characterCount = 0;
        int returnValue = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();

        // look all board and if 4 same characters are side by side return 1;
        // x or o player is won.
        for (int i = 0 ; i < heightBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                if(gameCells[i][j].getStatusOfCell() == character){
                    characterCount ++;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int k = 0; k < characterCount; ++k) {
                            // if there is a winner, convert character to lowercase
                            char lowerCaseCharacter = lowerCase(character);
                            gameCells[i][j - k].setStatusOfCell(lowerCaseCharacter);
                        }
                        i = heightBoard;
                        j = widthOfBoard;
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

    // Calls the horizontal and vertical check functions.
    // Override the checkAll method in the base class
    int ConnectFourPlus::checkAll(char character) {
        int returnValue = 0;
        returnValue += horizontalCheck(character);
        returnValue += verticalCheck(character);
        return returnValue;
    }
}