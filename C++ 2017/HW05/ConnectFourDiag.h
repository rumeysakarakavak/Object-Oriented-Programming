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
#ifndef HW5_CONNECTFOURDIAG_H
#define HW5_CONNECTFOURDIAG_H

#include "ConnectFourAbstract.h"
using namespace std;

namespace game{
    class ConnectFourDiag : public ConnectFourAbstract {

    public:
        ConnectFourDiag();
        // gets height and width, allocates the memory according to them
        ConnectFourDiag(int widthBoard, int heightOfBoard);

    private:
        int diagonalCheck(char character); // Checks the diagonal line like that -> /
        int reverseDiagonalCheck(char character); // Checks the diagonal line like that -> '\'
        // Override the checkAll method in the base class
        virtual int checkAll(char character);
    };
}

#endif //HW5_CONNECTFOURDIAG_H
