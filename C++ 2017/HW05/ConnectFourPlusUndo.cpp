/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the implementations of the                          */
/* functions of the derived CLASS                                           */
/*--------------------------------------------------------------------------*/
#include "ConnectFourPlusUndo.h"
#include "ConnectFourPlus.h"
#include "ConnectFourAbstract.h"


namespace game {

    // no parameter constructor for ConnectFour class
    ConnectFourPlusUndo::ConnectFourPlusUndo() : ConnectFourPlus() {
    }

    // two parameter constructor for ConnectFour class
    // gets height and width, allocates the memory according to them
    ConnectFourPlusUndo::ConnectFourPlusUndo(int widthBoard, int heightBoard)
                        : ConnectFourPlus(widthBoard, heightBoard) {
    }

    // gets move LOAD/ SAVE / UNDO or A B C..
    // parses the command in it
    // returns a character according the parsed command
    // LOAD -> # / SAVE -> $ / UNDO -> ~ else x
    // Override the getMove method in the base class
    // Change is -> UNDO move
    char ConnectFourPlusUndo::getMove(string &fileName, char playerCharacter)const {
        char character;
        string command;
        cout << "Turn of " << playerCharacter << endl;
        // Get command like SAVE FILE, LOAD FILE or A, B, C..
        command = parseCommandLine(fileName);
        // define a character for the string.
        if(command == "SAVE")
            character = '$';
        else if(command == "LOAD")
            character = '#';
        else if(command == "UNDO" && rowVector.size() != 0)
            character = '~';
        // if are all empty cells in the board, get another move
        while(command == "UNDO" && rowVector.size() == 0){
            cout << "Cant do UNDO!! Try another move" << endl;
            command = parseCommandLine(fileName);
        }
        // if command not SAVE or LOAD, check the whether is legal or illegal.
        if (command != "SAVE" && command != "LOAD" && command != "UNDO"){
            if(command.length() == 1){
                character = command[0];
            }
                // if is illegal, define that is 'x' and get command again.
            else{character = 'x';}
            int widthOfBoard = getWidth();
            while(!((character>='a' && character<='a' + widthOfBoard -1) || (character>='A' && character<='A'+ widthOfBoard -1 )
                    || character == '#' || character == '$' || character == '~')){
                cerr << "Enter A-" << static_cast<char> ('A' + widthOfBoard-1) << std :: endl;
                // parse command SAVE - FILE, LOAD - FILE etc.
                command = parseCommandLine(fileName);
                if(command.length() == 1){
                    character = command[0];
                }
                else{character = 'x';}
                // define a character for the string.
                if(command == "SAVE")
                    character = '$';
                else if(command == "LOAD")
                    character = '#';
                else if(command == "UNDO")
                    character = '~';
            }
        }
        return character;
    }

}