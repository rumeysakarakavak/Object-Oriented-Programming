/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW05_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 23.11.2017 by Rumeysa_Karakavak                               */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the implementations of the                          */
/* functions of the BASE CLASS                                              */
/*--------------------------------------------------------------------------*/
#include "ConnectFourAbstract.h"
#include "Cell.h"

namespace game{

// print border of gameboard -> A B C..
    void ConnectFourAbstract::printLetterBoard(int size) {
        char letterBoard[size];
        int firstLetter = 'A';
        for (int i = 0; i < size; ++i) {
            letterBoard[i] = static_cast<char>(firstLetter);
            firstLetter ++;
            std :: cout << letterBoard[i]<< " ";
        }
        std :: cout << std :: endl;
    }


// Prints all board character by character
    void ConnectFourAbstract :: printBoard(int widthOfBoard, int heightOfBoard)const {

        for (int i = 0; i < heightOfBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                if(gameCells[i][j].getStatusOfCell() == '#'){
                    cout <<"  ";
                }
                else{
                    cout << gameCells[i][j].getStatusOfCell();
                    cout <<" ";
                }
            }
            std::cout << std::endl;
        }
    }
// if the command is SAVE, saves the current board state a file.
    void ConnectFourAbstract::saveFile(const string &fileName,char players) {

        ofstream outputStream;
        outputStream.open(fileName);
        // file is open?
        if (!outputStream.is_open()) {
            cerr << "Input file could not be opened: " << fileName << endl;
            exit (-1);
        }


        // take count for non-empty cells
        int count = 0;
        for (int i = 0; i < getHeight() ; ++i) {
            for (int j = 0; j < getWidth() ; ++j) {
                if(gameCells[i][j].getStatusOfCell() != '.')
                    count ++;
            }
        }

        outputStream << count << "-";  // write a junk character for the seperate integers
        outputStream << getWidth() ;  // write the width of the board
        outputStream << '-';  // write a junk character for the seperate integers
        outputStream << getHeight() ;  // write the height of the board
        outputStream << players;  // write p or c

        for (int i = 0; i < rowVector.size(); ++i) {

            outputStream << rowVector[i]; // write move in the row vector
            outputStream << '-'; // write a junk character for the seperate integers
            outputStream << columnVector[i]; // write move in the column vector
            outputStream << '-';  // write a junk character for the seperate integers
        }


        outputStream << '+'; // put plus sign for seperate the vector and board containing

        // write all board to file.
        for (int i = 0; i < getHeight() ; ++i) {
            for (int j = 0; j < getWidth() ; ++j) {
                outputStream << gameCells[i][j].getStatusOfCell();
            }
        }
        // close file
        outputStream.close();
    }

// if command is LOAD, gets a file and reads from this and creates a new board
// resize the exist object.
    char **ConnectFourAbstract::loadFile(const string &fileName) {
        ifstream inputStream;
        int widthOfBoard = 0;
        int heightOfBoard = 0;
        char player = 0;

        // File is open?
        inputStream.open(fileName);
        if (!inputStream.is_open()) {
            cerr << "Input file could not be opened: " << fileName << endl;
            exit (-1);
        }

        int moveCount = 0;
        inputStream >> moveCount; // non-empty cells in the board
        char junk;
        inputStream >> junk ; // - sign
        inputStream >> widthOfBoard;  // size of board
        inputStream >> junk ; // - sign
        inputStream >> heightOfBoard;  // size of board
        inputStream >> player;  // p or c for the new game

        // clean old row and column vector for the new board
        for (int i = 0; i < rowVector.size() ; ++i) {
            rowVector.pop_back();
            columnVector.pop_back();
        }

        int row;
        int column;
        inputStream >> row; // read move for the row vector
        inputStream >> junk ; // read - sign
        inputStream >> column; // read move for the column vector
        inputStream >> junk ; // read - sign
        rowVector.push_back(row);  // add element
        columnVector.push_back(column); // add element

        // read the numbers till the + sign and add the element of the vectors
        int i = 0;
            while (i < moveCount - 1){
                inputStream >> row; // read move for the row vector
                inputStream >> junk; // read - sign
                inputStream >> column; // read move for the column vector
                inputStream >> junk; // read - sign
                rowVector.push_back(row); // add element
                columnVector.push_back(column); // add element
                i++;
        }
        inputStream >> junk ; // read + sign

        // reallocates the gamecells
        for (int i = 0; i < height ; ++i) {
            delete[] gameCells[i];
        }
        delete[] gameCells;

        setHeight(heightOfBoard);
        setWidth(widthOfBoard);

        // allocate for the new gamecell
        gameCells = new Cell*[heightOfBoard + 1];
        for (int k = 0; k <heightOfBoard + 1 ; ++k) {
            gameCells[k] = new Cell[widthOfBoard];
        }
        // initialize the new board.
        char character;
        for (int i = 1; i < heightOfBoard + 1; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                inputStream >> character;
                gameCells[i][j].setStatusOfCell(character);
                initializeStatus(character, gameCells, i, j, player);
            }
        }
        // size of board
        gameCells[0][0].setStatusOfCell(widthOfBoard);
        // p or c for the new game
        gameCells[0][2].setStatusOfCell(heightOfBoard);
        gameCells[0][3].setStatusOfCell(player);

        // print the new board
        printLetterBoard(widthOfBoard);
        for (int i = 1; i < heightOfBoard + 1; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                // if character is #, print space instead of #
                if(gameCells[i][j].getStatusOfCell() == '#'){
                    cout << "  ";
                }
                else{
                    //print the current character
                    cout << gameCells[i][j].getStatusOfCell();
                    cout <<" ";
                }
            }
            std::cout << std::endl;
        }
        // close the file
        inputStream.close();
    }

// parse the command like LOAD ABC.TXT
// takes the form like that [LOAD] [ABC.TXT]
// command is a reference and -> LOAD
// return string is -> ABC.TXT
    string ConnectFourAbstract::parseCommandLine(string &fileName)const {

        string command;
        getline(cin, command);
        if (command.length() == 0)
            exit(1);
        // tokenize according to space character
        string delimeter = " ";
        // first token is command
        fileName = command.substr(command.find_first_of(delimeter) + 1);
        // second token is command
        command = command.substr(0,command.find_first_of(delimeter));
        return command;
    }
