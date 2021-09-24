//
// Created by Rumeysa on 29.10.2016.
//

#ifndef HW2_CPU_H
#define HW2_CPU_H

#include <string>

using namespace std;

// Number of register.
const int NO_REGISTERS = 5;

// Maximum number of argument.
const int MAX_NO_ARGS = 2;

struct Arg {
    int value;			// Constant or the Register number
    bool isRegister;	// Whether is register or not
};

struct Instruction {
    string name;
    int noArgs;				//number of arguments
    Arg args[MAX_NO_ARGS];	//Arg structs array
};

class CPU {
public:
    CPU();

    /// Whether is halted or not
    bool halted() const;

    ///prints registers contents
    void print() const;

    int getRegister(int registerNumber) const;
    int getPC() const;
    void execute (string instruction);

private:
    int registers[NO_REGISTERS];
    int pc;
    bool isHalted;

    // Copies the value of register x to register y or
    // constant to register x.
    void executeMov(Instruction instruction);
    void executePrn(Instruction instruction);
    void executeSub(Instruction instruction);

    // Adds constant to register or register to register.
    void executeAdd(Instruction instruction);
    void executeJmp(Instruction instruction);
    void executeHlt(Instruction instruction);
};




#endif //HW2_CPU_H
