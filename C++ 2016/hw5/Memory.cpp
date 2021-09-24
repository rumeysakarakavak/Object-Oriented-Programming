/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 06/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file has memory class member functions implementations            */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "Memory.h"
#include "CPU.h"
#include <iostream>
using namespace std;



int Memory::getMem(int memoryNumber) const {
    return memories[memoryNumber];
}



void Memory::printAll() const {
    for (int i = 0; i < NO_MEMORY; ++i) {

        cout << "[" << i << "] -> " << memories[i] << endl;
    }
    cout << endl;
}

int Memory::setMem(int memoryNumber, int number) {

    memories[memoryNumber] = number;
}

Memory:: Memory() {
    for (int i = 0; i < NO_MEMORY; ++i) {
        memories[i] = 0;
    }

}

Memory:: Memory(int option) {
    for (int i = 0; i < NO_MEMORY; ++i) {
        memories[i] = 0;
    }
}
/*---------------------------------------------------------------------------*/
/*                              End of Memory.cpp                            */
/*---------------------------------------------------------------------------*/