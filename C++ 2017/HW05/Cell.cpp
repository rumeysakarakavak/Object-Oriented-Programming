/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the constructors implementations of Cell Class      */
/*--------------------------------------------------------------------------*/
#include "Cell.h"
#include "ConnectFourAbstract.h"

namespace game{
    // no parameter constructor for Cell class
    Cell::Cell() {
        positionOfCell = 0;
        rowNumber = 0;
        statusOfCell = '.';
        stateOfObject = " ";
    }
// gets the state constructor for Cell class
    Cell::Cell(string state) {
        positionOfCell = 0;
        rowNumber = 0;
        statusOfCell = '.';
        stateOfObject = state;
    }
}

