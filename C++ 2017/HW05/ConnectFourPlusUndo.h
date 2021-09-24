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
#ifndef HW5_CONNECTFOURPLUSUNDO_H
#define HW5_CONNECTFOURPLUSUNDO_H

#include "ConnectFourAbstract.h"
#include "ConnectFourPlus.h"


namespace game{

    class ConnectFourPlusUndo : public ConnectFourPlus {

    public:
        ConnectFourPlusUndo();
        // gets height and width, allocates the memory according to them
        ConnectFourPlusUndo(int widthBoard, int heightOfBoard);

    private:
        // Override the getMove method in the base class
        // Change is -> UNDO move
        virtual char getMove(string &fileName, char playerCharacter)const;
    };
}

#endif //HW5_CONNECTFOURPLUSUNDO_H