// gets move LOAD/ SAVE / or A B C..
// parses the command in it
// returns a character according the parsed command
// LOAD -> # / SAVE -> $ / else x
    char ConnectFourAbstract::getMove(string &fileName, char playerCharacter)const {

        cout << "Turn of " << playerCharacter << endl;
        char character;
        string command;
        // Get command like SAVE FILE, LOAD FILE or A, B, C..
        command = parseCommandLine(fileName);
        // define a character for the string.
        if(command == "SAVE")
            character = '$';
        else if(command == "LOAD")
            character = '#';
        // if command not SAVE or LOAD, check the whether is legal or illegal.
        if (command != "SAVE" && command != "LOAD"){
            if(command.length() == 1){
                character = command[0];
            }
                // if is illegal, define that is 'x' and get command again.
            else{character = 'x';}
            int widthOfBoard = getWidth();
            while(!((character>='a' && character<='a' + widthOfBoard -1) || (character>='A' && character<='A'+ widthOfBoard -1 )
                    || character == '#' || character == '$')){
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
            }
        }
        return character;
    }

// gets a character and converts the character to interger
// if character is A, return value is 0, B -> 1...
    int ConnectFourAbstract::getPosition(char character)const {
        int letter = 'A';
        int letters = 'a';
        int position = 0;
        for (int i = 0; i < getWidth(); ++i) {
            if(character == static_cast<char>(letter) || character == static_cast<char>(letters)){
                position = i;
            }
            letter++;
            letters++;
        }
        // convert the integer
        return getHeight() * getWidth() - (getWidth() - position);
    }

    // Calls getMove for the letter, getPosition for the index and updates the board.
    // Checks all possibilities.
    int ConnectFourAbstract::makeMove(string &fileName, char playerCharacter, char players) {
        int widthOfBoard = getWidth();
        int heightOfBoard = getHeight();
        int win = 0;
        int xCount = 0;
        int oCount = 0;
        // initiliaze board again. (for remove size and character on the board)
        for (int i = 0; i < heightOfBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                initializeStatus(playerCharacter, gameCells, i , j, players);
                if(gameCells[i][j].getStatusOfCell() == 'X'){
                    ++xCount;
                }
                else if(gameCells[i][j].getStatusOfCell() == 'O'){
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

        // get move -> A , B , LOAD
        char movement = getMove(fileName, playerCharacter);
        // if command is SAVE
        if (movement == '$') {
            cout << "SAVED" << endl;
            // open a file and write on them.
            saveFile(fileName, players);
            // go on play
            // get move -> A , B , LOAD
            movement = getMove(fileName, playerCharacter);
            // convert the movement to integer
            int movePosition = getPosition(movement);
            // check the illegal move
            int illegalMove = updateBoard(playerCharacter, movePosition);
            // check the win or no
            int check = checkAll(playerCharacter);
            if (check > 0) {
                // if check is not equal zero, game is won
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                if (win == 1) {
                    printLetterBoard(widthOfBoard); // Print all
                    printBoard(widthOfBoard, heightOfBoard);
                }
                // get move on
                while (illegalMove != 0) {
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                    // convert the movement to integer
                    movePosition = getPosition(movement);
                    // check the illegal move
                    illegalMove = updateBoard(playerCharacter, movePosition);
                    // check the win or no
                    check = checkAll(playerCharacter);
                    if (check > 0) {
                        // if check is not equal zero, game is won
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        if (win == 1) {
                            printLetterBoard(widthOfBoard); // Print all
                            printBoard(widthOfBoard, heightOfBoard);
                        }

                    }

                }
            }
        }// if command is LOAD
        else if (movement == '#') {
            cout << "LOADED" << endl;
            // initialize board from the file
            loadFile(fileName);
            // pvp or pvc for the game character
            setWidth(gameCells[0][0].getStatusOfCell());
            setHeight(gameCells[0][2].getStatusOfCell());
            char players = gameCells[0][3].getStatusOfCell();
            // if pvp, game is person versus person
            if (players == 'P' || players == 'p') {
                win = newBoardGame(playerCharacter, fileName, players);
            }// if pvc, game is person versus to computer
            else {
                win = newBoardGameComputer('X', fileName, players);
            }
        }

            // if command is UNDO
        else if(movement == '~') {
            if(rowVector.size() - 1 >=0){
                cout << "UNDO OKEY" << endl;
                // get the last move for in the game like row and column
                int rowPosition = rowVector[rowVector.size() - 1]; // row
                int columnPosition = columnVector[columnVector.size() - 1]; // column

                // Put '.' indtead of X or O
                gameCells[rowPosition][columnPosition].setStatusOfCell('.');
                // set the row of cell
                gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                // set the position of cell
                gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
                // remove the move's row and column in the row and column vector
                columnVector.pop_back();
                rowVector.pop_back();
                // print all
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightOfBoard);

                // change the player
                if (playerCharacter == 'X')
                    playerCharacter = 'O';
                else
                    playerCharacter = 'X';

                // get move -> A , B , LOAD
                movement = getMove(fileName, playerCharacter);
                int i = 1;
                while (movement == '~') {
                    if(rowVector.size() - 1 >= 0){

                    }

                    // get the last move for in the game like row and column
                    rowPosition = rowVector[rowVector.size() - 1];
                    columnPosition = columnVector[columnVector.size() - 1];
                    // Put '.' indtead of X or O
                    gameCells[rowPosition][columnPosition].setStatusOfCell('.');
                    // set the row of cell
                    gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                    // set the position of cell
                    gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
                    // remove the move's row and column in the row and column vector
                    columnVector.pop_back();
                    rowVector.pop_back();
                    // print all
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightOfBoard);
                    i++;
                    //change the player
                    if (playerCharacter == 'X')
                        playerCharacter = 'O';
                    else
                        playerCharacter = 'X';
                    // get another move
                    movement = getMove(fileName, playerCharacter);

                }
                // convert the movement to integer
                int movePosition = getPosition(movement);
                // check the illegal move
                int illegalMove = updateBoard(playerCharacter, movePosition);
                // check the win or no
                int check = checkAll(playerCharacter);
                if (check > 0) {
                    // if check is not equal zero, game is won
                    std::cout << "And the winner is " << playerCharacter << std::endl;
                    win = 1;
                    if (win == 1) {
                        printLetterBoard(widthOfBoard); // Print all
                        printBoard(widthOfBoard, heightOfBoard);
                    }
                    // get move on
                    while (illegalMove != 0) {
                        // get move -> A , B , LOAD
                        movement = getMove(fileName, playerCharacter);
                        // convert the movement to integer
                        movePosition = getPosition(movement);
                        // check the illegal move
                        illegalMove = updateBoard(playerCharacter, movePosition);
                        // check the win or no
                        check = checkAll(playerCharacter);
                        if (check > 0) {
                            // if check is not equal zero, game is won
                            std::cout << "And the winner is " << playerCharacter << std::endl;
                            win = 1;
                            if (win == 1) {
                                printLetterBoard(widthOfBoard); // Print all
                                printBoard(widthOfBoard, heightOfBoard);
                            }
                        }
                    }
                }
            }

            else{
                cout << "Cant do UNDO" << endl;
                movement = getMove(fileName, playerCharacter);

            }
        }


            // command is not SAVE or LOAD, make move on
        else {
            if (checkAllBoard() != 1) {
                // convert the movement to integer
                int movePosition = getPosition(movement);
                // check the illegal move
                int illegalMove = updateBoard(playerCharacter, movePosition);
                // check the win or no
                int check = checkAll(playerCharacter);
                if (check > 0) {
                    // if check is not equal zero, game is won
                    std::cout << "And the winner is " << playerCharacter << std::endl;
                    win = 1;
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightOfBoard);
                }
                if (checkAllBoard() == 1) {
                    win = 1;
                }
                while (illegalMove != 0) {
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                    // convert the movement to integer
                    movePosition = getPosition(movement);
                    // check the illegal move
                    illegalMove = updateBoard(playerCharacter, movePosition);
                    check = checkAll(playerCharacter);
                    // check the win or no
                    if (check > 0) {
                        // if check is not equal zero, game is won
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        printLetterBoard(widthOfBoard);
                        printBoard(widthOfBoard, heightOfBoard);
                    }
                    if (checkAllBoard() == 1) {
                        win = 1;
                    }
                }
            }
        }
        return win;
    }

