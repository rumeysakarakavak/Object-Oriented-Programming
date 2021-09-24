/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 29/10/2016 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains header for strings.	                                */
/*--------------------------------------------------------------------------*/
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


#endif

/*---------------------------------------------------------------------------*/
/*                              End of StringHelper.h                        */
/*---------------------------------------------------------------------------*/
