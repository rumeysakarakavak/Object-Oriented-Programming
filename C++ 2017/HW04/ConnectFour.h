/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW04_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 1.11.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the board definitions                               */
/*--------------------------------------------------------------------------*/
#ifndef HW4_CONNECTFOUR_H
#define HW4_CONNECTFOUR_H

#include <iostream>
#include <vector>
#include <fstream>
#include <ostream>

using namespace std;

class ConnectFour {
    class Cell;

public:

    // CONSTRUCTORS - DESTRUCTOR //
    ConnectFour(); // no parameter construuctor for ConnectFour class
    ConnectFour(int widthBoard, int heightOfBoard); // gets height and width, allocates the memory according to them
    explicit ConnectFour(string filename); // allocates the memory according to file
    ConnectFour(const ConnectFour& anObject); // copy constructor for ConnectFour class
    ~ConnectFour(); // Destructor for ConnectFour class
    // SETTERS - GETTERS //
    inline int getHeight()const{return  height;};
    inline void setHeight(int heightOfBoard){height = heightOfBoard;};
    inline int getWidth()const{ return width;};
    inline void setWidth(int widthOfBoard){width = widthOfBoard;};
    inline char getPlayers()const{return players;};
    inline void setPlayers(char player){players = player;};
    inline int getWin(){ return  win;};
    inline void setWin(int winOrNo){win = winOrNo;};
    inline vector<ConnectFour> getObjectVector()const{ return  objectVector;};
    inline void setObjectVector(vector<ConnectFour> anObjectVector){objectVector = anObjectVector;};
    // ADDITIONAL FUNCTIONS //
    char SingleOrMultipleGame()const; // Asks the game mode
    void playGame(); // Play game from start to finish.
    void multiGameInitializer(); // create 5 object and pushback this objects in a vector
    //overloaded play function is in the private section.
    void play(int object);
    // OVERLOADS //
    // overloaded assignment operator for ConnectFour class
    ConnectFour operator=(const ConnectFour& anObject);
    // compares 2 ConnectFour object(width, height, gamecells)
    bool operator ==(const ConnectFour& anobject)const;
    // compares 2 ConnectFour object(width, height, gamecells)
    bool operator !=(const ConnectFour& anobject)const;

private:

    class Cell{
    public:
        // CONSTRUCTORS//
        Cell();
        Cell(string state);
        // SETTERS - GETTERS //
        inline char getPositionOfCell()const{ return positionOfCell;};
        inline void setPositionOfCell(char position){positionOfCell = position;};
        inline int getRowNumber()const{ return rowNumber;};
        inline void setRowNumber(int row){rowNumber = row;};
        inline char getStatusOfCell()const{ return statusOfCell; };
        inline void setStatusOfCell(char status){statusOfCell = status;};
        inline string getState()const{ return  stateOfObject ;};
        inline void setStateOfObject(string state){stateOfObject = state;}
        // OVERLOADS //
        friend const Cell operator ++(Cell& anObject);
        friend const Cell operator ++(Cell& anObject,int ignore);
        friend bool operator ==(const Cell& anobject, const Cell& anotherObject );
        friend ostream& operator <<(ostream& outstream, const Cell& object);
        friend istream& operator >>(istream& instream, Cell& object);

    private:
        char positionOfCell; // A - B ... column character
        int rowNumber; // 1, 2
        char statusOfCell; // character in cell -> X, O, .,
        string stateOfObject; // user1, user2, computer, empty
    };

    // PRIVATE MEMBERS //
    Cell **gameCells; // board of the game
    vector<ConnectFour> objectVector; // object vector for multigame mode
    int height; // height of board
    int width; // width of board
    char players; // PVC or PVP
    int win; // win = 1 , lose = 0
    static int livingCells ; // living cells
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
    char getMove(string& fileName)const; // Gets the letter from user to make move and return that.
    int makeMove(string& fileName, char playerCharacter, char players);
    int verticalCheck(char character); // Checks the top and down.
    int horizontalCheck(char character); // Checks left and right
    int diagonalCheck(char character); // Checks the diagonal line like that -> /
    int reverseDiagonalCheck(char character); // Checks the diagonal line like that -> '\'
    int checkAll(char character); // Calls the all check functions.
    char lowerCase(int character, int lower = 32); // Converts the character upper to lower
    int checkAllBoard()const;  // Checks the whether the board is full or not
    int computer(char playerCharacter, string& fileName, char players); // Play with computer
    int getLocation(int position); // Returns the last move's location
    void playerComputer(int move); // Decides behavior of computer
    // Keep on playing after the LOAD command with a person.
    int newBoardGame(char playerCharacter, string &fileName, char players);
    // Keep on playing after the LOAD command with computer.
    int newBoardGameComputer(char playerCharacter, string &fileName, char players);
    char playerTo(); // Ask the game will be played among whom
    int play();// play against computer
    int widthFromUser();//get width by user for game board
    int heightFromUser();//get height by user for game board
    static int getLivingCells(){ return  livingCells;};
    inline static void setLivingCells(){ ++ livingCells;};
    int chooseObject();// get the object number from user
    string getFileName();// get filename from user
    void readBoard(string fileName);// read from file for for board creation
    // if x-> user1, if o and versus to computer -> computer, if o and versus to user -> user2
    void initializeStatus(char character, Cell** board, int i, int j, char gameMode);
    // OVERLOADS //
    friend const Cell operator ++(Cell& anObject);// overloaded pre-increment operator for Cell class
    friend const Cell operator ++(Cell& anObject, int ignore);// overloaded post-increment operator for Cell class
    friend ostream& operator <<(ostream& outstream, const ConnectFour :: Cell& object);// prints private members of Cell class
    friend istream& operator >>(istream& instream, ConnectFour :: Cell& object);// takes private members of Cell class
    // compares 2 Cell object(character, state, row, column)
    friend bool operator ==(const ConnectFour :: Cell& anobject, const ConnectFour :: Cell& anotherObject );
};


#endif //HW4_CONNECTFOUR_H