// Updates board after every move. Contains auto statement.
    int ConnectFourAbstract::updateBoard(char character, int position) {

        int widthOfBoard = getWidth();
        int heightOfBoard = getHeight();
        // column position if is A -> 0, b->1 ..
        int columnPosition = position %  widthOfBoard;
        // row position is 1 2 3 ...
        auto rowPosition = static_cast<int> (position / widthOfBoard);
        int illegalMove = 0;

        // if the cell object is full, error illegal move and gets another move
        if (gameCells[rowPosition][columnPosition].getStatusOfCell() == 'X' || gameCells[rowPosition][columnPosition].getStatusOfCell() == 'O') {
            while (rowPosition >= 0 && gameCells[rowPosition][columnPosition].getStatusOfCell() != '.') {
                rowPosition--;
                if (rowPosition < 0) {
                    // error message
                    std::cerr << "Illegal move\nTry another one!" << std::endl;
                    illegalMove = 1;
                }
            }
            // new move is not illegal, set the game cell with the character
            if (illegalMove != 1) { gameCells[rowPosition][columnPosition].setStatusOfCell(character) ;
                // set the state of cell
                initializeStatus(character, gameCells, rowPosition, columnPosition, 'P');
                // set the row of cell
                gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                // set the position of cell
                gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));};
            // add element by order to column vector.
            columnVector.push_back(columnPosition);
            // add element by order to row vector.
            rowVector.push_back(rowPosition);
        }//set the game cell with the character
        else if (gameCells[rowPosition][columnPosition].getStatusOfCell() == '.') {
            // set the row of cell
            gameCells[rowPosition][columnPosition].setStatusOfCell(character);
            initializeStatus(character, gameCells, rowPosition, columnPosition, 'P');
            // set the position of cell
            gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
            // set the position of cell
            gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
            // add element by order to column vector.
            columnVector.push_back(columnPosition);
            // add element by order to row vector.
            rowVector.push_back(rowPosition);
        }

        if (illegalMove != 1) {
            // print all board
            printLetterBoard(widthOfBoard);
            printBoard(widthOfBoard, heightOfBoard);
        }
        // return if move isillegal -> 1 else 0
        return illegalMove;
    }
// Turn of player 1 -> calls makeMove
    int ConnectFourAbstract::player1(string &fileName, char players) {
        // call make move
        return makeMove(fileName,'X',  players);
    }

// Turn of player 2 -> calls makeMove
    int ConnectFourAbstract::player2(string &fileName, char players) {
        // call make move
        return makeMove(fileName, 'O', players);
    }

// Play game from start to finish.
    void ConnectFourAbstract::playGame() {

        printLetterBoard(getWidth());
        printBoard(getWidth(), getHeight());
        string fileName;
        int win = 0;
        char players = playerTo(); // PVP or PVC
        // play with user
        if(players == 'P' || players == 'p'){
            while(win != 1 /*&& checkAllBoard(board, size) != 1*/){
                win = player1(fileName, players);
                if(win != 1){
                    win = player2(fileName, players);
                }
            }
        }
            // play with computer
        else{
            while(win != 1 && checkAllBoard() != 1){
                win = computer('X', fileName, players);
            }
        }

    }
// Ask the game will be played among whom
    char ConnectFourAbstract::playerTo() {

        std :: cout << "For PvP :P\nFor PvC :C"<< std :: endl;
        // get p or c from user
        string temp;
        getline(cin, temp);
        // if cin is newline character, exit the game
        if(temp.length() == 0)
            exit(1);
        while(temp.length() != 0){
            char players = temp[0];
            // if character is not equal p or ci, get a new one
            while(players != 'P' && players != 'p' && players != 'C' && players != 'c'){
                std :: cerr << "Please enter P or C" << std :: endl;
                getline(cin, temp);
                players = temp[0];
                // if cin is newline character, exit the game
                if(temp.length() == 0){
                    exit(1);
                }
            }
            return players;
        }

    }

