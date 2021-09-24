/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 04/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file has cpu class member functions implementations               */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "CPU.h"
#include "StringHelper.h"
#include "Memory.h"
#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <stdlib.h>

// Instructions
const string INS_MOV = "MOV";
const string INS_PRN = "PRN";
const string INS_SUB = "SUB";
const string INS_JMP = "JMP";
const string INS_HLT = "HLT";
const string INS_ADD = "ADD";
const string INS_JPN = "JPN";



// Removes arguments and gets instruction name.
string getInstructionName(string line) {
    string instructionString = StringHelper::trim(line.substr(0, line.find(" ")));

    // do uppercase all characters in instructions.
    for (int i = 0; i < 3; ++i)
    {
        if ((int)instructionString[i]<=122 && (int)instructionString[i]>=97)
        {
            instructionString[i] = StringHelper::toUpperCase(instructionString[i]);
        }
    }

    return instructionString;
}

// Gets first argument of expression.
string getFirstInstructionArg(string expression) {
    size_t n = expression.find(" ");
    string args = expression.substr(n + 1, expression.size() - n);
    return StringHelper::trim(args.substr(0, args.find(",")));
}

// Gets second argument of expression.
string getSecondInstructionArg(string expression) {
    size_t n = expression.find(",");
    return StringHelper::trim(expression.substr(n + 1, expression.size() - n));
}


// Gets constant value.
int getConstant(string arg) {
    return StringHelper::parseInt(arg, INT_MAX);
}

// Checks whether is register.
bool isArgRegister(string arg) {
    return (arg.size() > 0 && (arg[0] == 'R' || arg[0] == 'r'));
}

// Gets number of register R1 -> 1..
int getRegisterNumber(string arg) {
    if (!isArgRegister(arg)) {
        return INT_MAX;
    }
    return StringHelper::parseInt(arg.substr(1), INT_MAX);
}

// Checks whether is memory address.
bool isArgMemory(string arg) {
    return arg.size() > 0 && arg[0] == '#';

}

// Gets number of register #1 -> 1..
int getAddressNumber(string arg){
    if (!isArgMemory(arg)) {
        return INT_MAX;
    }
    return StringHelper::parseInt(arg.substr(1), INT_MAX);
}


// Checks how many arguments have in instruction.
int countInstructionArgs(string expression) {

    auto i = expression.find(" ");
    string args = i != string::npos ? StringHelper::trim(expression.substr(i)) : "";

    int noArgs = 0;
    for (size_t n = args.find(","); n != string::npos; n = args.find(","))
    {
        args = StringHelper::trim(args.substr(n + 1, args.size() - n - 1));
        ++noArgs;
    }

    if (args.size() > 0) {
        ++noArgs;
    }

    return noArgs;
}

// Checks the parse is successful or not.
bool parseInstructionArg(string argStr, Arg& arg) {
    arg.isRegister = isArgRegister(argStr);
    arg.isAddress = isArgMemory(argStr);

    // if argument is a register get register number.
    if (arg.isRegister) {
        arg.value = getRegisterNumber(argStr);
        // if could not get a number print error message.
        if (arg.value == INT_MAX) {
            cerr << "Can't parse register number: R" << arg.value << endl;
            return false;
        }

    }
    // if argument is an address get memory number.
    else if (arg.isAddress) {
        arg.value = getAddressNumber(argStr);
        // if could not get a number print error message.
        if (arg.value == INT_MAX) {
            cerr << "Can't parse memory number: #" << arg.value << endl;
            return false;
        }

    }else {
        arg.value = getConstant(argStr);
        // if could not get a number print error message.
        if (arg.value == INT_MAX) {
            cerr << "Can't parse constant: " << arg.value << endl;
            return false;
        }
    }

    return true;
}

