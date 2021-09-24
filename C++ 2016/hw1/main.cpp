#include "instructions.h"

using namespace std;

int main(int argc, char *argv[]) 
{
	// TODO: Check arguments


	int registers[NO_REGISTERS] = {0};
	Program program = readProgramFromFile(argv[1]);

	int option = 0;

        option = *argv[2] - '0';
    
    //if option is 0, program will run and finish.
	if (option == 0)
	{
			for (int i = 0; i < program.instructionCount; ++i)
			{
				execute(registers, program.instructions[i], program);
			}

	}
	//if option is 1, program will execute after displaying the instruction.
	else if (option == 1)
	{

		for (int i = 0; i < program.instructionCount; ++i)
		{
			cout << i + 1 << ". ";
			printInstruction(program.instructions[i]);
			execute(registers, program.instructions[i], program);
			
				for (int i = 0; i < NO_REGISTERS; ++i)
				{
				cout << "R" << i+1 <<" = " << registers[i] << ",";
				}

			cout << endl;
		}
	}

	//if option is not 0 or 1 , warn.
	else
	{
		cout << "ERROR! check arguments!" << endl ;
		// TODO: usage
	}

	return 0;
}