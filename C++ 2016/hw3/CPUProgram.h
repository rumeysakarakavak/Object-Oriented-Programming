//
// Created by Rumeysa on 29.10.2016.
//

#ifndef HW2_CPUPROGRAM_H
#define HW2_CPUPROGRAM_H

#include <iostream>
#include <string>

using namespace std;

// Maximum number of instructions.
const int MAX_NO_INSTRUCTION = 200;

class CPUProgram {
public:
    CPUProgram();
    CPUProgram(string filepath);

    void readFile(string filepath);
    string getLine(int programCounter);
    int size();

private:
    string instructions[MAX_NO_INSTRUCTION];
    int instructionCount = 0;
};


#endif //HW2_CPUPROGRAM_H