// Gets instructions, and arguments in instructions struct.
bool parseInstruction(string expression, Instruction& instruction) {
    const int FIRST_ARG_IND = 0;
    const int SECOND_ARG_IND = 1;

    // get name of instruction. like : MOV
    instruction.name = getInstructionName(expression);
    // get number of argument. like : MOV R3, 10 has 2 arg
    int argsCount = countInstructionArgs(expression);

    // if count greater than number of instruction argument print error message.
    if (argsCount > MAX_NO_ARGS) {
        cerr << "Instruction arguments count can't be greater than " <<
             MAX_NO_ARGS << endl;
        return false;
    }

    // specify number of arguments of instructions.
    // if parsing is not successful print error message.
    if (instruction.name == INS_MOV) {
        instruction.noArgs = 2;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND]) ||
            !parseInstructionArg(getSecondInstructionArg(expression),
                                 instruction.args[SECOND_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }
    } else if (instruction.name == INS_PRN) {
        instruction.noArgs = 1;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }
    } else if (instruction.name == INS_SUB) {
        instruction.noArgs = 2;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND]) ||
            !parseInstructionArg(getSecondInstructionArg(expression),
                                 instruction.args[SECOND_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }
    } else if (instruction.name == INS_ADD) {
        instruction.noArgs = 2;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND]) ||
            !parseInstructionArg(getSecondInstructionArg(expression),
                                 instruction.args[SECOND_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }
    } else if (instruction.name == INS_JMP) {
        instruction.noArgs = argsCount;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }

        if (instruction.noArgs > 1) {
            if (!parseInstructionArg(getSecondInstructionArg(expression),
                                     instruction.args[SECOND_ARG_IND])) {
                cerr << "Can't parse " << instruction.name << " instruction." <<
                     endl;
                return false;
            }
        }
    }
    else if (instruction.name == INS_JPN) {
        instruction.noArgs = 2;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
                                 instruction.args[FIRST_ARG_IND]) ||
            !parseInstructionArg(getSecondInstructionArg(expression),
                                 instruction.args[SECOND_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
                 endl;
            return false;
        }
    }
    else if (instruction.name == INS_HLT) {
            instruction.noArgs = FIRST_ARG_IND;

            // if instruction name is meaningless print unknown error.
        }
    else {
            cerr << "Unknown instruction: " << instruction.name << endl;
            return false;
        }

        if (argsCount != instruction.noArgs) {
            cerr << "Instruction arguments count can't be greater than " <<
                 instruction.noArgs << endl;
            return false;
        }

        return true;
    }

    bool CPU::halted() const {
        return isHalted;
    }

    void CPU::print() const {
        for (int i = 0; i < NO_REGISTERS; ++i) {
            cout << "R[" << i + 1 << "] = " << registers[i] <<" ";
        }
        cout << endl;
    }

    void CPU::execute(string instructionLine, Memory &mem) {
        Instruction instruction;
        if (!parseInstruction(instructionLine, instruction)) {
            cerr << "Cant parse instruction: " << instructionLine << endl;
            exit(EXIT_FAILURE);
        }

        if (instruction.name == INS_MOV) {
            executeMov(instruction, mem);
        } else if (instruction.name == INS_PRN) {
            executePrn(instruction, mem);
        } else if (instruction.name == INS_SUB) {
            executeSub(instruction, mem);
        } else if (instruction.name == INS_JMP) {
            executeJmp(instruction, mem);
        } else if (instruction.name == INS_JPN) {
            executeJpn(instruction, mem);
        } else if (instruction.name == INS_ADD) {
            executeAdd(instruction, mem);
        } else if (instruction.name == INS_HLT) {
            executeHlt(instruction);
        } else {
            cerr << "Unknown instruction: " << instruction.name << endl;
        }
    }

    void CPU::executeMov(Instruction instruction, Memory &mem) {
        int noFirstRegister = instruction.args[0].value;
        int noSecondRegister = 0;
        int noRegister = 0;
        int constantNumber = 0;

        // if argument 2 is a register, copy the register number and
        // copy the register value to another register.
        // else copy constant number and copy constant number to register.

        if (instruction.args[1].isRegister && instruction.args[0].isRegister) {
            noSecondRegister = instruction.args[1].value;
            registers[noSecondRegister - 1] = registers[noFirstRegister - 1];

        } else if (instruction.args[0].isRegister && instruction.args[1].isAddress){
            int noAddress = instruction.args[1].value;
            noRegister = instruction.args[0].value;
            mem.setMem(noAddress, registers[noRegister-1]);
        } else if (instruction.args[0].isRegister) {
            constantNumber = instruction.args[1].value;
            registers[noFirstRegister - 1] = constantNumber;
        }



        int noAddress = 0;
        if (instruction.args[0].isAddress){
            noAddress = instruction.args[0].value;
            if (instruction.args[1].isRegister){
                noRegister = instruction.args[1].value;
                registers[noRegister-1] = mem.getMem(noAddress);

            }else if (!instruction.args[1].isRegister){

                constantNumber = instruction.args[1].value;
                mem.setMem(noAddress, constantNumber);
            }

        }

            pc += 1;
    }

    void CPU::executePrn(Instruction instruction, Memory &mem) {
        int noFirstRegister = instruction.args[0].value;
        int constantNumber = 0;

        if (!instruction.args[0].isRegister && !instruction.args[0].isAddress) {
            constantNumber = instruction.args[0].value;
            cout << constantNumber << endl;
        } else if (instruction.args[0].isAddress){
            int noAddress = instruction.args[0].value;
            cout <<mem.getMem(noAddress) << endl;
        } else {

            cout << registers[noFirstRegister - 1] << endl;
        }

        pc += 1;
    }

    void CPU::executeSub(Instruction instruction, Memory &mem) {
        int noFirstRegister = instruction.args[0].value;

        //if second argument is register, substract register y to register x.
        if (instruction.args[1].isRegister) {
            int noSecondRegister = instruction.args[1].value;
            registers[noFirstRegister - 1] -= registers[noSecondRegister - 1];

            //if second argument is constant, substract constant to register x.
        }else if(instruction.args[1].isAddress){
            int noAddress = instruction.args[1].value;
            registers[noFirstRegister-1] -= mem.getMem(noAddress);
        } else {
            int constantNumber = instruction.args[1].value;
            registers[noFirstRegister - 1] -= constantNumber;
        }

        pc += 1;


    }

    void CPU::executeAdd(Instruction instruction, Memory &mem) {
        int noFirstRegister = instruction.args[0].value;
        int noSecondRegister = 0;
        int constantNumber = 0;

        //if second argument is register, add register y to register x.
        if (instruction.args[1].isRegister) {
            noSecondRegister = instruction.args[1].value;
            registers[noFirstRegister - 1] += registers[noSecondRegister - 1];
            //if second argument is constant, add constant to register x.
        } else if (instruction.args[1].isAddress) {
            int noAddress = instruction.args[1].value;
            registers[noFirstRegister-1] += mem.getMem(noAddress);
            //if second argument is constant, add constant to register x.
        }else {
            constantNumber = instruction.args[1].value;
            registers[noFirstRegister - 1] += constantNumber;
        }

        pc += 1;
    }

    void CPU::executeJmp(Instruction instruction, Memory &mem) {
// Jump line of the second argument value if register value is equal
        // to zero.
        if (instruction.args[0].isRegister) {

            // If register value equal to zero jump specified line number declared
            // in second arg
            int iFirstRegister = instruction.args[0].value;
            if (registers[iFirstRegister - 1] == 0) {
                pc = instruction.args[1].value;
            } else {
                pc = pc + 1;
            }
        } else {
            // Jump immediately to line number at first arg
            pc = instruction.args[0].value;
        }

    }

