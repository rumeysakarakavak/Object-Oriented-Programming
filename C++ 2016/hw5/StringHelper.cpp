/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 29/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file has string helper class member functions implementations     */
/*                                                                          */
/*--------------------------------------------------------------------------*/
#include "StringHelper.h"
#include <iostream>
#include <string>

/// Removes leading and trailing spaces.
string StringHelper::trim(string str) {
    // Remove leading spaces
    size_t n = str.find_first_not_of(' ');
    if (n == string::npos) {
        return str;
    }
    // Remove trailing spaces
    str = str.substr(n, str.size() - n);
    return str.substr(0, str.find_last_not_of(' ') + 1);
}

char StringHelper::toUpperCase(char c) {
    return (char) ((int) c - 32);
}

// Converts a string to integer ("32" -> 32)
int StringHelper::parseInt(string str, int defaultValue) {
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

/*---------------------------------------------------------------------------*/
/*                              End of StringHelper.cpp                      */
/*---------------------------------------------------------------------------*/