// Calls the all check functions.
    int ConnectFourAbstract::checkAll(char character) {
        int returnValue = 0;
        return returnValue;
    }

// Converts the character upper to lower. Lower is default argument
    char ConnectFourAbstract::lowerCase(int character, int lower) {
        return static_cast<char>(character + lower);
    }

// Checks the whether the board is full or not
    int ConnectFourAbstract::checkAllBoard()const {
        int full = 0;
        int count = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        for (int i = 0; i < heightBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                if(gameCells[i][j].getStatusOfCell() != '.'){
                    ++count;
                }
            }
        }
        // if all board is full and there is not a winner return full and scoreless
        if(count == heightBoard * widthOfBoard){
            full = 1;
            std :: cout << "Scoreless" << std :: endl;
            //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
        }
        return full;
    }

// Play with computer
    int ConnectFourAbstract::computer(char playerCharacter, string &fileName, char players) {
        int win = 0;
        int location = 0;
        int check = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        char movement = getMove(fileName, playerCharacter);
        // for user
        if(movement == '$') {
            // if command is SAVE
            cout << "SAVED" << endl;
            // open a file and write on them
            saveFile(fileName, players);
            // keep playing
            cout << "Turn of " << playerCharacter << endl;
            // get move -> A , B , LOAD
            movement = getMove(fileName, playerCharacter);
            // convert the movement to integer
            int movePosition = getPosition(movement);
            location = getLocation(movePosition);
            // check the illegal move
            int illegalMove = updateBoard(playerCharacter, movePosition);
            check = checkAll(playerCharacter);
            if (check > 0) {
                // check the win or no
                // if check is not equal zero, game is won
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                if(win == 1){
                    printLetterBoard(widthOfBoard); // Print all
                    printBoard(widthOfBoard, heightBoard);
                }

                while (illegalMove != 0) {
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                    // convert the movement to integer
                    movePosition = getPosition(movement);
                    location = getLocation(movePosition);
                    // check the illegal move
                    illegalMove = updateBoard(playerCharacter, movePosition);
                    check = checkAll(playerCharacter);
                    if (check > 0) {
                        // check the win or no
                        // if check is not equal zero, game is won
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        if(win == 1){
                            printLetterBoard(widthOfBoard); // Print all
                            printBoard(widthOfBoard,heightBoard);
                        }
                    }
                }
            }
            // for computer
            if(win != 1 && illegalMove != 1){
                win = 0;
                std :: cout << "Turn of computer";
                std::cout << std::endl;
                // call computer function that include the computer moves
                playerComputer(location);
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightBoard);
                check = checkAll('O');
                if( check > 0) {
                    // if computer is win
                    std :: cout << "And the winner is "<< 'O'<<  std :: endl;
                    win = 1;
                    printLetterBoard(widthOfBoard); // Print all
                    printBoard(widthOfBoard,heightBoard);
                }
                if(checkAllBoard() == 1){
                    win = 1;
                }
            }

        }// if command LOAD
        else if(movement == '#'){
            cout << "LOADED" << endl ;
            // initialize the board from file
            loadFile(fileName);
            // p or c

            int widthOfNew = gameCells[0][0].getStatusOfCell();
            setWidth(widthOfNew);
            int heightOfNew = gameCells[0][2].getStatusOfCell();
            setHeight(heightOfNew);
            char players = gameCells[0][3].getStatusOfCell();
            if(players == 'P' || players == 'p'){
                // if command is LOAD, call the new function for play the new game
                // for user v user
                win = newBoardGame(playerCharacter, fileName, players);
            }
            else{
                // if command is LOAD, call the new function for play the new game
                // for user to computer
                win = newBoardGameComputer('X', fileName, players);
            }

        }


            // if command is UNDO
        else if(movement == '~') {
            if (rowVector.size() - 1 >= 0) {
                //TODO: CHECK boundries
                cout << "UNDO OKEY" << endl;
                // get the last move for in the game like row and column
                int rowPosition = rowVector[rowVector.size() - 1];
                int columnPosition = columnVector[columnVector.size() - 1];

                // Put '.' indtead of X or O
                gameCells[rowPosition][columnPosition].setStatusOfCell('.');
                // set the row of cell
                gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                // set the position of cell
                gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
                // remove the move's row and column in the row and column vector
                columnVector.pop_back();
                rowVector.pop_back();
                // print all
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightBoard);

                // for computer
                if(win != 1 && checkAllBoard() != 1){
                    win = 0;
                    std :: cout << "Turn of computer";
                    std::cout << std::endl;
                    playerComputer(location);
                    cout << rowVector[rowVector.size() - 1] << "-" << columnVector[columnVector.size() - 1] << endl;
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                    //cout << "Living Cell: " << getLivingCells() << endl;
                    check = checkAll('O');
                    if( check > 0) {
                        std :: cout << "And the winner is "<< 'O'<<  std :: endl;
                        win = 1;
                        printLetterBoard(widthOfBoard); // Print all
                        printBoard(widthOfBoard,heightBoard);
                        //cout << "Living Cell: " << getLivingCells() << endl;
                    }
                    if(checkAllBoard() == 1){
                        win = 1;
                    }
                }
             }
        }
                // if command is not SAVE or LOAD
        else {
            int movePosition = getPosition(movement);
            location = getLocation(movePosition);
            int illegalMove = updateBoard(playerCharacter, movePosition);
            cout << rowVector[rowVector.size() - 1] << "-" << columnVector[columnVector.size() - 1] << endl;
            check = checkAll(playerCharacter);
            if (check > 0) {
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                if(win == 1){
                    printLetterBoard(widthOfBoard); // Print all
                    printBoard(widthOfBoard, heightBoard);
                }

                while (illegalMove != 0) {
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                    // convert the movement to integer
                    movePosition = getPosition(movement);
                    // convert the location -> 1 A ->32 ..
                    location = getLocation(movePosition);
                    // check the illegal move
                    illegalMove = updateBoard(playerCharacter, movePosition);
                    cout << "Living Cell: " << endl;
                    check = checkAll(playerCharacter);
                    if (check > 0) {
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        if(win == 1){
                            printLetterBoard(widthOfBoard); // Print all
                            printBoard(widthOfBoard, heightBoard);
                        }
                    }

                }
            }
            // for computer
            if(win != 1 && illegalMove != 1 && checkAllBoard() != 1){
                win = 0;
                std :: cout << "Turn of computer";
                std::cout << std::endl;
                playerComputer(location);
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightBoard);
                check = checkAll('O');
                if( check > 0) {
                    std :: cout << "And the winner is "<< 'O'<<  std :: endl;
                    win = 1;
                    printLetterBoard(widthOfBoard); // Print all
                    printBoard(widthOfBoard,heightBoard);
                }
                if(checkAllBoard() == 1){
                    win = 1;
                }

            }
        }
        return  win;
    }