void CPU::executeJpn(Instruction instruction, Memory &mem) {

    // if register value <= 0 , jump to line
    int iFirstRegister = instruction.args[0].value;
    if (registers[iFirstRegister - 1] <= 0) {
       pc = instruction.args[1].value;
        // else add 1 to current line number.
    } else {
        pc += 1;
    }
}

    void CPU::executeHlt(Instruction instruction) {
        isHalted = true;
    }

   /* int CPU::getRegister(int registerNumber){
        return registers[registerNumber];
    }*/

    int CPU::getPC() const {
        return pc;
    }

    CPU::CPU() {
        for (int i = 0; i < NO_REGISTERS; ++i) {
            registers[i] = 0;
        }
        pc = 1;
        isHalted = false;
    }

void CPU::printInstruction(Instruction instruction) {
    cout << instruction.name << (instruction.noArgs > 0 ? " : " : "");
    for (int i = 0; i < instruction.noArgs; ++i)
    {
        cout << (instruction.args[i].isRegister ? "R" : "") <<
             instruction.args[i].value;

        if (i < instruction.noArgs - 1) {
            cout << ", ";
        }


    }
    cout << endl;
}

CPU::CPU(int option) {
    for (int i = 0; i < NO_REGISTERS; ++i) {
        registers[i] = 0;
    }
    pc = 1;
    isHalted = false;
}

/*---------------------------------------------------------------------------*/
/*                              End of CPU.cpp                               */
/*---------------------------------------------------------------------------*/
