/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW03_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 29/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This program that simulate a simple CPU.                               */
/*   Gets instructions from file and runs the instructions                  */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "CPU.h"
#include "CPUProgram.h"
#include "StringHelper.h"

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
    int option = StringHelper::parseInt(argv[2]);
    if (option != 0 && option != 1 ) {
        cerr << "Invalid option." << endl;
        cout << "Usage : myprog inputfile option[0-1]" << endl;
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

    CPUProgram myProg (argv[1]);
    CPU myCPU;

    while(!myCPU.halted()){
        string instruction = myProg.getLine(myCPU.getPC());
        myCPU.execute(instruction);

        if(option == 1)
        {
            cout << instruction << endl;
            myCPU.print();

        }

    }


    return 0;
}
/*---------------------------------------------------------------------------*/
/*                              End of main.cpp                              */
/*---------------------------------------------------------------------------*/