// Returns the last move's location. Contains auto statement.
    int ConnectFourAbstract::getLocation(int position) {
        int widthOfBoard = getWidth();
        // column if A -> 0...
        int columnPosition = position % widthOfBoard;
        // row -> 1 2 3
        auto rowPosition = static_cast<int> (position / widthOfBoard);
        // set the location, if there is no player in the cell
        // if 5. row and A. column is full, go 4.column A. row..
        if (gameCells[rowPosition][columnPosition].getStatusOfCell() == 'X' || gameCells[rowPosition][columnPosition].getStatusOfCell() == 'O') {
            while (rowPosition >= 0 && gameCells[rowPosition][columnPosition].getStatusOfCell() != '.') {
                rowPosition--;
            }
        }
        // return the location
        return rowPosition * widthOfBoard + columnPosition;
    }
// Decides behavior of computer
    void ConnectFourAbstract::playerComputer(int move) {
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        // set the row and column
        int row = move / widthOfBoard;
        int column = move % widthOfBoard;

        // if 3 X is vertical, put the character on top of them
        if(row + 2 < heightBoard && row - 1 >= 0 && gameCells[row + 1][column].getStatusOfCell() == 'X' && gameCells[row + 2][column].getStatusOfCell() == 'X'){
            if(gameCells[row - 1][column].getStatusOfCell() == '.'){
                gameCells[row - 1][column].setStatusOfCell('O');
                initializeStatus('O', gameCells, row - 1, column, 'C');
                gameCells[row - 1][column].setRowNumber(row - 1);
                gameCells[row - 1][column].setPositionOfCell(static_cast<char>(column + 'A'));
                std :: cout << static_cast<char>(column + 'A') << std :: endl;
                // add element by order to column vector.
                columnVector.push_back(column);
                // add element by order to row vector.
                rowVector.push_back(row - 1);

            }

        }// if 3 X is diagonal, put the character on diagonal of them.
        else if(column + 3 < widthOfBoard && gameCells[row][column + 1].getStatusOfCell() == 'X' && gameCells[row][column + 2].getStatusOfCell() == 'X' && gameCells[row][column + 3].getStatusOfCell() == '.' ){
            gameCells[row][column + 3].setStatusOfCell('O');
            initializeStatus('O', gameCells, row, column + 3, 'C');
            gameCells[row][column + 3].setRowNumber(row);
            gameCells[row][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
            std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column + 3);
            // add element by order to row vector.
            rowVector.push_back(row);

        }// if 3 X is horizontal, put the character on right of them.
        else if(column - 3 >= 0 && gameCells[row][column - 1].getStatusOfCell() == 'X' && gameCells[row][column - 2].getStatusOfCell() == 'X' && gameCells[row][column - 3].getStatusOfCell() == '.'){
            gameCells[row][column - 3].setStatusOfCell('O');
            initializeStatus('O', gameCells, row, column - 3, 'C');
            gameCells[row][column - 3].setRowNumber(row);
            gameCells[row][column - 3].setPositionOfCell(static_cast<char>(column + 'A' - 3));
            std :: cout << static_cast<char>(column + 'A' - 3) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column - 3);
            // add element by order to row vector.
            rowVector.push_back(row);
        }
            // if 2 X is vertical, put the character on top of them
        else if(column + 3 < widthOfBoard && row + 3 < heightBoard && gameCells[row + 1][column + 1].getStatusOfCell() == 'X' && gameCells[row + 2][column + 2].getStatusOfCell() == 'X' && gameCells[row + 3][column + 3].getStatusOfCell() == '.'){
            gameCells[row + 3][column + 3].setStatusOfCell('O');
            initializeStatus('O', gameCells, row + 3, column + 3, 'C');
            gameCells[row + 3][column + 3].setRowNumber(row + 3);
            gameCells[row + 3][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
            std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column + 3);
            // add element by order to row vector.
            rowVector.push_back(row + 3);
        }
            // if 2 X is diagonal, put the character on diagonal of them.
        else if(column - 2 >= 0 && row + 2 < heightBoard && row -2 >= 0 && column + 1 < widthOfBoard &&
                gameCells[row + 1][column - 1].getStatusOfCell() == 'X' && gameCells[row + 2][column - 2].getStatusOfCell() == 'X' && gameCells[row - 1][column + 1].getStatusOfCell() != '.' && gameCells[row - 2][column + 1].getStatusOfCell() != '.'){
            gameCells[row - 1][column + 1].setStatusOfCell('O');
            initializeStatus('O', gameCells, row - 1, column + 1, 'C');
            gameCells[row - 1][column + 1].setRowNumber(row - 1);
            gameCells[row - 1][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
            std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column + 1);
            // add element by order to row vector.
            rowVector.push_back(row - 1);
        }
            // if 2 X is horizontal, put the character on right of them.
        else if(column -1 >=0  && row + 1 < heightBoard && gameCells[row][column - 1].getStatusOfCell() == '.' &&
                gameCells[row + 1][column -1].getStatusOfCell() != '.' && gameCells[row][column].getStatusOfCell() == 'X' && gameCells[row][column+1].getStatusOfCell() == 'X'){
            gameCells[row][column - 1].setStatusOfCell('O');
            initializeStatus('O', gameCells, row , column - 1, 'C');
            gameCells[row][column - 1].setRowNumber(row);
            gameCells[row][column - 1].setPositionOfCell(static_cast<char>(column + 'A' - 1));
            std :: cout << static_cast<char>(column + 'A' - 1) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column - 1);
            // add element by order to row vector.
            rowVector.push_back(row);
        }// if 3 X is left diagonal, put the character on diagonal of them.
        else if(column + 1 < widthOfBoard && row == heightBoard - 1 && gameCells[row][column + 1].getStatusOfCell() == '.'){
            gameCells[row][column + 1].setStatusOfCell('O');
            initializeStatus('O', gameCells, row , column + 1, 'C');
            gameCells[row][column + 1].setRowNumber(row);
            gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
            std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column + 1);
            // add element by order to row vector.
            rowVector.push_back(row);
        }// if 2 X is left diagonal, put the character on diagonal of them.
        else if(column + 1 < widthOfBoard && row + 1 < heightBoard && gameCells[row][column + 1].getStatusOfCell() == '.' && gameCells[row + 1][column +1].getStatusOfCell() != '.'){
            gameCells[row][column + 1].setStatusOfCell('O');
            initializeStatus('O', gameCells, row , column + 1, 'C');
            gameCells[row][column + 1].setRowNumber(row);
            gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
            std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
            // add element by order to column vector.
            columnVector.push_back(column + 1);
            // add element by order to row vector.
            rowVector.push_back(row);
        }// else make move the first empty location
        else{
            for (int i = heightBoard - 1 ; i >= 0; --i) {
                for (int j = widthOfBoard - 1; j >= 0 ; --j) {
                    if(gameCells[i][j].getStatusOfCell() == '.'){
                        gameCells[i][j].setStatusOfCell('O');
                        initializeStatus('O', gameCells, i , j, 'C');
                        gameCells[i][j].setRowNumber(i);
                        gameCells[i][j].setPositionOfCell(static_cast<char>(j + 'A'));
                        std :: cout << static_cast<char>(j + 'A') << std :: endl;
                        // add element by order to column vector.
                        columnVector.push_back(j);
                        // add element by order to row vector.
                        rowVector.push_back(i);
                        j = -1;
                        i = -1;
                    }
                }
            }
        }
    }
