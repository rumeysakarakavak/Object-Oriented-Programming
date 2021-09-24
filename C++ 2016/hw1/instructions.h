#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_NO_INSTRUCTION = 200;
const int NO_REGISTERS = 5;
const int MAX_NO_ARGS = 2;

// Instructions
const string INS_MOV = "MOV";
const string INS_PRN = "PRN";
const string INS_SUB = "SUB";
const string INS_JMP = "JMP";
const string INS_HLT = "HLT";
const string INS_ADD = "ADD";

struct Arg {
	int value;			// Constant or the Register number
	bool isRegister;	// Whether is register or not
};

struct Instruction {
	string name;
	int noArgs;
	Arg args[MAX_NO_ARGS];
};

struct Program {
	Instruction instructions[MAX_NO_INSTRUCTION];
	int instructionCount;
};

/// Executes an instruction given.
void execute(int registers[], Instruction instruction, Program program);

/// Reads entire assembly program from file.
Program readProgramFromFile(char* filePath);

/// Prints and instruction given.
void printInstruction(Instruction instruction);
