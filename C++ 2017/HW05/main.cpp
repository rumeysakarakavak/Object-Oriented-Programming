/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 1.11.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This homework is the game of Connect Four                              */
/*   The game of Connect Four is played by two players                      */
/*   (computer-user or user1-user2) on a two dimensional board (2D array)   */
/*   with nonregular cells.                                                */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"
#include "GameCreator.h"
#include "Cell.h"

using namespace std;
using namespace game;

int main() {

    // get game mode -> single or multi game
    char mode = SingleOrMultipleGame();
    // get height of board
    int height = heightFromUser();
    // get width of board
    int width = widthFromUser();

    // play with 1 object
    if(mode == 'P' || mode == 'p'){
        // create an object for the game
        ConnectFourPlus gameObjectPlus(width, height);
        gameObjectPlus.playGame();
    }
    else if(mode == 'D' || mode == 'd'){
        // create an object for the game
        ConnectFourDiag gameObjectDiag(width, height);
        gameObjectDiag.playGame();
    }
    else if(mode == 'U' || mode == 'u'){
        // create an object for the game
        ConnectFourPlusUndo gameObjectUndo(width, height);
        gameObjectUndo.playGame();
    }

    return 0;
}

