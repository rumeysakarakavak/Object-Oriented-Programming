/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
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
#include "ConnectFour.h"

using namespace std;

int main() {

    ConnectFour a;
    //a.playGame(); // Play
    char mode = a.SingleOrMultipleGame();
    if(mode == 'S')
        a.playGame();
    else if(mode == 'M'){
        a.multiGameInitializer();
        a.play();
    }
    else {
        while (mode != 'S' && mode != 'M') {
            mode = a.SingleOrMultipleGame();
        }
        if(mode == 'S')
            a.playGame();
        else if(mode == 'M'){
            a.multiGameInitializer();
            a.play();
        }

    }




    return 0;
}