//
// Created by Rumeysa on 29.10.2016.
//

#ifndef HW2_STRINGHELPER_H
#define HW2_STRINGHELPER_H

#include <string>
#include <climits>

using namespace std;

class StringHelper {

public:

    /// Removes leading and trailing spaces.
    static string trim(string str);

    static char toUpperCase(char c);

    // Converts a string to integer ("32" -> 32)
    static int parseInt(string str, int defaultValue = INT_MAX);

};


#endif //HW2_STRİNGHELPER_H
