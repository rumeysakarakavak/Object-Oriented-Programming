/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the headers of the functions of the derived class   */
/*--------------------------------------------------------------------------*/
#ifndef HW5_CONNECTFOURPLUS_H
#define HW5_CONNECTFOURPLUS_H

#include <iostream>
#include "ConnectFourAbstract.h"
using namespace std;

namespace game{
    class ConnectFourPlus : public ConnectFourAbstract {

    public:
        ConnectFourPlus();
        // gets height and width, allocates the memory according to them
        ConnectFourPlus(int widthBoard, int heightOfBoard);

    protected:
        int verticalCheck(char character); // Checks the top and down.
        int horizontalCheck(char character); // Checks left and right.
        // Override the checkAll method in the base class
        virtual int checkAll(char character);
    };
}



#endif //HW5_CONNECTFOURPLUS_H
