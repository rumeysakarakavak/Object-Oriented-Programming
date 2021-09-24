/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 15/11/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file has cpu program class member functions implementations       */
/*                                                                          */
/*--------------------------------------------------------------------------*/

#include "CPUProgram.h"
#include "StringHelper.h"
#include "CPU.h"
#include <fstream>
#include <stdlib.h>
#include <vector>



// Removes comments and gets expressions.
string getExpression(string line) {
    return StringHelper::trim(line.substr(0, line.find(";")));
}

CPUProgram::CPUProgram() { }

CPUProgram::CPUProgram(string filepath) {
    ReadFile(filepath);
}

void CPUProgram::ReadFile(string filepath) {
//open a input file.
    ifstream inputFile;
    inputFile.open(filepath);
    // if file can't open print error message.
    if (!inputFile.is_open()) {
        cerr << "Input file could not be opened: " << filepath << endl;
        exit (-1);
    } else {
        // Read line by line
        string line;
        while (!inputFile.eof()) {
            getline(inputFile, line);
            if (StringHelper::trim(line).size() == 0) {
                continue;
            }
            instructions.push_back(getExpression(line)) ;
            ++instructionCount;
        }
    }
}


int CPUProgram::size() {
    return instructionCount;
}

CPUProgram::CPUProgram(int option) {

}


//getter for instruction vector
string CPUProgram::getInstructions(int number) {

    return instructions[number];
}


//setter for instruction vector.
void CPUProgram::setInstruction(string instruction) {

    instructions.push_back(instruction);

}

// that takes an integer and works like the getLine function. It returns 
//the program line as a string.
string CPUProgram::operator[](int programCounter) {

    return instructions[programCounter];
}


// that takes a CPUProgram and an instruction line as a string. 
// It returns a new CPUProgram that has the original CPUProgram with appended
// last line from the parameter string.
CPUProgram  operator+(CPUProgram &myCPUProg, string instruction) {

    myCPUProg.instructionCount++;
    myCPUProg.setInstruction(instruction);
    return myCPUProg;
}

//that takes an instruction line as a string and appends the instruction 
//to the end of the program.
void CPUProgram :: operator+=(string instruction) {
     instructions.push_back(instruction);

}

// that prints the program
ostream& operator <<(ostream& outputStream, const CPUProgram& myProgram)
{
    for (int i = 0; i < myProgram.instructionCount ; ++i) {
        outputStream << i <<' ';
        outputStream << myProgram.instructions[i] ;
        outputStream << endl;
    }


    return outputStream;
}

//that takes two programs and returns a new program that appends the second
//programs to the first one
CPUProgram operator+(CPUProgram &prog1, CPUProgram &prog2) {

    int count = (prog1.size() + prog2.size());

    for (int i = prog1.size() ; i < prog2.size() ; ++i) {

        prog1.setInstruction(prog2.getInstructions(i)) ;
    }


    return CPUProgram( );
}

//checks the whether equal or not two CPUProgram objects.
bool operator ==( CPUProgram& prog1, CPUProgram& prog2)
{
    if(prog1.size() == prog2.size()){
         for (int i = 0; i < prog2.size() ; ++i) {

                if(prog1.getInstructions(i) == prog2.getInstructions(i)) ;
                return true;
            }
    }
    else
        return  false;

}
//checks the whether equal or not two CPUProgram objects.
bool operator!=(CPUProgram &prog1, CPUProgram &prog2) {

    if(!(prog1 == prog2))
        return true;
    else
    return false;
}
//checks the whether equal or not two CPUProgram objects.
bool operator<=(CPUProgram &prog1, CPUProgram &prog2) {

    if(prog1.size() <= prog2.size())
    {return true;}
    else return false;
}
//checks the whether equal or not two CPUProgram objects.
bool operator>=(CPUProgram &prog1, CPUProgram &prog2) {

    if(prog1.size() >= prog2.size())
    {return true;}
    else return false;
}
//checks the whether equal or not two CPUProgram objects.
bool operator<(CPUProgram &prog1, CPUProgram &prog2) {
    if(prog1.size() < prog2.size())
    {return true;}
    else return false;
}
//checks the whether equal or not two CPUProgram objects.
bool operator>(CPUProgram &prog1, CPUProgram &prog2) {
    if(prog1.size() > prog2.size())
    {return true;}
    else return false;
}
// takes two integers and returns a new program that contains the
//instructions between the given integers.
CPUProgram CPUProgram :: operator()(int low, int high) {


    for (int i = low; i <= high ; ++i) {

        cout << i <<") " << getInstructions(i) << endl;
    }
    return CPUProgram();
}
//hat delete the last line of the program
CPUProgram CPUProgram::operator--(int) {

    int temp1 = instructionCount;
    instructionCount--;

    return CPUProgram(temp1);
}
//hat delete the last line of the program
CPUProgram CPUProgram::operator--() {

    instructionCount--;

    return CPUProgram(instructionCount);
}





/*---------------------------------------------------------------------------*/
/*                              End of CPUProgram.cpp                        */
/*---------------------------------------------------------------------------*/
