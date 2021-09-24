//
// Created by Rumeysa on 29.10.2016.
//

#include "CPUProgram.h"
#include "StringHelper.h"
#include <fstream>
#include <stdlib.h>



// Removes comments and gets expressions.
string getExpression(string line) {
    return StringHelper::trim(line.substr(0, line.find(";")));
}

CPUProgram::CPUProgram() { }

CPUProgram::CPUProgram(string filepath) {
    readFile(filepath);
}

void CPUProgram::readFile(string filepath) {
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
            instructions[instructionCount] = getExpression(line);
            ++instructionCount;
        }
    }
}

string CPUProgram::getLine(int programCounter) {
    return instructions[programCounter - 1];
}

int CPUProgram::size() {
    return instructionCount;
}
