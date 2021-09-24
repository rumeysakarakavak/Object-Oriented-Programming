/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 15/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */  
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the instructions implementation                     */
/*--------------------------------------------------------------------------*/
#include "instructions.h"

#include <climits>

using namespace std;

/// Removes leading and trailing spaces.  
string trim(string str) {
	// Remove leading spaces
	size_t n = str.find_first_not_of(' ');
    if (n == string::npos) {
        return str;
    }
    // Remove trailing spaces
    str = str.substr(n, str.size() - n);
    return str.substr(0, str.find_last_not_of(' ') + 1);
}

// Removes comments and gets expressions.
string getExpression(string line) {

	if (line.find(";")){

		return trim(line.substr(0, line.find(";")));}

	else { 
		return trim(line.substr(0, line.find("NULL")));}

	
}

char toUpperCase(char c) {
    return (char) ((int) c - 32);
}

// Removes arguments and gets instruction name.
string getInstructionName(string line) {
	 string instructionString = trim(line.substr(0, line.find(" ")));

	 // do uppercase all characters in instructions.
	  for (int i = 0; i < 3; ++i)
	 {
	 	if ((int)instructionString[i]<=122 && (int)instructionString[i]>=97)
	 	{
	 		instructionString[i] = toUpperCase(instructionString[i]);
	 	}
	 }

	return instructionString;
}

// Gets first argument of expression.
string getFirstInstructionArg(string expression) {
	size_t n = expression.find(" ");
	string args = expression.substr(n + 1, expression.size() - n);
	return trim(args.substr(0, args.find(",")));
}

// Gets second argument of expression.
string getSecondInstructionArg(string expression) {
	size_t n = expression.find(",");
	return trim(expression.substr(n + 1, expression.size() - n));
}
// Converts a string to integer ("32" -> 32)
int parseInt(string str, int defaultValue) {
    string trimmed = trim(str);

    int n = 0;
    for (int i = 0; i < trimmed.size(); ++i) {
        char c = trimmed[i];
        //if no exist digit return default.
        if (isdigit(c) == 0) {
            n = defaultValue;
            break;
        }
        // convert to integer.
        n *= 10;
        n += (int) (c - '0');
    }

    return n;
}

// Gets constant value.
int getConstant(string arg) {
	return parseInt(arg, INT_MAX);
}

// Checks whether is register.
bool isArgRegister(string arg) {
    return arg.size() > 0 && (arg[0] == 'R' || arg[0] == 'r');
}

// Gets number of register R1 -> 1..
int getRegisterNumber(string arg) {
    if (!isArgRegister(arg)) {
        return INT_MAX;
    }
    return parseInt(arg.substr(1), INT_MAX);
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
    return parseInt(arg.substr(1), INT_MAX);
}

