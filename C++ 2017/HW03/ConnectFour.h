//
// Created by Rumeysa on 14.10.2017.
//

#ifndef HW3_CONNECTFOUR_H
#define HW3_CONNECTFOUR_H

#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

class ConnectFour {
    class Cell;

public:

    ConnectFour();
    ConnectFour(int widthBoard);
    ConnectFour(int widthOfBoard, int heightOfBoard, char player);
    inline int getHeight()const{return  height;};
    inline void setHeight(int heightOfBoard){height = heightOfBoard;};
    inline int getWidth()const{ return width;};
    inline void setWidth(int widthOfBoard){width = widthOfBoard;};
    inline char getPlayers()const{return players;};
    inline void setPlayers(char player){players = player;};
    inline int getWin(){ return  win;};
    inline void setWin(int winOrNo){win = winOrNo;};
    inline vector<vector<Cell>> getGameCells()const{ return  gameCells;};
    inline void setGameCells(vector<vector<Cell>> aGameCell ){gameCells = aGameCell;};
    inline vector<ConnectFour> getObjectVector()const{ return  objectVector;};
    inline void setObjectVector(vector<ConnectFour> anObjectVector){objectVector = anObjectVector;};

    char SingleOrMultipleGame()const;
    void playGame();
    void multiGameInitializer();
    //overloaded play function is in the private section.
    void play();



private:

    class Cell{
    public:
        Cell();
        inline char getPositionOfCell()const{ return positionOfCell;};
        inline void setPositionOfCell(char position){positionOfCell = position;};
        inline int getRowNumber()const{ return rowNumber;};
        inline void setRowNumber(int row){rowNumber = row;};
        inline char getStatusOfCell()const{ return statusOfCell; };
        inline void setStatusOfCell(int status){statusOfCell = status;};

    private:
        char positionOfCell;
        int rowNumber;
        char statusOfCell;
    };

    vector< vector <Cell> > gameCells;
    vector<ConnectFour> objectVector;
    int height;
    int width;
    char players;
    int win;
    static int livingCells ;

    string parseCommandLine(string& filename)const;
    int getPosition(char character)const; // Converts the letter to index for first position.
    int updateBoard(char character, int position);  // Updates board after every move.
    int player1(string& fileName, char players); // Turn of player 1 -> calls makeMove
    int player2(string& fileName, char players); // Turn of player 2 -> calls makeMove
    static void printLetterBoard(int size); // Prints letter border
    void printBoard(int widthOfBoard, int heightOfBoard)const; // Prints all board
    // opens a file and writes the latest version of the board.
    void saveFile(const string &fileName, char players);
    // Reads the file and loads the status of board.
    char** loadFile(const string &fileName);
    // Parses command line.
    char getMove(string& fileName)const; // Gets the letter from user to make move and return that.
    int makeMove(string& fileName, char playerCharacter, char players);
    int verticalCheck(char character); // Checks the top and down.
    int horizontalCheck(char character); // Checks left and right
    int diagonalCheck(char character); // Checks the diagonal line like that -> /
    int reverseDiagonalCheck(char character); // Checks the diagonal line like that -> '\'
    int checkAll(char character); // Calls the all check functions.
    // Default argument used in this function.
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
    int widthFromUser();
    int heightFromUser();
    static int getLivingCells(){ return  livingCells;};
    inline static void setLivingCells(){ ++ livingCells;};
    int chooseObject();
    void initializeBoard();
    bool compare(ConnectFour anObject);
    int play(int cellPosition);
};


#endif //HW3_CONNECTFOUR_H
