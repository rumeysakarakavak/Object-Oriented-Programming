/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 06/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains header for computer.                                */
/*--------------------------------------------------------------------------*/

#include "CPU.h"
#include "CPUProgram.h"
#include "Memory.h"

#ifndef HW2_COMPUTER_H
#define HW2_COMPUTER_H


class Computer {

public:
    Computer();
    Computer(int option);

    Computer(CPU myCPU, CPUProgram myCPUProgram, Memory &myMemory, int option);

    CPUProgram getCPUProgram();
    Memory getMemory();
    CPU getCPU();
    void setCPU(CPU myCPU);
    void setCPUProgram(CPUProgram myCPUProgram);
    void setMemory(Memory myMemory);
    void execute();

private:
    void execute(CPU myCPU, CPUProgram myProg, Memory &memo);
    int option;
    Memory myMem;
    CPU myCpu;
    CPUProgram myCPUProg;
};


#endif //HW2_COMPUTER_H

/*---------------------------------------------------------------------------*/
/*                              End of Computer.h                            */
/*---------------------------------------------------------------------------*/