// Keep on playing after the LOAD command with a person.
    int ConnectFourAbstract::newBoardGame(char playerCharacter, string &fileName, char players) {
        int win = 0;
        int xCount = 0;
        int oCount = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        // initiliaze board again. (for remove size and character on the board)
        for (int i = 0; i < heightBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                // initialize board
                gameCells[i][j].setStatusOfCell(gameCells[i + 1][j].getStatusOfCell());
                // set state
                initializeStatus(playerCharacter, gameCells, i , j, players);
                if(gameCells[i][j].getStatusOfCell() == 'X'){
                    ++xCount;
                }
                else if(gameCells[i][j].getStatusOfCell() == 'O'){
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
        while (win != 1 && checkAllBoard() != 1){
            int movement = getMove(fileName, playerCharacter);
            // if command is SAVE
            while(movement == '$'){
                cout << "SAVED" << endl;
                // open a file and write on them
                saveFile(fileName,players);
                movement = getMove(fileName, playerCharacter);
            }
            // command is LOAD
            while(movement == '#'){
                cout << "LOADED" << endl;
                // initialize board
                loadFile(fileName);
                // character for pvp or pvc
                int widthOfNew = gameCells[0][0].getStatusOfCell();
                int heightOfNew = gameCells[0][2].getStatusOfCell();
                players = gameCells[0][3].getStatusOfCell();
                if(players == 'P' || players == 'p'){
                    // go play on for user v user
                    win = newBoardGame(playerCharacter, fileName, players);
                }
                else{
                    // go play on for user v computer
                    win = newBoardGameComputer('X', fileName, players);
                }
            }

            // if command is UNDO
            while (movement == '~') {
                if(rowVector.size() - 1 >=0) {
                    cout << "UNDO OKEY" << endl;
                    // go on play
                    int rowPosition = rowVector[rowVector.size() - 1];
                    int columnPosition = columnVector[columnVector.size() - 1];
                    // Put '.' indtead of X or O
                    gameCells[rowPosition][columnPosition].setStatusOfCell('.');
                    // set the row of cell
                    gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                    // set the position of cell
                    gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
                    // remove the move's row and column in the row and column vector
                    columnVector.pop_back();
                    rowVector.pop_back();
                    // print all
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                    // change the player
                    if (playerCharacter == 'X')
                        playerCharacter = 'O';
                    else
                        playerCharacter = 'X';
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                }

            }
            // Keep playing on
            if(checkAllBoard() != 1){
                int movePosition = getPosition(movement);
                // check the illegal move
                int illegalMove = updateBoard(playerCharacter, movePosition);
                // check the win or no
                int check = checkAll(playerCharacter);
                if (check > 0) {
                    std::cout << "And the winner is " << playerCharacter << std::endl;
                    win = 1;
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                }
                if(checkAllBoard() == 1){
                    win = 1;
                }
                while (illegalMove != 0 && checkAllBoard() != 1 ) {
                    // get move -> A , B , LOAD
                    movement = getMove(fileName, playerCharacter);
                    // convert the movement to integer
                    movePosition = getPosition(movement);
                    // check the illegal move
                    illegalMove = updateBoard(playerCharacter, movePosition);
                    // check the win or no
                    check = checkAll(playerCharacter);
                    if (check > 0) {
                        // if check is not equal zero, game is won
                        std::cout << "And the winner is " << playerCharacter << std::endl;
                        win = 1;
                        printLetterBoard(widthOfBoard);
                        printBoard(widthOfBoard, heightBoard);
                    }
                    if(checkAllBoard() == 1){
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
    int ConnectFourAbstract::newBoardGameComputer(char playerCharacter, string &fileName, char players) {
        int win = 0;
        int widthOfBoard = getWidth();
        int heightBoard = getHeight();
        // initialize board again
        for (int i = 0; i < heightBoard; ++i) {
            for (int j = 0; j < widthOfBoard; ++j) {
                gameCells[i][j].setStatusOfCell(gameCells[i + 1][j].getStatusOfCell());
                initializeStatus(playerCharacter, gameCells, i , j, players);
            }
        }

        while (win != 1 && checkAllBoard() != 1) {
            int movement = getMove(fileName, playerCharacter);
            // if command is SAVE
            while (movement == '$') {
                cout << "SAVED" << endl;
                saveFile(fileName, players);
                movement = getMove(fileName, playerCharacter);
            }

            // if command is LOAD
            while (movement == '#') {
                cout << "LOADED" << endl;
                loadFile(fileName);
                int widthOfNew = gameCells[0][0].getStatusOfCell();
                int heightOfNew = gameCells[0][2].getStatusOfCell();
                players = gameCells[0][3].getStatusOfCell();
                if(players == 'P' || players == 'p'){
                    win = newBoardGame(playerCharacter, fileName, players);
                }
                else{
                    win = newBoardGameComputer('X', fileName, players);
                }
                if (win == 1) {
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                }
            }

            // if command is UNDO
            while(movement == '~') {
                if(rowVector.size() - 1 >=0) {
                    //TODO: CHECK boundries
                    cout << "UNDO OKEY" << endl;
                    // go on play
                    int rowPosition = rowVector[rowVector.size() - 1];
                    int columnPosition = columnVector[columnVector.size() - 1];
                    // Put '.' indtead of X or O
                    gameCells[rowPosition][columnPosition].setStatusOfCell('.');
                    // set the row of cell
                    gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
                    // set the position of cell
                    gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
                    // remove the move's row and column in the row and column vector
                    columnVector.pop_back();
                    rowVector.pop_back();
                    // print all
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);

                    // for computer
                    if(win != 1 && checkAllBoard() != 1){
                        win = 0;
                        std :: cout << "Turn of computer";
                        std::cout << std::endl;
                        int location = rowPosition * widthOfBoard + columnPosition;
                        playerComputer(location);
                        printLetterBoard(widthOfBoard);
                        printBoard(widthOfBoard, heightBoard);;
                        int check = checkAll('O');
                        if( check > 0) {
                            std :: cout << "And the winner is "<< 'O'<<  std :: endl;
                            win = 1;
                            printLetterBoard(widthOfBoard); // Print all
                            printBoard(widthOfBoard,heightBoard);
                        }
                        if(checkAllBoard() == 1){
                            win = 1;
                        }

                    }
                    // get another move
                    movement = getMove(fileName, 'X');
                }
            }

            // keep playing on
            int movePosition = getPosition(movement);
            int location = getLocation(movePosition);
            int illegalMove = updateBoard(playerCharacter, movePosition);
            int check = checkAll(playerCharacter);
            if (check > 0) {
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightBoard);
            }
            if(checkAllBoard() == 1){
                win = 1;
            }
            while (illegalMove != 0) {
                movement = getMove(fileName, playerCharacter);
                movePosition = getPosition(movement);
                location = getLocation(movePosition);
                illegalMove = updateBoard(playerCharacter, movePosition);
                check = checkAll(playerCharacter);
                if (check > 0) {
                    std::cout << "And the winner is " << playerCharacter << std::endl;
                    win = 1;
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                }

            }
            // for computer
            if (win != 1 && illegalMove != 1) {
                win = 0;
                std::cout << "Turn of computer";
                std::cout << std::endl;
                playerComputer(location);
                // print all
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightBoard);
                check = checkAll('O');
                if (check > 0) {
                    std::cout << "And the winner is " << 'O' << std::endl;
                    win = 1;
                    printLetterBoard(widthOfBoard);
                    printBoard(widthOfBoard, heightBoard);
                }
                if(checkAllBoard() == 1){
                    win = 1;
                }
            }
        }

        return win;
    }

// Play user versus user single step for every object
    void ConnectFourAbstract::play(int object) {

        string file;
        // set the object numberr
        int objectNumber = chooseObject();
        // set the players
        cout << objectVector[objectNumber - 1 ].getPlayers()<< endl;
        int check = 0;
        for (int i = 0; i < 5 ; ++i) {
            check += objectVector[i].getWin();
        }
        // check the boundries
        while((objectNumber < 0 || objectNumber > 5) ){
            cout<< "Enter 1-5" << endl;
            objectNumber = chooseObject();
        }// check the boundries
        // if the 5 objects is not over
        while(objectNumber > 0 && objectNumber <= 5 && check != 5){
            while(objectNumber < 0 || objectNumber > 5){
                cout<< "Enter 1-5" << endl;
                objectNumber = chooseObject();
            }
            // if the game plays versus to user
            if(objectVector[objectNumber - 1 ].getPlayers() == 'P' || objectVector[objectNumber - 1 ].getPlayers() == 'p'){
                if(objectVector[objectNumber - 1].getWin() != 1){
                    objectVector[objectNumber - 1].printLetterBoard((objectVector[objectNumber - 1].getWidth()));
                    objectVector[objectNumber - 1].printBoard((objectVector[objectNumber - 1].getWidth()), (objectVector[objectNumber - 1].getHeight()));
                    objectVector[objectNumber - 1].setWin(objectVector[objectNumber - 1].player1(file,players ));
                    if(objectVector[objectNumber - 1].getWin() != 1){
                        objectVector[objectNumber - 1].setWin(objectVector[objectNumber - 1].player2(file,players ));
                    }
                    //cout << "Living Cells:" << getLivingCells() << endl;
                    objectNumber = chooseObject();
                    //check the boundries
                    while(objectNumber < 0 || objectNumber > 5){
                        cout<< "Enter 1-5" << endl;
                        objectNumber = chooseObject();
                    }
                }
                else{
                    // if the game is over, select another object
                    cout << "This game is over."<< endl;
                    objectNumber = chooseObject();
                    while(objectNumber < 0 || objectNumber > 5){
                        cout<< "Enter 1-5" << endl;
                        objectNumber = chooseObject();
                    }
                }

            }
            else{
                if(objectVector[objectNumber - 1].getWin() != 1){
                    objectVector[objectNumber - 1].play();
                    //cout << "Living Cells:" << getLivingCells() << endl;
                    objectNumber = chooseObject();
                    while(objectNumber < 0 || objectNumber > 5){
                        cout<< "Enter 1-5" << endl;
                        objectNumber = chooseObject();
                    }
                }
                else{
                    // if the game is over, select another object
                    cout << "This game is over." << endl;
                    objectNumber = chooseObject();
                    while(objectNumber < 0 || objectNumber > 5){
                        cout<< "Enter 1-5" << endl;
                        objectNumber = chooseObject();
                    }
                }

            }check = 0;
            for (int i = 0; i < 5 ; ++i) {
                // if the object is over, increment the variable
                check += objectVector[i].getWin();
            }
        }
    }
// play against computer
    int ConnectFourAbstract::play() {

        string fileName;
        int win = 0;
        printLetterBoard(getWidth());
        printBoard(getWidth(), getHeight());
        // call computer function
        setWin(computer('X', fileName, players));
    }
// no parameter constructor for ConnectFour class
    ConnectFourAbstract::ConnectFourAbstract() {
        // default height and width is 5.
        setWidth(5);
        setHeight(5);
        setPlayers('N');
        // allocate the memory dynamically
        gameCells = new Cell*[height];
        for (int i = 0; i < height ; ++i) {
            gameCells[i] = new Cell[width];
        }// initiliaze the board with '.' characters
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < width; ++j) {
                gameCells[i][j].setStatusOfCell('.');
                initializeStatus('.', gameCells, i , j, players);
            }
        }
    }

// two parameter constructor for ConnectFour class
// gets height and width, allocates the memory according to them
    ConnectFourAbstract::ConnectFourAbstract(int widthBoard, int heightBoard) : width(widthBoard), height(heightBoard) {

        // set players
        players = 'N';
        //allocate the memory dynamically
        gameCells = new Cell*[height];
        for (int i = 0; i < height ; ++i) {
            gameCells[i] = new Cell[width];
        }
        // initialize the board
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                gameCells[i][j].setStatusOfCell('.');
                initializeStatus('.', gameCells, i , j, players);
            }
        }
    }
