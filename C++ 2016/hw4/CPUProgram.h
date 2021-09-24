//
// Created by Rumeysa on 15.11.2016.
//

#ifndef HW2_CPUPROGRAM_H
#define HW2_CPUPROGRAM_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Maximum number of instructions.
const int MAX_NO_INSTRUCTION = 200;

class CPUProgram {
public:
    CPUProgram();
    CPUProgram(int option);
    CPUProgram(string filepath);

    void ReadFile(string filepath);
    int size();
    void setInstruction(string instruction);
    string getInstructions(int number);

    string operator[](int programCounter);
    CPUProgram operator()(int low, int high);
	void operator +=(string instruction);
    CPUProgram operator--( ); //Prefix version
    CPUProgram operator--(int); //Postfix version

    friend ostream& operator <<(ostream& outputStream, const CPUProgram& myProgram);
    friend CPUProgram operator +(CPUProgram &myProgram, string instruction);

private:

    vector<string> instructions;
    int
	instructionCount = 0;
    int option;
};



bool operator ==( CPUProgram& myProgram,  CPUProgram& prog2);
bool operator !=( CPUProgram& prog1, CPUProgram& prog2);
bool operator <=( CPUProgram& prog1, CPUProgram& prog2);
bool operator >=( CPUProgram& prog1, CPUProgram& prog2);
bool operator <( CPUProgram& prog1, CPUProgram& prog2);
bool operator >( CPUProgram& prog1, CPUProgram& prog2);
CPUProgram operator +(CPUProgram& myProgram, CPUProgram& prog2);


#endif //HW2_CPUPROGRAM_H
