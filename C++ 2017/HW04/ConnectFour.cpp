/*--------------------------------------------------------------------------*/
/*                                                                          */
/* HW01_141044063_Rumeysa_Karakavak                                         */
/*                                                                          */
/* Created on 1.11.2017 by Rumeysa_Karakavak                                */
/*                                                                          */
/* Description                                                              */
/* -----------                                                              */
/*   This file contains the board functions implementations                 */
/*--------------------------------------------------------------------------*/
#include "ConnectFour.h"

//decltype for lowercase characters
decltype('a') lowerCaseCharacter;
//initialize static member
int ConnectFour::livingCells = 0;

//get width by user for game board
int ConnectFour::widthFromUser(){

    std :: cout << "Enter the board width" << std :: endl;
    int widthOfBoard = 0;
    string temp;
    getline(cin, temp);
    widthOfBoard = stoi(temp);
    return widthOfBoard;
}

//get height by user for game board
int ConnectFour::heightFromUser(){
    std :: cout << "Enter the board height" << std :: endl;
    int heightOfBoard = 0;
    string temp;
    getline(cin, temp);
    heightOfBoard = stoi(temp);
    return heightOfBoard;
}
// print border of gameboard -> A B C..
void ConnectFour::printLetterBoard(int size) {
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
void ConnectFour :: printBoard(int widthOfBoard, int heightOfBoard)const {

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
void ConnectFour::saveFile(const string &fileName,char players) {

    ofstream outputStream;
    outputStream.open(fileName);
    // file is open?
    if (!outputStream.is_open()) {
        cerr << "Input file could not be opened: " << fileName << endl;
        exit (-1);
    }
    // write the width of the board
    outputStream << getWidth() ;
    // write the height of the board
    outputStream << '-';
    outputStream << getHeight() ;
    // write p or c
    outputStream << players;
    // write all board to file.
    for (int i = 0; i < getHeight() ; ++i) {
        for (int j = 0; j < getWidth() ; ++j) {
            outputStream << gameCells[i][j].getStatusOfCell() << "  ";
        }
        outputStream << endl;
    }
    // close file
    outputStream.close();
}
// if command is LOAD, gets a file and reads from this and creates a new board
// resize the exist object.
char **ConnectFour::loadFile(const string &fileName) {
    ifstream inputStream;
    int widthOfBoard = 0;
    int heightOfBoard = 0;
    char player = 0;
    char line;
    // File is open?
    inputStream.open(fileName);
    if (!inputStream.is_open()) {
        cerr << "Input file could not be opened: " << fileName << endl;
        exit (-1);
    }
    // size of board
    inputStream >> widthOfBoard;
    // p or c for the new game
    inputStream >> line ;
    inputStream >> heightOfBoard;
    // initialize board.
    inputStream >> player;

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
string ConnectFour::parseCommandLine(string &fileName)const {

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
char ConnectFour::getMove(string &fileName)const {
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
int ConnectFour::getPosition(char character)const {
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
int ConnectFour::makeMove(string &fileName, char playerCharacter, char players) {
    int widthOfBoard = getWidth();
    int heightOfBoard = getHeight();
    int win = 0;
    // get move -> A , B , LOAD
    char movement = getMove(fileName);
    // if command is SAVE
    if (movement == '$') {
        cout << "SAVED" << endl;
        // open a file and write on them.
        saveFile(fileName, players);
        // go on play
        cout << "Turn of " << playerCharacter << endl;
        // get move -> A , B , LOAD
        movement = getMove(fileName);
        // convert the movement to integer
        int movePosition = getPosition(movement);
        // check the illegal move
        int illegalMove = updateBoard(playerCharacter, movePosition);
        // check the win or no
        int check = checkAll(playerCharacter);
        if(illegalMove != 1){setLivingCells();}
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
                movement = getMove(fileName);
                // convert the movement to integer
                movePosition = getPosition(movement);
                // check the illegal move
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
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
        // command is not SAVE or LOAD, make move on
    else {
        if (checkAllBoard() != 1) {
            // convert the movement to integer
            int movePosition = getPosition(movement);
            // check the illegal move
            int illegalMove = updateBoard(playerCharacter, movePosition);
            if(illegalMove != 1){setLivingCells();}
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
                movement = getMove(fileName);
                // convert the movement to integer
                movePosition = getPosition(movement);
                // check the illegal move
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
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
int ConnectFour::updateBoard(char character, int position) {

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
    }//set the game cell with the character
    else if (gameCells[rowPosition][columnPosition].getStatusOfCell() == '.') {
        // set the row of cell
        gameCells[rowPosition][columnPosition].setStatusOfCell(character);
        initializeStatus(character, gameCells, rowPosition, columnPosition, 'P');
        // set the position of cell
        gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
        // set the position of cell
        gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
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
int ConnectFour::player1(string &fileName, char players) {
    //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
    std :: cout << "Turn of player X";
    std::cout << std::endl;
    // call make move
    return makeMove(fileName,'X',  players);
}

// Turn of player 2 -> calls makeMove
int ConnectFour::player2(string &fileName, char players) {
    //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
    std :: cout << "Turn of player O";
    std::cout << std::endl;
    // call make move
    return makeMove(fileName, 'O', players);
}

// Play game from start to finish.
void ConnectFour::playGame() {
    // delete the gamecell from exist object
    for (int i = 0; i < height ; ++i) {
        delete[] gameCells[i];
    }
    delete[] gameCells;
    // resize the game cell
    // get filename
    string file = getFileName();
    // allocate the new memory for the gamecell
    readBoard(file);
    // print board
    printLetterBoard(width);
    printBoard(width, height);

    string fileName;
    int win = 0;
    char players = playerTo(); // PVP or PVC
    // play with user
    if(players == 'P' || players == 'p'){
        while(win != 1 /*&& checkAllBoard(board, size) != 1*/){
            win = player1(fileName, players);
            //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
            if(win != 1){
                win = player2(fileName, players);
                //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
            }
        }
    }
        // play with computer
    else{
        while(win != 1 && checkAllBoard() != 1){
            win = computer('X', fileName, players);
            //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
        }
    }

}
// Ask the game will be played among whom
char ConnectFour::playerTo() {

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
// Checks the top and down.
int ConnectFour::verticalCheck(char character) {
    int characterCount = 0;
    int returnValue = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();
    // look all board and if 4 same characters are in a row return 1;
    // x or o player is won.
    for (int i = 0 ; i < widthOfBoard; ++i) {
        for (int j = 0; j < heightBoard; ++j) {
            if(gameCells[j][i].getStatusOfCell() == character){
                characterCount ++;
                if (characterCount == 4){
                    returnValue = 1;
                    for (int k = 0; k < characterCount; ++k) {
                        // if there is a winner, convert character to lowercase
                        lowerCaseCharacter = lowerCase(character);
                        gameCells[j - k][i].setStatusOfCell(lowerCaseCharacter);
                    }
                    i = widthOfBoard;
                    j = heightBoard;
                }
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return returnValue;
}

// Checks left and right
int ConnectFour::horizontalCheck(char character) {
    int characterCount = 0;
    int returnValue = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();

    // look all board and if 4 same characters are side by side return 1;
    // x or o player is won.
    for (int i = 0 ; i < heightBoard; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            if(gameCells[i][j].getStatusOfCell() == character){
                characterCount ++;
                if (characterCount == 4){
                    returnValue = 1;
                    for (int k = 0; k < characterCount; ++k) {
                        // if there is a winner, convert character to lowercase
                        lowerCaseCharacter = lowerCase(character);
                        gameCells[i][j - k].setStatusOfCell(lowerCaseCharacter);
                    }
                    i = heightBoard;
                    j = widthOfBoard;
                }
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return returnValue;
}

// Checks the diagonal line like that -> '\'
int ConnectFour::diagonalCheck(char character) {
    int characterCount = 0;
    int returnValue = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();

    // look all board and if 4 same characters diagonal return 1;
    // x or o player is won.
    for (int i = 0; i < widthOfBoard; ++i) {
        for (int j = 0; j < heightBoard ; ++j) {
            int l = j;
            int m = i;
            int k = 0;
            while (k < 4 and l < heightBoard and m < widthOfBoard){
                if (gameCells[l][m].getStatusOfCell() == character) {
                    ++characterCount;
                    ++l;
                    ++m;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int n = 0; n < characterCount; ++n) {
                            // if there is a winner, convert character to lowercase
                            lowerCaseCharacter = lowerCase(character);
                            gameCells[j + n][i + n].setStatusOfCell(lowerCaseCharacter);
                        }

                        k = 3;
                    }
                }
                ++k;
            }
            if (characterCount == 4){
                returnValue = 1;
                i = widthOfBoard;
                j = heightBoard;
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return  returnValue;
}

// Checks the diagonal line like that -> '/'
int ConnectFour::reverseDiagonalCheck(char character) {
    int characterCount = 1;
    int returnValue = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();

    // look all board and if 4 same characters diagonal return 1;
    // x or o player is won.
    for (int i = 0; i < widthOfBoard; ++i) {
        for (int j = 0; j < heightBoard ; ++j) {
            int l = j;
            int m = i;
            int k = 0;
            while (k < 4 and l < heightBoard and m >= 0){
                if (gameCells[l][m].getStatusOfCell() == character) {
                    ++characterCount;
                    ++l;
                    --m;
                    if (characterCount == 4){
                        returnValue = 1;
                        for (int n = 0; n < characterCount; ++n) {
                            // if there is a winner, convert character to lowercase
                            lowerCaseCharacter = lowerCase(character);
                            gameCells[j + n][i - n].setStatusOfCell(lowerCaseCharacter);
                        }

                        k =  3;
                    }
                }
                ++k;
            }
            if (characterCount == 4){
                returnValue = 1;
                i = widthOfBoard;
                j = heightBoard;
            }
            else{
                characterCount = 0;
            }
        }
        characterCount = 0;
    }
    return  returnValue;
}

// Calls the all check functions.
int ConnectFour::checkAll(char character) {
    int returnValue = 0;
    returnValue += horizontalCheck(character);
    returnValue += verticalCheck(character);
    returnValue += diagonalCheck(character);
    returnValue += reverseDiagonalCheck(character);

    return returnValue;
}

// Converts the character upper to lower. Lower is default argument
char ConnectFour::lowerCase(int character, int lower) {
    return static_cast<char>(character + lower);
}

// Checks the whether the board is full or not
int ConnectFour::checkAllBoard()const {
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
int ConnectFour::computer(char playerCharacter, string &fileName, char players) {
    int win = 0;
    int location = 0;
    int check = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();
    cout << "Turn of X" << endl;
    char movement = getMove(fileName);
    // for user
    if(movement == '$') {
        // if command is SAVE
        cout << "SAVED" << endl;
        // open a file and write on them
        saveFile(fileName, players);
        // keep playing
        cout << "Turn of " << playerCharacter << endl;
        // get move -> A , B , LOAD
        movement = getMove(fileName);
        // convert the movement to integer
        int movePosition = getPosition(movement);
        location = getLocation(movePosition);
        // check the illegal move
        int illegalMove = updateBoard(playerCharacter, movePosition);
        if(illegalMove != 1){setLivingCells();}
        //cout << "Living Cell: " << getLivingCells() << endl;
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
                movement = getMove(fileName);
                // convert the movement to integer
                movePosition = getPosition(movement);
                location = getLocation(movePosition);
                // check the illegal move
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                //cout << "Living Cell: " << getLivingCells() << endl;
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
            setLivingCells();
            //cout << "Living Cell: " << getLivingCells() << endl;
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

    }// if command is not SAVE or LOAD
    else {
        int movePosition = getPosition(movement);
        location = getLocation(movePosition);
        int illegalMove = updateBoard(playerCharacter, movePosition);
        if(illegalMove != 1){setLivingCells();}
        //cout << "Living Cell: " << getLivingCells() << endl;
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
                movement = getMove(fileName);
                // convert the movement to integer
                movePosition = getPosition(movement);
                // convert the location -> 1 A ->32 ..
                location = getLocation(movePosition);
                // check the illegal move
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
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
            setLivingCells();
            std :: cout << "Turn of computer";
            std::cout << std::endl;
            playerComputer(location);
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
    return  win;
}

// Returns the last move's location. Contains auto statement.
int ConnectFour::getLocation(int position) {
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
void ConnectFour::playerComputer(int move) {
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
        }

    }// if 3 X is diagonal, put the character on diagonal of them.
    else if(column + 3 < widthOfBoard && gameCells[row][column + 1].getStatusOfCell() == 'X' && gameCells[row][column + 2].getStatusOfCell() == 'X' && gameCells[row][column + 3].getStatusOfCell() == '.' ){
        gameCells[row][column + 3].setStatusOfCell('O');
        initializeStatus('O', gameCells, row, column + 3, 'C');
        gameCells[row][column + 3].setRowNumber(row);
        gameCells[row][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
        std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;

    }// if 3 X is horizontal, put the character on right of them.
    else if(column - 3 >= 0 && gameCells[row][column - 1].getStatusOfCell() == 'X' && gameCells[row][column - 2].getStatusOfCell() == 'X' && gameCells[row][column - 3].getStatusOfCell() == '.'){
        gameCells[row][column - 3].setStatusOfCell('O');
        initializeStatus('O', gameCells, row, column - 3, 'C');
        gameCells[row][column - 3].setRowNumber(row);
        gameCells[row][column - 3].setPositionOfCell(static_cast<char>(column + 'A' - 3));
        std :: cout << static_cast<char>(column + 'A' - 3) << std :: endl;
    }
        // if 2 X is vertical, put the character on top of them
    else if(column + 3 < widthOfBoard && row + 3 < heightBoard && gameCells[row + 1][column + 1].getStatusOfCell() == 'X' && gameCells[row + 2][column + 2].getStatusOfCell() == 'X' && gameCells[row + 3][column + 3].getStatusOfCell() == '.'){
        gameCells[row + 3][column + 3].setStatusOfCell('O');
        initializeStatus('O', gameCells, row + 3, column + 3, 'C');
        gameCells[row + 3][column + 3].setRowNumber(row + 3);
        gameCells[row + 3][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
        std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;
    }
        // if 2 X is diagonal, put the character on diagonal of them.
    else if(column - 2 >= 0 && row + 2 < heightBoard && row -2 >= 0 && column + 1 < widthOfBoard &&
            gameCells[row + 1][column - 1].getStatusOfCell() == 'X' && gameCells[row + 2][column - 2].getStatusOfCell() == 'X' && gameCells[row - 1][column + 1].getStatusOfCell() != '.' && gameCells[row - 2][column + 1].getStatusOfCell() != '.'){
        gameCells[row - 1][column + 1].setStatusOfCell('O');
        initializeStatus('O', gameCells, row - 1, column + 1, 'C');
        gameCells[row - 1][column + 1].setRowNumber(row - 1);
        gameCells[row - 1][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
        // if 2 X is horizontal, put the character on right of them.
    else if(column -1 >=0  && row + 1 < heightBoard && gameCells[row][column - 1].getStatusOfCell() == '.' &&
            gameCells[row + 1][column -1].getStatusOfCell() != '.' && gameCells[row][column].getStatusOfCell() == 'X' && gameCells[row][column+1].getStatusOfCell() == 'X'){
        gameCells[row][column - 1].setStatusOfCell('O');
        initializeStatus('O', gameCells, row , column - 1, 'C');
        gameCells[row][column - 1].setRowNumber(row);
        gameCells[row][column - 1].setPositionOfCell(static_cast<char>(column + 'A' - 1));
        std :: cout << static_cast<char>(column + 'A' - 1) << std :: endl;
    }// if 3 X is left diagonal, put the character on diagonal of them.
    else if(column + 1 < widthOfBoard && row == heightBoard - 1 && gameCells[row][column + 1].getStatusOfCell() == '.'){
        gameCells[row][column + 1].setStatusOfCell('O');
        initializeStatus('O', gameCells, row , column + 1, 'C');
        gameCells[row][column + 1].setRowNumber(row);
        gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }// if 2 X is left diagonal, put the character on diagonal of them.
    else if(column + 1 < widthOfBoard && row + 1 < heightBoard && gameCells[row][column + 1].getStatusOfCell() == '.' && gameCells[row + 1][column +1].getStatusOfCell() != '.'){
        gameCells[row][column + 1].setStatusOfCell('O');
        initializeStatus('O', gameCells, row , column + 1, 'C');
        gameCells[row][column + 1].setRowNumber(row);
        gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
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
                    j = -1;
                    i = -1;
                }
            }
        }
    }
}
// Keep on playing after the LOAD command with a person.
int ConnectFour::newBoardGame(char playerCharacter, string &fileName, char players) {
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
        cout << "Turn of " << playerCharacter << endl;
        int movement = getMove(fileName);
        // if command is SAVE
        while(movement == '$'){
            cout << "SAVED" << endl;
            // open a file and write on them
            saveFile(fileName,players);
            cout << "Turn of " << playerCharacter << endl;
            movement = getMove(fileName);
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
        // Keep playing on
        if(checkAllBoard() != 1){
            int movePosition = getPosition(movement);
            int illegalMove = updateBoard(playerCharacter, movePosition);
            if(illegalMove != 1){setLivingCells();}
            //cout << "Living Cells:" << getLivingCells() << endl;
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
                movement = getMove(fileName);
                // convert the movement to integer
                movePosition = getPosition(movement);
                // check the illegal move
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                // check the win or no
                //cout << "Living Cells:" << getLivingCells() << endl;
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
int ConnectFour::newBoardGameComputer(char playerCharacter, string &fileName, char players) {
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
        cout << "Turn of " << playerCharacter << endl;
        int movement = getMove(fileName);
        // if command is SAVE
        while (movement == '$') {
            cout << "SAVED" << endl;
            saveFile(fileName, players);
            cout << "Turn of " << playerCharacter << endl;
            movement = getMove(fileName);
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
        // keep playing on
        int movePosition = getPosition(movement);
        int location = getLocation(movePosition);
        int illegalMove = updateBoard(playerCharacter, movePosition);
        if(illegalMove != 1){setLivingCells();}
        //cout << "Living Cells:" << getLivingCells() << endl;
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
            movement = getMove(fileName);
            movePosition = getPosition(movement);
            location = getLocation(movePosition);
            illegalMove = updateBoard(playerCharacter, movePosition);
            if(illegalMove != 1){setLivingCells();}
            //cout << "Living Cells:" << getLivingCells() << endl;
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
            //setLivingCells();
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

// create 5 object and pushback this objects in a vector
void ConnectFour::multiGameInitializer(){
    //create temp vector
    vector<ConnectFour> tempVector;
    //take 5 object
    for (int i = 0; i < 5 ; ++i) {
        // string parameter constructor
        string filename = getFileName();
        ConnectFour temp(filename);
        tempVector.push_back(temp);
        tempVector[i].setPlayers(playerTo());
    }
    setObjectVector(tempVector);
}
// Asks the game mode
// For single game -> S, multigame -> Mode
char ConnectFour::SingleOrMultipleGame()const {
    // get from user
    cout << "Please enter the game mode\nSingle: S or Multiple: M" << endl;
    string temp;
    getline(cin, temp);
    // if the character is not S or M exit from game
    if(temp.length() == 0)
        exit(1);
    while(temp.length() != 0){
        char mode = temp[0];
        while(mode != 'S' && mode != 's' && mode != 'M' && mode != 'm'){
            // take another character
            std :: cerr << "Please enter S or M" << std :: endl;
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
// Play user versus user single step for every object
void ConnectFour::play(int object) {

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
int ConnectFour::play() {
    string fileName;
    int win = 0;
    printLetterBoard(getWidth());
    printBoard(getWidth(), getHeight());
    // call computer function
    setWin(computer('X', fileName, players));
}
// no parameter construuctor for ConnectFour class
ConnectFour::ConnectFour() {
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
// one parameter constructor for ConnectFour class
// allocates the memory according to file
ConnectFour::ConnectFour(string filename) {

    readBoard(filename);
    printLetterBoard(getWidth());
    printBoard(width, height);
}
// two parameter constructor for ConnectFour class
// gets height and width, allocates the memory according to them
ConnectFour::ConnectFour(int widthBoard, int heightBoard) : width(widthBoard), height(heightBoard) {

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
ConnectFour::ConnectFour(const ConnectFour &anObject) {
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
ConnectFour::~ConnectFour() {
    gameCells = new Cell*[height];
    for (int i = 0; i < height ; ++i) {
        gameCells[i] = new Cell[width];
    }
}
// no parameter constructor for Cell class
ConnectFour::Cell::Cell() {
    positionOfCell = 0;
    rowNumber = 0;
    statusOfCell = '.';
    stateOfObject = " ";
}
// gets the state constructor forn Cell class
ConnectFour::Cell::Cell(string state) {
    positionOfCell = 0;
    rowNumber = 0;
    statusOfCell = '.';
    stateOfObject = state;
}
// overloaded pre-increment operator for Cell class
//The ++ operator changes the cell state from empty to user1, from user1 to user2,
// from user2 to computer, from computer back to empty.
const ConnectFour :: Cell operator++(ConnectFour::Cell &anObject) {

    if( anObject.getState() == "empty")
        anObject.setStateOfObject("user1");
    else if(anObject.getState() == "user1")
        anObject.setStateOfObject("user2");
    else if(anObject.getState() == "user2")
        anObject.setStateOfObject("computer");
    else if(anObject.getState() == "computer")
        anObject.setStateOfObject("empty");

    return anObject;
}
// overloaded post-increment operator for Cell class
//The ++ operator changes the cell state from empty to user1, from user1 to user2,
// from user2 to computer, from computer back to empty.
const ConnectFour::Cell operator++(ConnectFour::Cell &anObject, int ignore) {

    string state = anObject.getState();
    ConnectFour :: Cell object(state);

    if( anObject.getState() == "empty")
        anObject.setStateOfObject("user1");
    else if(anObject.getState() == "user1")
        anObject.setStateOfObject("user2");
    else if(anObject.getState() == "user2")
        anObject.setStateOfObject("computer");
    else if(anObject.getState() == "computer")
        anObject.setStateOfObject("empty");

    return object;
}
// overloaded stream extraction operator for Cell class
// prints private members of Cell class
ostream &operator<<(ostream &outstream, const ConnectFour :: Cell &object) {

    outstream << " Player character"<<object.getStatusOfCell() << endl;
    outstream << " Player status"<<object.getState() << endl;
    outstream << " Row number"<<object.getRowNumber() << endl;
    outstream << " Column character"<<object.getPositionOfCell() << endl;
    return outstream;
}
// overloaded stream insertion operator for Cell class
// takes private members of Cell class
istream &operator>>(istream &instream, ConnectFour :: Cell &object) {
    instream >> object.statusOfCell;
    instream >> object.stateOfObject;
    instream >> object.rowNumber;
    instream >> object.positionOfCell;
    return instream;
}
// overloaded == operator
// compares 2 Cell object(character, state, row, column)
// if equals,  return true else false
bool operator ==(const ConnectFour :: Cell& anobject, const ConnectFour :: Cell& anotherObject ){

    if((anobject.statusOfCell == anotherObject.statusOfCell)
            && (anobject.stateOfObject == anotherObject.stateOfObject)
            && (anobject.rowNumber == anotherObject.rowNumber)
            && (anobject.positionOfCell == anotherObject.positionOfCell)){
        return true;
    }
    else return false;
}

// overloaded assignment operator for ConnectFour class
ConnectFour ConnectFour::operator=(const ConnectFour &anObject) {

    // if objects are not equal
    if(*this != anObject){
        // delete the exist gamecell
        for (int i = 0; i < height ; ++i) {
            delete[] gameCells[i];
        }
        delete[] gameCells;
        // assign private members according to anobject
        players = anObject.players;
        height = anObject.height;
        width = anObject.width;
        // allocate the memory according to height and width of anObject
        gameCells = new Cell*[height];
        for (int i = 0; i < height ; ++i) {
            gameCells[i] = new Cell[width];
        }
        // assign gamecell according to anobject
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                gameCells[i][j].setStatusOfCell(anObject.gameCells[i][j].getStatusOfCell());
                initializeStatus(anObject.gameCells[i][j].getStatusOfCell(), gameCells, i , j, players);
            }
        }
        return *this;
    }
        //if the objects are equal, return this object
    else
        return *this;

}
// get the object number from user
int ConnectFour::chooseObject() {
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
void ConnectFour::initializeStatus(char character, Cell** board, int i ,int j, char gameMode) {

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
string ConnectFour::getFileName() {
    cout << "Enter filename" << endl;
    string file;
    getline(cin, file);
    if(file.length() == 0)
        exit(1);
    return file;
}
// read from file for for board creation
void ConnectFour::readBoard(string fileName) {
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
// overloaded != operator
// compares 2 ConnectFour object(width, height, gamecells)
// if equals,  return true else false
bool ConnectFour::operator==(const ConnectFour &anobject)const {
    int compare = 0;
    if(height == anobject.height && width == anobject.width && players == anobject.players){
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if((gameCells[i][j].getState() != anobject.gameCells[i][j].getState())){
                    j = width;
                    i = height;
                    compare = -1;
                }
            }
        }
    }
    else
        compare = -1;

    if(compare != 0)
        return false;
    else return true;

}
// overloaded != operator
// compares 2 ConnectFour object(width, height, gamecells)
// if not equals,  return true else false
bool ConnectFour::operator!=(const ConnectFour &anobject)const {
    if (*this == anobject)
        return false;
    return true;
}


