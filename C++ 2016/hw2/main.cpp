/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 15/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */  
/* Description                                                              */
/* -----------                                                              */
/*   This program that simulate a simple CPU.                               */
/*   Gets instructions from file and runs the instructions                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "instructions.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	// If number of arguments less than three, print error message.
	if (argc < 3) {
		cerr << "Insufficent number of arguments." << endl;
        cout << "Usage : myprog inputfile option" << endl;
        return 0;
	}

    // If number of arguments is invalid, print error message.
    int option = parseInt(argv[2]);
    if (option != 0 && option != 1 && option != 2) {
        cerr << "Invalid option." << endl;
        cout << "Usage : myprog inputfile option[0-2]" << endl;
        return 0;
    }
    // If number of arguments greater than 3, print error message.
    if (argc > 3) {
        cout << "Ignoring extra arguments: \"";
        for (int i = 3; i < argc; ++i) {
            cout << argv[i] << " ";
        }
        cout << "\"" << endl;
    }
    // Initialization register and memory.
	int registers[NO_REGISTERS] = {0};
	unsigned int memory[NO_MEMORY] = {0};
	Program program;
    // If reading is not successful print error message.
    if (!readProgramFromFile(argv[1], program)) {
        cerr << "Program could not be parsed." << endl;
        return 0;
    }

    while (!program.halted && program.currentLineNumber < program.instructionCount) {

        // if option is 0, run and finish the program.
        if(option == 0)
        {
            execute(registers, memory, program);
        }

		if (option == 1 || option == 2 ) {
			cout << program.currentLineNumber + 1 << ". ";
			printInstruction(program.instructions[program.currentLineNumber]);
            execute(registers, memory, program);
		}

        // if option is 1, print registers.
		if (option == 1) {
			for (int i = 0; i < NO_REGISTERS; ++i) {
				cout << "R" << i + 1 << "[" << registers[i] <<"] ";
                if (i < NO_REGISTERS - 1) {
                    cout << " ";
                }
			}

            cout << endl;
            cout << endl;
		}

        // if option is 2, print memory.
        if (option == 2) {
            for (int i = 0; i < NO_MEMORY; ++i) {

                cout << "#" << i << "[" << memory[i] << "]  ";
            }
            cout << endl;
        }
	}

	return 0;
}
/*---------------------------------------------------------------------------*/ 
/*                              End of main.cpp                              */
/*---------------------------------------------------------------------------*/