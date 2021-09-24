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
#include "ConnectFour.h"

using namespace std;

int main() {
    // create an object for the game
    ConnectFour a(0,0);
    // get game mode -> single or multi game
    char mode = a.SingleOrMultipleGame();
    // play with 1 object
    if(mode == 'S' || mode == 's')
        a.playGame();
        // play with 5 object
    else if(mode == 'M' || mode == 'm'){
        a.multiGameInitializer();
        a.play(1);
    }

    return 0;
}