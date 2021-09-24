/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 06/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file has computer class member functions implementations          */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "Computer.h"
#include "StringHelper.h"


Computer::Computer() {

}

Computer::Computer(int option) {

}

void Computer::execute(CPU myCPU, CPUProgram myProg, Memory& memo) {

    while(!myCPU.halted()){
        string instruction = myProg.operator[](myCPU.getPC());
        myCPU.execute(instruction, memo );

        if(option == 1)
        {
            cout << instruction << endl;
            myCPU.print();

        }

    }

}


Computer::Computer(CPU myCPU, CPUProgram myCPUProgram, Memory &myMemory, int option) {

    execute(myCPU,myCPUProgram, myMemory);
}

Memory Computer::getMemory() {
    return myMem;
}

CPU Computer::getCPU() {
    return myCpu;
}

CPUProgram Computer::getCPUProgram(){
    return myCPUProg;
}




void Computer::setMemory(Memory myMemory){
    myMem = myMemory;
}


void Computer::setCPU(CPU myCPU) {
    myCpu = myCPU;
}


void Computer :: setCPUProgram(CPUProgram myCPUProgram){
    myCPUProg = myCPUProgram;
}

void Computer::execute() {

}

/*---------------------------------------------------------------------------*/
/*                              End of Computer.cpp                          */
/*---------------------------------------------------------------------------*/