// Checks how many arguments have in instruction.
int countInstructionArgs(string expression) {
	
	auto i = expression.find(" ");
	string args = i != string::npos ? trim(expression.substr(i)) : "";

	int noArgs = 0;
	for (size_t n = args.find(","); n != string::npos; n = args.find(","))
	{
		args = trim(args.substr(n + 1, args.size() - n - 1));
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
    // if argument is a memory get memory number.
	} else if(arg.isAddress){
		arg.value = getAddressNumber(argStr);
		// if could not get a number print error message.
        if (arg.value == INT_MAX) {
            cerr << "Can't parse memory address number: #" << arg.value << endl;
            return false;
        }
    // if argument is a constant get the number.    
	} else {
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
bool parseInstruction(string line, Instruction& instruction) {

	const int FIRST_ARG_IND     = 0;
	const int SECOND_ARG_IND    = 1;

	// get expression. like : MOV R3, 10
	string expression = getExpression(line);
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
	}else if (instruction.name == INS_ADD) {
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
	} else if (instruction.name == INS_JPN) {
        instruction.noArgs = 2;
        if (!parseInstructionArg(getFirstInstructionArg(expression),
         instruction.args[FIRST_ARG_IND]) ||
            !parseInstructionArg(getSecondInstructionArg(expression),
             instruction.args[SECOND_ARG_IND])) {
            cerr << "Can't parse " << instruction.name << " instruction." <<
             endl;
            return false;
        }
    } else if (instruction.name == INS_HLT) {
		instruction.noArgs = FIRST_ARG_IND;

	// if instruction name is meaningless print unknown error.
	} else {
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

// Prints each instructions on file.
void printInstruction(Instruction instruction) {

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

// Reads the program from file in program struct.
bool readProgramFromFile(char* filePath, Program& program) {

	program.instructionCount = 0;
	program.currentLineNumber = 0;
	program.halted = false;

	//open a input file.
	ifstream inputFile;
	inputFile.open(filePath);
	// if file can't open print error message.
	if (!inputFile.is_open()) {
		cerr << "Input file could not be opened: " << filePath << endl;
        return false;
	} else {
		// Read line by line
		string line;
		while (!inputFile.eof()) {
			getline(inputFile, line);
            if (trim(line).size() == 0) {
                continue;
            }

			// Read instruction
            if (!parseInstruction(line, program.instructions
            	[program.instructionCount])) {
                cerr << "Cant parse line " << program.instructionCount + 1 << 
            ": " << line << endl;
                return false;
            }
			++program.instructionCount;
		}
	}

    // Everything is OK
	return true;
}

// Copies the value of register x to register y or
// constant to register x.
// the value of register to memory address.
// the value of memory address to register x.
// or the constant to memory address.
void executeMov(int registers[], unsigned int memory[], 
	 Instruction instruction, Program& program) {

	int noFirstRegister = instruction.args[0].value;
	int noSecondRegister = 0;
	int noRegister = 0;
	int constantNumber = 0;

	// if argument 2 is a register, copy the register number and
	// copy the register value to another register.
	// else if copy the register value to memory address.
	// else copy constant number and copy constant number to register.

	if (instruction.args[1].isRegister){
		noSecondRegister = instruction.args[1].value;
		registers[noSecondRegister-1] = registers[noFirstRegister-1];

	}else if (instruction.args[0].isRegister&&instruction.args[1].isAddress){
		int noAddress = instruction.args[1].value;
		noRegister = instruction.args[0].value;
		memory[noAddress] = registers[noRegister-1];}

	else{
		constantNumber = instruction.args[1].value;
		registers[noFirstRegister-1] = constantNumber;
	}
	
	// if argument 1 is a memory address 
	// copy the register value to another register.
	// else copy constant number to memory address.
	int noAddress = 0;
	if (instruction.args[0].isAddress){
		noAddress = instruction.args[0].value;

		if (instruction.args[1].isRegister){
			noRegister = instruction.args[1].value;
			registers[noRegister-1] = memory[noAddress];
		}else{
			
			constantNumber = instruction.args[1].value;
			memory[noAddress] = constantNumber;
		}

	}

	program.currentLineNumber += 1;
}


// Prints the constant or register value or memory address value.
void executePrn(int registers[], unsigned int memory[],
	 Instruction instruction, Program& program) {

	int noFirstRegister = instruction.args[0].value;
	int constantNumber = 0;

	if (!instruction.args[0].isRegister && !instruction.args[0].isAddress){
		constantNumber = instruction.args[0].value;
		cout << constantNumber << endl;
	}

	else if (instruction.args[0].isRegister) {

		cout << registers[noFirstRegister-1] << endl;
	} 

	else if (instruction.args[0].isAddress){
		int noAddress = instruction.args[0].value;
		cout << memory[noAddress] << endl;
	}

	program.currentLineNumber += 1;
} 

// Substracts constant from register or register from register or 
//memory address from register.
void executeSub(int registers[], unsigned int memory[],
 	 Instruction instruction, Program& program) {

	int noFirstRegister = instruction.args[0].value;

	//if second argument is register, substract register y to register x.
	if (instruction.args[1].isRegister){
		int noSecondRegister = instruction.args[1].value;
		registers[noFirstRegister-1] -= registers[noSecondRegister-1];

	//if second argument is constant, substract constant to register x.
	}else if(instruction.args[1].isAddress){
		int noAddress = instruction.args[1].value;
		registers[noFirstRegister-1] -= memory[noAddress];
	}else{
		int constantNumber = instruction.args[1].value;
		registers[noFirstRegister-1] -= constantNumber;
	}
	
	program.currentLineNumber += 1;
} 

// Adds constant to register or register to register.
// Adds memory address value to register.
// Adds constant to register or register to register.
void executeAdd(int registers[], unsigned int memory[],
	 Instruction instruction, Program& program) {

	int noFirstRegister = instruction.args[0].value;
	int noSecondRegister = 0;
	int constantNumber = 0;

	//if second argument is register, add register y to register x.
	if (instruction.args[1].isRegister) {
		noSecondRegister = instruction.args[1].value;
		registers[noFirstRegister-1] += registers[noSecondRegister-1];
	//if second argument is a memory address, add value to register x.
	} else if (instruction.args[1].isAddress) {
		int noAddress = instruction.args[1].value;
		registers[noFirstRegister-1] += memory[noAddress];
	//if second argument is constant, add constant to register x.
	} else { 
		constantNumber = instruction.args[1].value;
		registers[noFirstRegister-1] += constantNumber;
	}

	program.currentLineNumber += 1;
} 

//Jumps to specific line address, if the register value is equal or less than 0
void executeJpn(int registers[], unsigned int memory[],
     Instruction instruction, Program& program) {

	// if register value <= 0 , jump to line
	int iFirstRegister = instruction.args[0].value;
	if (registers[iFirstRegister - 1] <= 0) {
		program.currentLineNumber = instruction.args[1].value - 1;
	// else add 1 to current line number.
	} else {
		program.currentLineNumber += 1;
	}

}
// Jumps to specific line address.
// If instruction has two arguments, checks whether register value is zero
// or not and is equal zero, jumps to line.
void executeJmp(int registers[], unsigned int memory[],
     Instruction instruction, Program& program) 
{    
    // Jump line of the second argument value if register value is equal
    // to zero.
    if (instruction.args[0].isRegister) {

    	// If register value equal to zero jump specified line number declared
    	// in second arg
    	int iFirstRegister = instruction.args[0].value;
    	if (registers[iFirstRegister - 1] == 0) {
    		program.currentLineNumber = instruction.args[1].value - 1;
    	} else {
    		program.currentLineNumber = program.currentLineNumber + 1;
    	}
    } else {
    	// Jump immediately to line number at first arg
    	program.currentLineNumber = instruction.args[0].value - 1;
    }
}

// Prints the memory and finished the program.
void executeHlt (int registers[], unsigned int memory[], 
	 Instruction instruction, Program& program) {
	if (instruction.name == INS_HLT) {
		program.halted = true;
	}

    for (int i = 0; i < NO_MEMORY; ++i) {

        cout << "#" << i << "[" << memory[i] << "]  ";
    }
    cout << endl << endl;
}

// Execute each instructions.
void execute(int registers[], unsigned int memory[], Program& program) {

	Instruction instruction = program.instructions[program.currentLineNumber];
	if (instruction.name == INS_MOV) {
		executeMov(registers, memory, instruction, program);

	} else if (instruction.name == INS_PRN) {
		executePrn(registers, memory, instruction, program);
		

	} else if (instruction.name == INS_SUB) {
		executeSub(registers, memory, instruction, program);
		

	} else if (instruction.name == INS_JPN) {
		executeJpn(registers, memory, instruction, program);
		

	} else if (instruction.name == INS_JMP) {
		executeJmp(registers, memory, instruction, program);
		

	} else if (instruction.name == INS_ADD) {
		executeAdd(registers, memory, instruction, program);
		

	} else if (instruction.name == INS_HLT) {
		executeHlt(registers, memory, instruction, program);
		

	} else {
		cerr << "Unknown instruction: " << instruction.name << endl;
	}
	
	
}
/*---------------------------------------------------------------------------*/ 
/*								End of instructions.cpp						 */
/*---------------------------------------------------------------------------*/