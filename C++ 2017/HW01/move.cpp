/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 21.9.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the move functions implementations                  */
/*--------------------------------------------------------------------------*/
#include <iostream>
#include "move.h"
#include "board.h"
#include "check.h"

// Gets the letter from user to make move and return that.
char getMove(int size) {
    char character;
    std :: cin >> character;
    while(!((character>='a' && character<='a' + size -1) || (character>='A' && character<='A'+ size -1))){
        std :: cout << "Enter A-" << static_cast<char> ('A' + size-1) << std :: endl;
        std :: cin >> character;
    }
    return character;
}
// Converts the letter to index for first position.
int getPosition(char character, int size) {
    int letter = 'A';
    int letters = 'a';
    int position = 0;
    for (int i = 0; i < size; ++i) {
        if(character == static_cast<char>(letter) || character == static_cast<char>(letters)){
            position = i;
        }
        letter++;
        letters++;
    }
    return size * size - (size - position);
}

// Calls getMove for the letter, getPosition for the index and updates the board.
// Checks all possibilities.
int makeMove(int size, char **board, char playerCharacter){

    int win = 0;
        char movement = getMove(size);
        int movePosition = getPosition(movement, size);
        int illegalMove = updateBoard(board,size, playerCharacter, movePosition);
        int check = checkAll(board,size,playerCharacter);
        if( check > 0) {
            std :: cout << "And the winner is " << playerCharacter <<  std :: endl;
            win = 1;
        }

        while(illegalMove != 0){
            movement = getMove(size);
            movePosition = getPosition(movement, size);
            illegalMove = updateBoard(board,size, playerCharacter, movePosition);
            check = checkAll(board,size,playerCharacter);
            if( check > 0) {
                std :: cout << "And the winner is "<< playerCharacter << std :: endl;
                win = 1;
            }

        }
    return win;
}
// Turn of player 1 -> calls makeMove
int player1(int size, char **board) {
    std :: cout << "Turn of player 1";
    std::cout << std::endl;
    return makeMove(size, board, 'X');;
}
// Turn of player 2 -> calls makeMove
int player2(int size, char **board) {
    std :: cout << "Turn of player 2";
    std::cout << std::endl;
    return makeMove(size, board, 'O');;
}
// Who will play the game? -> user2user or user2computer
void playTogether(int size, char **board, char players) {
    int win = 0;
    if(players == 'P' || players == 'p'){
        while(win != 1 && checkAllBoard(board, size) != 1){
            win = player1(size, board);
            if(win != 1){
                win =player2(size, board);
            }
        }
    }
    else{
    	while(win != 1 && checkAllBoard(board, size) != 1){
            win = computer(size, board, 'X');
    	}

    }
}

// Play with computer
int computer(int size, char **board, char playerCharacter) {
    int win = 0;
    //for person
    while(win != 1){
        std :: cout << "Turn of player 1";
	std::cout << std::endl;
        char movement = getMove(size);
        int movePosition = getPosition(movement, size);
        int location = getLocation(board, size, movePosition);
        int illegalMove = updateBoard(board,size, playerCharacter, movePosition);
        int check = checkAll(board,size,playerCharacter);
        if( check > 0) {
            std :: cout << "And the winner is " << 'X' << std :: endl;
            win = 1;
        }

        while(illegalMove != 0){
            std :: cout << "Turn of player 1";
	    std::cout << std::endl;
            movement = getMove(size);
            movePosition = getPosition(movement, size);
            location = getLocation(board, size, movePosition);
            illegalMove = updateBoard(board,size, playerCharacter, movePosition);
            check = checkAll(board,size,playerCharacter);
            if( check > 0) {
                std :: cout << "And the winner is " << 'X'<<  std :: endl;
                win = 1;
            }

        }
        // for computer
        if(win != 1){
            win = 0;
            std :: cout << "Turn of computer";
            std::cout << std::endl;
            playerComputer(board, size, location);
            printLetterBoard(size);
            printBoard(board, size);
            check = checkAll(board,size,'O');
            if( check > 0) {
                std :: cout << "And the winner is "<< 'O'<<  std :: endl;
                win = 1;
            }

        }
    }
    return  win;

}
// Returns the last move's location
int getLocation(char **board, int size, int position){
    int columnPosition = position % size;
    auto rowPosition = static_cast<int> (position / size);
    if (board[rowPosition][columnPosition] == 'X' || board[rowPosition][columnPosition] == 'O') {
        while (rowPosition >= 0 && board[rowPosition][columnPosition] != '.') {
            rowPosition--;
        }
    }
    return rowPosition * size + columnPosition;
}
// Decides behavior of computer
void playerComputer(char **board, int size, int move) {

    int row = move / size;
    int column = move % size;

    // if 3 X is vertical
    if(row + 2 < size && row - 1 >= 0 && board[row + 1][column] == 'X' && board[row + 2][column] == 'X'){
            if(board[row - 1][column] == '.'){
                board[row - 1][column] = 'O';
		std :: cout << static_cast<char>(column + 'A') << std :: endl;
        }

    }// if 3 X is horizontal
    else if(column + 3 < size && board[row][column + 1] == 'X' && board[row][column + 2] == 'X' && board[row][column + 3] == '.' ){
            board[row][column + 3] = 'O';
	    std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;

    }
    else if(column - 3 >= 0 && board[row][column - 1] == 'X' && board[row][column - 2] == 'X' && board[row][column - 3] == '.'){
            board[row][column - 3] = 'O';
            std :: cout << static_cast<char>(column + 'A' - 3) << std :: endl;
    }
    else if(column + 3 < size && row + 3 < size && board[row + 1][column + 1] == 'X' && board[row + 2][column + 2] == 'X' && board[row + 3][column + 3] == '.'){
            board[row + 3][column + 3] = 'O';
	    std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;
    }
    else if(column - 2 >= 0 && row + 2 < size && row -2 >= 0 && column + 1 < size &&
            board[row + 1][column - 1] == 'X' && board[row + 2][column - 2] == 'X' && board[row - 1][column + 1] != '.' && board[row - 2][column + 1] != '.'){
            board[row - 1][column + 1] = 'O';
	    std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else if(column -1 >=0  && row + 1 < size && board[row][column - 1] == '.' &&
            board[row + 1][column -1] != '.' && board[row][column] == 'X' && board[row][column+1] == 'X'){
        board[row][column - 1] = 'O';
	std :: cout << static_cast<char>(column + 'A' - 1) << std :: endl;
    }
    else if(column + 1 < size && row == size - 1 && board[row][column + 1] == '.'){
        board[row][column + 1] = 'O';
	std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else if(column + 1 < size && row + 1 < size && board[row][column + 1] == '.' && board[row + 1][column +1] != '.'){
        board[row][column + 1] = 'O';
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else{
        for (int i = size - 1 ; i >= 0; --i) {
            for (int j = size - 1; j >= 0 ; --j) {
                if(board[i][j] == '.'){
                    board[i][j] = 'O';
		    std :: cout << static_cast<char>(j + 'A') << std :: endl;
                    j = -1;
                    i = -1;
                }
            }
        }
    }
}