// copy constructor for ConnectFour class
    ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract &anObject) {
        // assign private members according to anObject
        players = anObject.players;
        height = anObject.height;
        width = anObject.width;
        // allocate the memory according to anObject
        gameCells = new Cell*[height];
        for (int i = 0; i < height ; ++i) {
            gameCells[i] = new Cell[width];
        }
        // initialize the gamecell according to an object
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                gameCells[i][j].setStatusOfCell(anObject.gameCells[i][j].getStatusOfCell());
                initializeStatus(anObject.gameCells[i][j].getStatusOfCell(), gameCells, i , j, players);
            }
        }
    }
// Destructor for ConnectFour class
    ConnectFourAbstract::~ConnectFourAbstract() {
        gameCells = new Cell*[height];
        for (int i = 0; i < height ; ++i) {
            gameCells[i] = new Cell[width];
        }
    }

// get the object number from user
    int ConnectFourAbstract::chooseObject() {
        cout << "Please choose an object" << endl;
        string objectNo;
        getline(cin, objectNo);
        // if objectno not equal an integer, exit the game
        if(objectNo.length() == 0)
            exit(1);
        // convert string to integer
        int objectNumber = stoi(objectNo);
        return objectNumber;
    }

// Set the state of cell
// if x-> user1, if o and versus to computer -> computer, if o and versus to user -> user2
    void ConnectFourAbstract::initializeStatus(char character, Cell** board, int i ,int j, char gameMode) {

        if (character == ' ')
            board[i][j].setStateOfObject("empty");
        else if(character == 'X')
            board[i][j].setStateOfObject("user1");
        else if(character == 'O' && (gameMode == 'P' || gameMode == 'p'))
            board[i][j].setStateOfObject("user2");
        else if(character == 'O'&& (gameMode == 'C' || gameMode == 'c'))
            board[i][j].setStateOfObject("computer");
    }
