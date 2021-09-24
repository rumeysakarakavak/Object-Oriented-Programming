/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the headers of the functions of the BASE CLASS      */
/*--------------------------------------------------------------------------*/
#ifndef HW5_CONNECTFOURABSTRACT_H
#define HW5_CONNECTFOURABSTRACT_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>
#include "Cell.h"

using namespace std;

namespace game{
class Cell;
class ConnectFourAbstract {

    public:

        // CONSTRUCTORS - DESTRUCTOR //
        ConnectFourAbstract(); // no parameter construuctor for ConnectFour class
        ConnectFourAbstract(int widthBoard, int heightOfBoard); // gets height and width, allocates the memory according to them
        ConnectFourAbstract(const ConnectFourAbstract& anObject); // copy constructor for ConnectFour class
        ~ConnectFourAbstract(); // Destructor for ConnectFour class

        // SETTERS - GETTERS //
        inline int getHeight()const{return  height;};
        inline void setHeight(int heightOfBoard){height = heightOfBoard;};
        inline int getWidth()const{ return width;};
        inline void setWidth(int widthOfBoard){width = widthOfBoard;};
        inline char getPlayers()const{return players;};
        inline void setPlayers(char player){players = player;};
        inline int getWin(){ return  win;};
        inline void setWin(int winOrNo){win = winOrNo;};
        inline vector<ConnectFourAbstract> getObjectVector()const{ return  objectVector;};
        inline void setObjectVector(vector<ConnectFourAbstract> anObjectVector){objectVector = anObjectVector;};

        // ADDITIONAL FUNCTIONS //
        void playGame(); // Play game from start to finish.
        //overloaded play function is in the private section.
        void play(int object);

    // TODO:  private member check
    protected:

        // PRIVATE MEMBERS
        vector <int> rowVector;  // for holding to all row position of moves
        vector <int> columnVector; // for holding to all column position of moves
        Cell **gameCells; // board of the game
        vector<ConnectFourAbstract> objectVector; // object vector for multigame mode
        int height; // height of board
        int width; // width of board
        char players; // PVC or PVP
        int win; // win = 1 , lose = 0

        // PRIVATE METHODS //
        string parseCommandLine(string& filename)const; // parse the command like LOAD ABC.TXT
        int getPosition(char character)const; // Converts the letter to index for first position.
        int updateBoard(char character, int position);  // Updates board after every move.
        int player1(string& fileName, char players); // Turn of player 1 -> calls makeMove
        int player2(string& fileName, char players); // Turn of player 2 -> calls makeMove
        static void printLetterBoard(int size); // Prints letter border
        void printBoard(int widthOfBoard, int heightOfBoard)const; // Prints all board
        void saveFile(const string &fileName, char players);// opens a file and writes the latest version of the board.
        char** loadFile(const string &fileName);// Reads the file and loads the status of board.
        char lowerCase(int character, int lower = 32); // Converts the character upper to lower
        int checkAllBoard()const;  // Checks the whether the board is full or not
        int computer(char playerCharacter, string& fileName, char players); // Play with computer
        void initializeStatus(char character, Cell** board, int i, int j, char gameMode);
        int getLocation(int position); // Returns the last move's location
        void playerComputer(int move); // Decides behavior of computer
        // Keep on playing after the LOAD command with a person.
        int newBoardGame(char playerCharacter, string &fileName, char players);
        // Keep on playing after the LOAD command with computer.
        int newBoardGameComputer(char playerCharacter, string &fileName, char players);
        char playerTo(); // Ask the game will be played among whom
        int play();// play against computer
        int chooseObject();// get the object number from user
        string getFileName();// get filename from user
        void readBoard(string fileName);// read from file for for board creation
        // if x-> user1, if o and versus to computer -> computer, if o and versus to user -> user2

        // VIRTUAL FUNCTIONS //
        virtual char getMove(string& fileName, char playerCharacter)const; // Gets the letter from user to make move and return that.
        virtual int makeMove(string& fileName, char playerCharacter, char players);
        virtual int checkAll(char character); // Calls the all check functions.
    };
}

#endif //HW5_CONNECTFOURABSTRACT_H
