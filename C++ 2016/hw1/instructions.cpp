#include "instructions.h"

using namespace std;

/// Removes leading and trailing spaces.  
string trim(string str) {
	// Remove leading spaces
	size_t n = str.find_first_not_of(' ');
	str = str.substr(n, str.size() - n);

	// Remove trailing spaces
	return str.substr(0, str.find_last_not_of(' ') + 1);
}

// Removes comments and gets expressions.
string getExpression(string line) {

	if (line.find(";")){

		return trim(line.substr(0, line.find(";")));}

	else { 
		return trim(line.substr(0, line.find("NULL")));}

	
}

// Removes arguments and gets instruction name.
string getInstructionName(string line) {
	 string instructionString = trim(line.substr(0, line.find(" ")));

	 // do uppercase all characters in instructions.
	  for (int i = 0; i < 3; ++i)
	 {
	 	if ((int)instructionString[i]<=122 && (int)instructionString[i]>=97)
	 	{
	 		instructionString[i] = (int)instructionString[i]-32;
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

// Does string to integer.
int getConstant(string arg) {

	int constant = 0;

    for (int i = 0; arg[i] != '\0'; ++i)
    {
        constant = constant*10 + arg[i] - '0';
    }

	return constant;
}

// Gets number of register R1, R2..
int getRegisterNumber(string arg) {
	string reg = "R_";
	string reg2 = "r_";


	for (int i = 0; i < NO_REGISTERS; ++i)
	{
		reg[1] = (char) ((int) '0' + (i + 1));
		reg2[1] = (char) ((int) '0' + (i + 1));

		if (reg == arg || reg2 == arg) {
			return i + 1;
		}
	}

	// Is constant
	return -1;
}

// Checks whether is register.
bool isArgRegister(string arg) {

	if (arg[0] == 'R' || arg[0] == 'r'){

		return true;
	}

	else{

		return false;
	}
	
}

// Checks how many arguments have.
int countInstructionArgs(string expression) {
	
	int i = expression.find(" ");
	string args = i != string::npos ? trim(expression.substr(i)) : "";

	int noArgs = 0;	// 2
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

Arg parseInstructionArg(string argStr) {
	Arg arg;
	arg.isRegister = isArgRegister(argStr);

	if (arg.isRegister) {
		arg.value = getRegisterNumber(argStr);
	} else {
		arg.value = getConstant(argStr);
	}

	return arg;
}

// Gets instructions, and arguments in instructions struct.
Instruction parseInstruction(string line) {

	const int ZERO = 0;
	const int ONE = 1;
	const int TWO = 2;
	string expression = getExpression(line);

	Instruction instruction;
	instruction.name = getInstructionName(expression);

	int noArgs = countInstructionArgs(expression);
	
	if (instruction.name == INS_MOV) {
		instruction.noArgs = TWO;
		instruction.args[ZERO] = parseInstructionArg(getFirstInstructionArg(expression));
		instruction.args[ONE] = parseInstructionArg(getSecondInstructionArg(expression));
	} else if (instruction.name == INS_PRN) {
		instruction.noArgs = ONE;
		instruction.args[ZERO] = parseInstructionArg(getFirstInstructionArg(expression));
	} else if (instruction.name == INS_SUB) {
		instruction.noArgs = TWO;
		instruction.args[ZERO] = parseInstructionArg(getFirstInstructionArg(expression));
		instruction.args[ONE] = parseInstructionArg(getSecondInstructionArg(expression));
	}else if (instruction.name == INS_ADD) {
		instruction.noArgs = TWO;
		instruction.args[ZERO] = parseInstructionArg(getFirstInstructionArg(expression));
		instruction.args[ONE] = parseInstructionArg(getSecondInstructionArg(expression));
	} else if (instruction.name == INS_JMP) {
		instruction.noArgs = noArgs;
		instruction.args[ZERO] = parseInstructionArg(getFirstInstructionArg(expression));

		if (instruction.noArgs > ONE) {
			instruction.args[ONE] = parseInstructionArg(getSecondInstructionArg(expression));
		}
	} else if (instruction.name == INS_HLT) {
		instruction.noArgs = ZERO;
	}

	return instruction;
}

// Prints each instructions on file.
void printInstruction(Instruction instruction) {
	cout << instruction.name << (instruction.noArgs > 0 ? " : " : "");
	for (int i = 0; i < instruction.noArgs; ++i)
	{
	  	cout << (instruction.args[i].isRegister ? "R" : "") << instruction.args[i].value;

	  	if (i < instruction.noArgs - 1) {
	  		cout << ", ";
	  	} 


	} 
	cout << endl;
}

// Reads the program from file in program struct.
Program readProgramFromFile(char* filePath) {
	Program program;
	program.instructionCount = 0;

	ifstream inputFile;

	inputFile.open(filePath);
	if (!inputFile.is_open()) {
		cerr << "Input file could not be opened: " << filePath << endl;
	} else {
		// Read line by line
		string line;
		while (!inputFile.eof()) {
			getline(inputFile, line);

			// Read instruction
			program.instructions[program.instructionCount] = parseInstruction(line);
			++program.instructionCount;
		}
	}

	return program;
}

// Copies the value of register x to register y or
// copies the value of register constant to register x.
void executeMov(int registers[], Instruction instruction) {

	int noFirstRegister = instruction.args[0].value;
	int noSecondRegister = 0;
	int constantNumber = 0;

	//if argument 2 is a register, copy the register number.
	//else copy constant number. 
	if (instruction.args[1].isRegister){
		noSecondRegister = instruction.args[1].value;
	}else{
		constantNumber = instruction.args[1].value;
	}
	
	//if argument 2 is a register, copy the register value to another register.
	//else copy constant number to register.
	if (instruction.args[1].isRegister) {
		registers[noSecondRegister-1] = registers[noFirstRegister-1];
	}else {
		registers[noFirstRegister-1] = constantNumber;
	}
} 

// Prints the constant or register value.
void executePrn(int registers[], Instruction instruction) {

	int noFirstRegister = instruction.args[0].value;
	int constantNumber = 0;

	if (!instruction.args[0].isRegister){
		constantNumber = instruction.args[0].value;
	}

	if (instruction.args[0].isRegister) {

		cout << registers[noFirstRegister-1] << endl;
	} 

	else cout << constantNumber << endl;
} 

// Substracts constant to register or register to register.
void executeSub(int registers[], Instruction instruction) {

	int noFirstRegister = instruction.args[0].value;
	int noSecondRegister = 0;
	int constantNumber = 0;

	//if second argument is register, substract register y to register x.
	if (instruction.args[1].isRegister){
		noSecondRegister = instruction.args[1].value;
		registers[noFirstRegister-1] -= registers[noSecondRegister-1];

	//if second argument is constant, substract constant to register x.
	}else{
		constantNumber = instruction.args[1].value;
		registers[noFirstRegister-1] -= constantNumber;
	}

} 

// Adds constant to register or register to register.
void executeAdd(int registers[], Instruction instruction) {

	int noFirstRegister = instruction.args[0].value;
	int noSecondRegister = 0;
	int constantNumber = 0;

	//if second argument is register, add register y to register x.
	if (instruction.args[1].isRegister){
		noSecondRegister = instruction.args[1].value;
		registers[noFirstRegister-1] += registers[noSecondRegister-1];

	//if second argument is constant, add constant to register x.
	}else{
		constantNumber = instruction.args[1].value;
		registers[noFirstRegister-1] += constantNumber;
	}
} 

// Jumps to another instruction.
void executeJmp(int registers[], Instruction instruction, Program program) {

	int noFirstRegister = instruction.args[0].value;

	//jump line of the second argument value if register value is equal to zero.
	if (instruction.args[0].isRegister) {

		if (registers[noFirstRegister-1] == 0) {
			int lineAddress = instruction.args[1].value;
			int i=-1;
			while(lineAddress+i!=0){
				Instruction instruction = program.instructions[lineAddress +i];
				execute(registers, instruction, program);
				++i;
			}
		}
	//jump line of the argument.
	}else {

		int lineAddress = instruction.args[0].value;
		int i=-1;
		while(program.instructions[lineAddress +i].name.compare(INS_HLT)!=1){
			Instruction instruction = program.instructions[lineAddress +i];
			execute(registers, instruction, program);
			++i;
		}	
	}
}

// Execute each instructions.
void execute(int registers[], Instruction instruction, Program program) {

	if (instruction.name == INS_MOV) {
		executeMov(registers, instruction);
		
	} else if (instruction.name == INS_PRN) {
		executePrn(registers, instruction);
		
	} else if (instruction.name == INS_SUB) {
		executeSub(registers, instruction);
		
	} else if (instruction.name == INS_JMP) {
		executeJmp(registers, instruction, program);
	} else if (instruction.name == INS_ADD) {
		executeAdd(registers, instruction);
		
	} else if (instruction.name == INS_HLT) {
		exit(1);
		
	} else {
		cerr << "Unknown instruction: " << instruction.name << endl;
	} 
	
	
}
