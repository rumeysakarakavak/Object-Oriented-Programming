/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 05/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains header for memory.	                                */
/*--------------------------------------------------------------------------*/

#ifndef HW2_MEMORY_H
#define HW2_MEMORY_H

#include <string>
using namespace std;


// Number of memory.
const int NO_MEMORY = 50;

class Memory {

public:

    Memory();
    Memory(int option);
    int setMem(int memoryNumber, int number) ;
    int getMem(int memoryNumber) const;
    void printAll() const;


private:
    int memories[NO_MEMORY];

};


#endif
/*---------------------------------------------------------------------------*/
/*                              End of memory.h 	                         */
/*---------------------------------------------------------------------------*/