// get filename from user
    string ConnectFourAbstract::getFileName() {
        cout << "Enter filename" << endl;
        string file;
        getline(cin, file);
        if(file.length() == 0)
            exit(1);
        return file;
    }
// read from file for for board creation
    void ConnectFourAbstract::readBoard(string fileName) {
        // File is open?
        ifstream inputStream;
        inputStream.open(fileName);
        if (!inputStream.is_open()) {
            cerr << "Input file could not be opened: " << fileName << endl;
            exit (-1);
        }
        // read line by line
        string line;
        int rowCount = 0;
        while (!inputStream.eof()) {
            getline(inputStream, line);
            // if the character is null
            if(line != ""){
                rowCount++;
                int length = line.length();
                setWidth(length);
            }

        }
        // allocate the memory according to board
        setHeight(rowCount);
        gameCells = new Cell*[getHeight()];
        for (int i = 0; i < getHeight(); ++i) {
            gameCells[i] = new Cell[getWidth()];
        }
        // close the file
        inputStream.close();
        int i = 0;
        ifstream input;
        // open file again for read again
        input.open(fileName);
        // initialize the gameboard according to file
        for (int i = 0; i < getHeight() ; ++i) {
            getline(input, line);
            for (int j = 0; j <getWidth() ; ++j) {
                if (line[j] == '*') {
                    // if the character is *, board character is '.'
                    gameCells[i][j].setStatusOfCell('.');
                    initializeStatus('.', gameCells, i , j, players);
                    gameCells[i][j].setPositionOfCell(j);
                    gameCells[i][j].setRowNumber(i);
                } else {
                    // if the character is space, board character is '#'
                    gameCells[i][j].setStatusOfCell('#');
                    gameCells[i][j].setPositionOfCell(j);
                    gameCells[i][j].setRowNumber(i);
                }
            }
        }
        input.close();
    }
}

