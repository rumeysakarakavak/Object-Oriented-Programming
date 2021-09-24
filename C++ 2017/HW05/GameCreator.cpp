/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the implementations of the helper functions         */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include "GameCreator.h"
using namespace std;

namespace game{

    //get width by user for game board
    int widthFromUser(){

        std :: cout << "Enter the board width" << std :: endl;
        int widthOfBoard = 0;
        string temp;
        getline(cin, temp);
        widthOfBoard = stoi(temp);
        return widthOfBoard;
    }

//get height by user for game board
    int heightFromUser(){
        std :: cout << "Enter the board height" << std :: endl;
        int heightOfBoard = 0;
        string temp;
        getline(cin, temp);
        heightOfBoard = stoi(temp);
        return heightOfBoard;
    }

    // Asks the game mode
// For single game -> S, multigame -> Mode
    char SingleOrMultipleGame(){
        // get from user
        cout << "Please enter the game mode\nPlus: P or Diagonal: D or Undo: U" << endl;
        string temp;
        getline(cin, temp);
        // if the character is not S or M exit from game
        if(temp.length() == 0)
            exit(1);
        while(temp.length() != 0){
            char mode = temp[0];
            while(mode != 'P' && mode != 'p' && mode != 'D' && mode != 'd'&& mode != 'U' && mode != 'u'){
                // take another character
                std :: cerr << "Please enter P or D or U" << std :: endl;
                getline(cin, temp);
                mode = temp[0];
                // if the character is not S or M exit from game
                if(temp.length() == 0){
                    exit(1);
                }
            }
            return mode;
        }
    }
}


