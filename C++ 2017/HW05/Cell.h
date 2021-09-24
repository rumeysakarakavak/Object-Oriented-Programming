/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the function headers and inner implementations      */
/*   of Cell Class                                                          */
/*--------------------------------------------------------------------------*/
#ifndef HW3_CELL_H
#define HW3_CELL_H

#include <string>
#include "ConnectFourAbstract.h"
using namespace std;

namespace game{
    class Cell {

    public:
        // CONSTRUCTORS//
        Cell(); //no param
        Cell(string state); // takes the state  of the cell
        // SETTERS - GETTERS //
        inline char getPositionOfCell()const{ return positionOfCell;};
        inline void setPositionOfCell(char position){positionOfCell = position;};
        inline int getRowNumber()const{ return rowNumber;};
        inline void setRowNumber(int row){rowNumber = row;};
        inline char getStatusOfCell()const{ return statusOfCell; };
        inline void setStatusOfCell(char status){statusOfCell = status;};
        inline string getState()const{ return  stateOfObject ;};
        inline void setStateOfObject(string state){stateOfObject = state;}

    private:
        char positionOfCell; // A - B ... column character
        int rowNumber; // 1, 2
        char statusOfCell; // character in cell -> X, O, .,
        string stateOfObject; // user1, user2, computer, empty

    };
}

#endif //HW3_CELL_H
