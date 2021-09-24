/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 15/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */  
/* Description                                                              */
/* -----------                                                              */
/*   This file contains header.							                    */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
// Maximum number of instructions.
const int MAX_NO_INSTRUCTION = 200;
// Number of register.
const int NO_REGISTERS = 50;
// Number of memory.
const int NO_MEMORY = 50;
// Maximum number of argument.
const int MAX_NO_ARGS = 2;

// Instructions
const string INS_MOV = "MOV";
const string INS_PRN = "PRN";
const string INS_SUB = "SUB";
const string INS_JMP = "JMP";
const string INS_HLT = "HLT";
const string INS_ADD = "ADD";
const string INS_JPN = "JPN";

struct Arg {
	int value;			// Constant or the Register number
	bool isRegister;	// Whether is register or not
	bool isAddress;		// Whether is memory or not
};

struct Instruction {
	string name;	
	int noArgs;				//number of arguments
	Arg args[MAX_NO_ARGS];	//Arg structs array
};

struct Program {
	Instruction instructions[MAX_NO_INSTRUCTION];// Instructions structs array
	int instructionCount;						 // Total number of instructions
	int currentLineNumber;						 // Which number
	bool halted;								 // Whether is halted or not
};

/// Executes an instruction given.
void execute(int registers[], unsigned int memory[], Program& program);

/// Reads entire assembly program from file.
/// Returns true if read successfull.
bool readProgramFromFile(char* filePath, Program& program);

/// Prints and instruction given.
void printInstruction(Instruction instruction);
/// Parses string and returns integer value.
int parseInt(string str, int defaultValue = 0);

/*---------------------------------------------------------------------------*/ 
/*								End of instructions.h 						 */
/*---------------------------------------------------------------------------*/