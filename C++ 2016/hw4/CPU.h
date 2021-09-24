/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 04/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains header for CPU.                                     */
/*--------------------------------------------------------------------------*/
#ifndef HW2_CPU_H
#define HW2_CPU_H

#include <string>
#include "Memory.h"

using namespace std;

// Number of register.
const int NO_REGISTERS = 5;

// Maximum number of argument.
const int MAX_NO_ARGS = 2;

struct Arg {
    int value;			// Constant or the Register number
    bool isRegister;	// Whether is register or not
    bool isAddress;
};

struct Instruction {
    string name;
    int noArgs;				//number of arguments
    Arg args[MAX_NO_ARGS];	//Arg structs array
};

class CPU {
public:
    CPU();
    CPU(int option);
    /// Whether is halted or not
    bool halted() const;

    ///prints registers contents
    void print() const;

    static void printInstruction(Instruction instruction);
    int getPC() const;
    void execute (string instruction, Memory& mem);

private:
    int registers[NO_REGISTERS];
    int pc;
    bool isHalted;
    int option;

    // Copies the value of register x to register y or
    // constant to register x.
    void executeMov(Instruction instruction, Memory &mem);
    void executePrn(Instruction instruction, Memory &mem);
    void executeSub(Instruction instruction, Memory &mem);

    // Adds constant to register or register to register.
    void executeAdd(Instruction instruction, Memory &mem);
    void executeJmp(Instruction instruction, Memory &mem);
    void executeJpn(Instruction instruction, Memory &mem);
    void executeHlt(Instruction instruction);
};


#endif 

/*---------------------------------------------------------------------------*/
/*                              End of CPU.h                                 */
/*---------------------------------------------------------------------------*/
