/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW02_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 19.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the board functions implementations                 */
/*--------------------------------------------------------------------------*/

#include <iostream>
#include "board.h"

// Get the size of board from user.
int boardSize() {

    std :: cout << "Enter the board n size \nIt must be from 4 to 20 and even" << std :: endl;
    int nSize;
    std :: cin >> nSize;
    while ((!(nSize >= 4 && nSize <= 20) || nSize % 2 == 1)){
        std :: cerr << "Please enter from 4 to 20 and even" << std :: endl;
        std :: cin.clear();
        std :: cin.ignore(512, '\n');
        std :: cin >> nSize;

    }
    return  nSize;
}
// First look at the game board. Contains auto statement.
char** initializeBoard(int size) {
    // game board maker
    auto **gameBoard = (char **) malloc((size) * sizeof(char*));
    for (int i=0; i<size ; i++)
        gameBoard[i] = (char *)malloc((size) * sizeof(char*));

    // game board initializer
    printLetterBoard(size);
    for (int i = 0; i < size ; ++i) {
        for (int j = 0; j < size; ++j) {
            gameBoard[i][j] = '.';
            std::cout << gameBoard[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    return gameBoard;
}
// Ask the game will be played among whom
char playerTo() {
    std :: cout << "For PvP :P\nFor PvC :C"<< std :: endl;
    char players;
    std :: cin >> players;
    std :: cin.clear();
    std :: cin.ignore();
    while(players != 'P' && players != 'p' && players != 'C' && players != 'c'){
        std :: cerr << "Please enter P or C" << std :: endl;
        std :: cin >> players;
        std :: cin.clear();
        std :: cin.ignore();
    }
    return players;
}
// Updates board after every move. Contains auto statement.
int updateBoard(char **board, int size, char character, int position) {

    int columnPosition = position % size;
    auto rowPosition = static_cast<int> (position / size);
    int illegalMove = 0;

    if (board[rowPosition][columnPosition] == 'X' || board[rowPosition][columnPosition] == 'O') {
        while (rowPosition >= 0 && board[rowPosition][columnPosition] != '.') {
            rowPosition--;
            if (rowPosition < 0) {
                std::cerr << "Illegal move\nTry another one!" << std::endl;
                illegalMove = 1;
            }
        }
        if (illegalMove != 1) { board[rowPosition][columnPosition] = character; };
    }
    else if (board[rowPosition][columnPosition] == '.') {
        board[rowPosition][columnPosition] = character;
    }

    if (illegalMove != 1) {
        printLetterBoard(size);
        printBoard(board,size);
    }
    return illegalMove;
}
// Prints letter border
void printLetterBoard(int size){

    char letterBoard[size];
    int firstLetter = 'A';
    for (int i = 0; i < size ; ++i) {
        letterBoard[i] = static_cast<char>(firstLetter);
        firstLetter ++;
        std :: cout << letterBoard[i]<< "  ";
    }
    std :: cout << std :: endl;
}
// Prints all board
void printBoard(char **board, int size) {

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << board[i][j] << "  ";
        }
        std::cout << std::endl;
    }
}
// Checks the whether the board is full or not
int checkAllBoard(char **board, int size) {

    int full = 0;
    int count = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if(board[i][j] != '.'){
                ++count;
            }
        }
    }
    if(count == size * size){
        full = 1;
        std :: cout << "Scoreless" << std :: endl;
    }
    return full;
}
// Keep on playing after the LOAD command with a person.
int newBoardGame(char **newBoard, int size, char playerCharacter, string &fileName, char players) {

    int win = 0;
    int xCount = 0;
    int oCount = 0;
    // initiliaze board again. (for remove size and character on the board)
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = newBoard[i + 1][j];
            if(newBoard[i][j] == 'X'){
                ++xCount;
            }
            else if(newBoard[i][j] == 'O'){
                ++oCount;
            }
        }
    }
    // check the counts for to know whose turn
    if(xCount > oCount){
        playerCharacter = 'O';
    }
    else{
        playerCharacter = 'X';
    }
    // play
    while (win != 1 && checkAllBoard(newBoard, size) != 1){
        cout << "Turn of " << playerCharacter << endl;
        int movement = getMove(size, fileName);
        // if command is SAVE
        while(movement == '$'){
            cout << "SAVED" << endl;
            // open a file and write on them
            saveFile(fileName, newBoard, size, players);
            cout << "Turn of " << playerCharacter << endl;
            movement = getMove(size, fileName);
        }
        // command is LOAD
        while(movement == '#'){
            cout << "LOADED" << endl;
            // create new board
            char **newBoard = 0;
            // initialize board
            newBoard = loadFile(fileName, newBoard);
            // size of board
            int newSize = newBoard[0][0];
            // character for pvp or pvc
            players = newBoard[0][1];
            if(players == 'P' || players == 'p'){
                win = newBoardGame(newBoard, newSize, playerCharacter, fileName, players);
            }
            else{
                win = newBoardGameComputer(newBoard, newSize, 'X', fileName, players);
            }
        }
        // Keep playing on
        if(checkAllBoard(newBoard, size) != 1){
            int movePosition = getPosition(movement, size);
            int illegalMove = updateBoard(newBoard, size, playerCharacter, movePosition);
            int check = checkAll(newBoard, size, playerCharacter);
            if (check > 0) {
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                printLetterBoard(size);
                printBoard(newBoard, size);
            }
            if(checkAllBoard(newBoard, size) == 1){
                win = 1;
            }
                while (illegalMove != 0 && checkAllBoard(newBoard, size) != 1 ) {
                    movement = getMove(size, fileName);
                    movePosition = getPosition(movement, size);
                    illegalMove = updateBoard(newBoard, size, playerCharacter, movePosition);
                    check = checkAll(newBoard, size, playerCharacter);
                    if (check > 0) {
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        printLetterBoard(size);
                        printBoard(newBoard, size);
                    }
                    if(checkAllBoard(newBoard, size) == 1){
                        win = 1;
                    }
                }
            // chance the player character
            if(illegalMove != 1){
                if(playerCharacter == 'X'){
                    playerCharacter = 'O';
                }
                else if(playerCharacter == 'O'){
                    playerCharacter = 'X';
                }
            }
        }
    }

    return win;
}
// Keep on playing after the LOAD command with computer.
int newBoardGameComputer(char **newBoard, int size, char playerCharacter, string &fileName, char players) {

    int win = 0;
    // initialize board again
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            newBoard[i][j] = newBoard[i + 1][j];
        }
    }

    while (win != 1 && checkAllBoard(newBoard, size) != 1) {
        cout << "Turn of " << playerCharacter << endl;
        int movement = getMove(size, fileName);
        // if command is SAVE
        while (movement == '$') {
            cout << "SAVED" << endl;
            saveFile(fileName, newBoard, size, players);
            cout << "Turn of " << playerCharacter << endl;
            movement = getMove(size, fileName);
        }

        // if command is LOAD
        while (movement == '#') {
            cout << "LOADED" << endl;
            char **newBoard = 0;
            newBoard = loadFile(fileName, newBoard);
            int newSize = newBoard[0][0];
            players = newBoard[0][1];
            if(players == 'P' || players == 'p'){
                win = newBoardGame(newBoard, newSize, playerCharacter, fileName, players);
            }
            else{
                win = newBoardGameComputer(newBoard, newSize, 'X', fileName, players);
            }
            if (win == 1) {
                printLetterBoard(newSize);
                printBoard(newBoard, newSize);
            }
        }
        // keep playing on
        int movePosition = getPosition(movement, size);
        int location = getLocation(newBoard, size, movePosition);
        int illegalMove = updateBoard(newBoard, size, playerCharacter, movePosition);
        int check = checkAll(newBoard, size, playerCharacter);
        if (check > 0) {
            std::cout << "And the winner is " << playerCharacter << std::endl;
            win = 1;
            printLetterBoard(size);
            printBoard(newBoard, size);
        }
        if(checkAllBoard(newBoard, size) == 1){
            win = 1;
        }
            while (illegalMove != 0) {
                movement = getMove(size, fileName);
                movePosition = getPosition(movement, size);
                location = getLocation(newBoard, size, movePosition);
                illegalMove = updateBoard(newBoard, size, playerCharacter, movePosition);
                check = checkAll(newBoard, size, playerCharacter);
                if (check > 0) {
                    std::cout << "And the winner is " << playerCharacter << std::endl;
                    win = 1;
                    printLetterBoard(size);
                    printBoard(newBoard, size);
                }

            }
        // for computer
        if (win != 1 && illegalMove != 1) {
            win = 0;
            std::cout << "Turn of computer";
            std::cout << std::endl;
            playerComputer(newBoard, size, location);
            printLetterBoard(size);
            printBoard(newBoard, size);
            check = checkAll(newBoard, size, 'O');
            if (check > 0) {
                std::cout << "And the winner is " << 'O' << std::endl;
                win = 1;
                printLetterBoard(size);
                printBoard(newBoard, size);
            }
            if(checkAllBoard(newBoard, size) == 1){
                win = 1;
            }
        }
    }

    return win;
}