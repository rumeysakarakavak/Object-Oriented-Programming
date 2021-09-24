//
// Created by Rumeysa on 14.10.2017.
//

#include "ConnectFour.h"
decltype('a') lowerCaseCharacter;
int ConnectFour::livingCells = 0;

int ConnectFour::widthFromUser(){
    std :: cout << "Enter the board width" << std :: endl;
    int widthOfBoard = 0;
    std :: cin >> widthOfBoard;
    //std :: cin.clear();
    //std :: cin.ignore();
    setWidth(widthOfBoard);
}
int ConnectFour::heightFromUser(){
    std :: cout << "Enter the board height" << std :: endl;
    int heightOfBoard = 0;
    std :: cin >> heightOfBoard;
    //std :: cin.clear();
   // std :: cin.ignore();
    setHeight(heightOfBoard);
}

// First look at the game board. Contains auto statement.
void ConnectFour :: initializeBoard() {

    heightFromUser();
    widthFromUser();
    int widthOfBoard = getWidth();
    int heightOfBoard = getHeight();
    vector<vector< Cell>> aGameCell;
    vector<Cell> tempVec;
    Cell temp;

    for(int i=0; i<widthOfBoard; i++){
        tempVec.push_back(temp);
    }
    for (int j = 0; j < heightOfBoard ; ++j) {
        aGameCell.push_back(tempVec);
    }

    setGameCells(aGameCell);

    // game board initializer
    printLetterBoard(widthOfBoard);
    for (int i = 0; i < heightOfBoard; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            gameCells[i][j].setStatusOfCell('.');
            std::cout << gameCells[i][j].getStatusOfCell() << "  ";
        }
        std::cout << std::endl;
    }
}

void ConnectFour::printLetterBoard(int size) {
    char letterBoard[size];
    int firstLetter = 'A';
    for (int i = 0; i < size; ++i) {
        letterBoard[i] = static_cast<char>(firstLetter);
        firstLetter ++;
        std :: cout << letterBoard[i]<< "  ";
    }
    std :: cout << std :: endl;
}


// Prints all board
void ConnectFour :: printBoard(int widthOfBoard, int heightOfBoard)const {

    for (int i = 0; i < heightOfBoard; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            std::cout << gameCells[i][j].getStatusOfCell() << "  ";
        }
        std::cout << std::endl;
    }
}

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

    outputStream.close();
}

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

    gameCells.resize(heightOfBoard + 1);
    for (int i = 0; i < heightOfBoard + 1; ++i){
        gameCells[i].resize(widthOfBoard);
    }

    char character;
    for (int i = 1; i < heightOfBoard + 1; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            inputStream >> character;
            gameCells[i][j].setStatusOfCell(character);
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
            std::cout << gameCells[i][j].getStatusOfCell() << "  ";
        }
        std::cout << std::endl;
    }
    inputStream.close();
}

string ConnectFour::parseCommandLine(string &fileName)const {

    string command;
    getline(cin, command);
    string delimeter = " ";
    fileName = command.substr(command.find_first_of(delimeter) + 1);
    command = command.substr(0,command.find_first_of(delimeter));
    return command;
}

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
    return getHeight() * getWidth() - (getWidth() - position);
}

// Calls getMove for the letter, getPosition for the index and updates the board.
// Checks all possibilities.
int ConnectFour::makeMove(string &fileName, char playerCharacter, char players) {
    int widthOfBoard = getWidth();
    int heightOfBoard = getHeight();
    int win = 0;
    char movement = getMove(fileName);
    // if command is SAVE
    if (movement == '$') {
        cout << "SAVED" << endl;
        // open a file and write on them.
        saveFile(fileName, players);
        // go on play
        cout << "Turn of " << playerCharacter << endl;
        movement = getMove(fileName);
        int movePosition = getPosition(movement);
        int illegalMove = updateBoard(playerCharacter, movePosition);
        int check = checkAll(playerCharacter);
        if(illegalMove != 1){setLivingCells();}
        if (check > 0) {
            std::cout << "And the winner is " << playerCharacter << std::endl;
            win = 1;
            if (win == 1) {
                printLetterBoard(widthOfBoard); // Print all
                printBoard(widthOfBoard, heightOfBoard);
            }
            // get move on
            while (illegalMove != 0) {
                movement = getMove(fileName);
                movePosition = getPosition(movement);
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                check = checkAll(playerCharacter);
                if (check > 0) {
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
        // initializa board from the file
        loadFile(fileName);
        // pvp or pvc for the game character
        setWidth(gameCells[0][0].getStatusOfCell());
        setHeight(gameCells[0][2].getStatusOfCell());
        char players = gameCells[0][3].getStatusOfCell();
        // if pvp
        if (players == 'P' || players == 'p') {
            win = newBoardGame(playerCharacter, fileName, players);
        }// if pvc
        else {
            win = newBoardGameComputer('X', fileName, players);
        }
    }
    // command is not SAVE or LOAD, make move on
    else {
        if (checkAllBoard() != 1) {
            int movePosition = getPosition(movement);
            int illegalMove = updateBoard(playerCharacter, movePosition);
            if(illegalMove != 1){setLivingCells();}
            int check = checkAll(playerCharacter);
            if (check > 0) {
                std::cout << "And the winner is " << playerCharacter << std::endl;
                win = 1;
                printLetterBoard(widthOfBoard);
                printBoard(widthOfBoard, heightOfBoard);
            }
            if (checkAllBoard() == 1) {
                win = 1;
            }
            while (illegalMove != 0) {
                movement = getMove(fileName);
                movePosition = getPosition(movement);
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                check = checkAll(playerCharacter);
                if (check > 0) {
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
    int columnPosition = position %  widthOfBoard;
    auto rowPosition = static_cast<int> (position / widthOfBoard);
    int illegalMove = 0;

    if (gameCells[rowPosition][columnPosition].getStatusOfCell() == 'X' || gameCells[rowPosition][columnPosition].getStatusOfCell() == 'O') {
        while (rowPosition >= 0 && gameCells[rowPosition][columnPosition].getStatusOfCell() != '.') {
            rowPosition--;
            if (rowPosition < 0) {
                std::cerr << "Illegal move\nTry another one!" << std::endl;
                illegalMove = 1;
            }
        }
        if (illegalMove != 1) { gameCells[rowPosition][columnPosition].setStatusOfCell(character) ;
            gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
            gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));};
    }
    else if (gameCells[rowPosition][columnPosition].getStatusOfCell() == '.') {
        gameCells[rowPosition][columnPosition].setStatusOfCell(character);
        gameCells[rowPosition][columnPosition].setRowNumber(rowPosition);
        gameCells[rowPosition][columnPosition].setPositionOfCell(static_cast<char>(columnPosition + 'A'));
    }

    if (illegalMove != 1) {
        printLetterBoard(widthOfBoard);
        printBoard(widthOfBoard, heightOfBoard);
    }
    return illegalMove;
}

// Turn of player 1 -> calls makeMove
int ConnectFour::player1(string &fileName, char players) {
    //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
    std :: cout << "Turn of player X";
    std::cout << std::endl;
    return makeMove(fileName,'X',  players);
}

// Turn of player 2 -> calls makeMove
int ConnectFour::player2(string &fileName, char players) {
    //cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
    std :: cout << "Turn of player O";
    std::cout << std::endl;
    return makeMove(fileName, 'O', players);
}

// Who will play the game? -> user2user or user2computer
void ConnectFour::playGame() {
    string fileName;
    int win = 0;
    initializeBoard(); // Create board
    char players = playerTo(); // PVP or PVC
    if(players == 'P' || players == 'p'){
        while(win != 1 /*&& checkAllBoard(board, size) != 1*/){
            win = player1(fileName, players);
            cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
            if(win != 1){
                win =player2(fileName, players);
                cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
            }
        }
    }
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
// Checks the top and down.
int ConnectFour::verticalCheck(char character) {
    int characterCount = 0;
    int returnValue = 0;
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();

    for (int i = 0 ; i < widthOfBoard; ++i) {
        for (int j = 0; j < heightBoard; ++j) {
            if(gameCells[j][i].getStatusOfCell() == character){
                characterCount ++;
                if (characterCount == 4){
                    returnValue = 1;
                    for (int k = 0; k < characterCount; ++k) {
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

    for (int i = 0 ; i < heightBoard; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            if(gameCells[i][j].getStatusOfCell() == character){
                characterCount ++;
                if (characterCount == 4){
                    returnValue = 1;
                    for (int k = 0; k < characterCount; ++k) {
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
    if(count == heightBoard * widthOfBoard){
        full = 1;
        std :: cout << "Scoreless" << std :: endl;
        cout << "Living Cells: " << ConnectFour :: getLivingCells() << endl;
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
        movement = getMove(fileName);
        int movePosition = getPosition(movement);
        location = getLocation(movePosition);
        int illegalMove = updateBoard(playerCharacter, movePosition);
        if(illegalMove != 1){setLivingCells();}
        check = checkAll(playerCharacter);
        if (check > 0) {
            std::cout << "And the winner is " << playerCharacter << std::endl;
            win = 1;
            if(win == 1){
                printLetterBoard(widthOfBoard); // Print all
                printBoard(widthOfBoard, heightBoard);
            }

            while (illegalMove != 0) {
                movement = getMove(fileName);
                movePosition = getPosition(movement);
                location = getLocation(movePosition);
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                check = checkAll(playerCharacter);
                if (check > 0) {
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
            playerComputer(location);
            setLivingCells();
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
            win = newBoardGame(playerCharacter, fileName, players);
        }
        else{
            win = newBoardGameComputer('X', fileName, players);
        }

    }// if command is not SAVE or LOAD
    else {
        int movePosition = getPosition(movement);
        location = getLocation(movePosition);
        int illegalMove = updateBoard(playerCharacter, movePosition);
        if(illegalMove != 1){setLivingCells();}
        check = checkAll(playerCharacter);
        if (check > 0) {
            std::cout << "And the winner is " << playerCharacter << std::endl;
            win = 1;
            if(win == 1){
                printLetterBoard(widthOfBoard); // Print all
                printBoard(widthOfBoard, heightBoard);
            }

            while (illegalMove != 0) {
                movement = getMove(fileName);
                movePosition = getPosition(movement);
                location = getLocation(movePosition);
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
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
int ConnectFour::getLocation(int position) {
    int widthOfBoard = getWidth();
    int columnPosition = position % widthOfBoard;
    auto rowPosition = static_cast<int> (position / widthOfBoard);
    if (gameCells[rowPosition][columnPosition].getStatusOfCell() == 'X' || gameCells[rowPosition][columnPosition].getStatusOfCell() == 'O') {
        while (rowPosition >= 0 && gameCells[rowPosition][columnPosition].getStatusOfCell() != '.') {
            rowPosition--;
        }
    }
    return rowPosition * widthOfBoard + columnPosition;
}
// Decides behavior of computer
void ConnectFour::playerComputer(int move) {
    int widthOfBoard = getWidth();
    int heightBoard = getHeight();
    int row = move / widthOfBoard;
    int column = move % widthOfBoard;

    // if 3 X is vertical
    if(row + 2 < heightBoard && row - 1 >= 0 && gameCells[row + 1][column].getStatusOfCell() == 'X' && gameCells[row + 2][column].getStatusOfCell() == 'X'){
        if(gameCells[row - 1][column].getStatusOfCell() == '.'){
            gameCells[row - 1][column].setStatusOfCell('O');
            gameCells[row - 1][column].setRowNumber(row - 1);
            gameCells[row - 1][column].setPositionOfCell(static_cast<char>(column + 'A'));
            std :: cout << static_cast<char>(column + 'A') << std :: endl;
        }

    }// if 3 X is horizontal
    else if(column + 3 < widthOfBoard && gameCells[row][column + 1].getStatusOfCell() == 'X' && gameCells[row][column + 2].getStatusOfCell() == 'X' && gameCells[row][column + 3].getStatusOfCell() == '.' ){
        gameCells[row][column + 3].setStatusOfCell('O');
        gameCells[row][column + 3].setRowNumber(row);
        gameCells[row][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
        std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;

    }
    else if(column - 3 >= 0 && gameCells[row][column - 1].getStatusOfCell() == 'X' && gameCells[row][column - 2].getStatusOfCell() == 'X' && gameCells[row][column - 3].getStatusOfCell() == '.'){
        gameCells[row][column - 3].setStatusOfCell('O');
        gameCells[row][column - 3].setRowNumber(row);
        gameCells[row][column - 3].setPositionOfCell(static_cast<char>(column + 'A' - 3));
        std :: cout << static_cast<char>(column + 'A' - 3) << std :: endl;
    }
    else if(column + 3 < widthOfBoard && row + 3 < heightBoard && gameCells[row + 1][column + 1].getStatusOfCell() == 'X' && gameCells[row + 2][column + 2].getStatusOfCell() == 'X' && gameCells[row + 3][column + 3].getStatusOfCell() == '.'){
        gameCells[row + 3][column + 3].setStatusOfCell('O');
        gameCells[row + 3][column + 3].setRowNumber(row + 3);
        gameCells[row + 3][column + 3].setPositionOfCell(static_cast<char>(column + 'A' + 3));
        std :: cout << static_cast<char>(column + 'A' + 3) << std :: endl;
    }
    else if(column - 2 >= 0 && row + 2 < heightBoard && row -2 >= 0 && column + 1 < widthOfBoard &&
            gameCells[row + 1][column - 1].getStatusOfCell() == 'X' && gameCells[row + 2][column - 2].getStatusOfCell() == 'X' && gameCells[row - 1][column + 1].getStatusOfCell() != '.' && gameCells[row - 2][column + 1].getStatusOfCell() != '.'){
        gameCells[row - 1][column + 1].setStatusOfCell('O');
        gameCells[row - 1][column + 1].setRowNumber(row - 1);
        gameCells[row - 1][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else if(column -1 >=0  && row + 1 < heightBoard && gameCells[row][column - 1].getStatusOfCell() == '.' &&
            gameCells[row + 1][column -1].getStatusOfCell() != '.' && gameCells[row][column].getStatusOfCell() == 'X' && gameCells[row][column+1].getStatusOfCell() == 'X'){
        gameCells[row][column - 1].setStatusOfCell('O');
        gameCells[row][column - 1].setRowNumber(row);
        gameCells[row][column - 1].setPositionOfCell(static_cast<char>(column + 'A' - 1));
        std :: cout << static_cast<char>(column + 'A' - 1) << std :: endl;
    }
    else if(column + 1 < widthOfBoard && row == heightBoard - 1 && gameCells[row][column + 1].getStatusOfCell() == '.'){
        gameCells[row][column + 1].setStatusOfCell('O');
        gameCells[row][column + 1].setRowNumber(row);
        gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else if(column + 1 < widthOfBoard && row + 1 < heightBoard && gameCells[row][column + 1].getStatusOfCell() == '.' && gameCells[row + 1][column +1].getStatusOfCell() != '.'){
        gameCells[row][column + 1].setStatusOfCell('O');
        gameCells[row][column + 1].setRowNumber(row);
        gameCells[row][column + 1].setPositionOfCell(static_cast<char>(column + 'A' + 1));
        std :: cout << static_cast<char>(column + 'A' + 1) << std :: endl;
    }
    else{
        for (int i = heightBoard - 1 ; i >= 0; --i) {
            for (int j = widthOfBoard - 1; j >= 0 ; --j) {
                if(gameCells[i][j].getStatusOfCell() == '.'){
                    gameCells[i][j].setStatusOfCell('O');
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
            gameCells[i][j].setStatusOfCell(gameCells[i + 1][j].getStatusOfCell());
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
                win = newBoardGame(playerCharacter, fileName, players);
            }
            else{
                win = newBoardGameComputer('X', fileName, players);
            }
        }
        // Keep playing on
        if(checkAllBoard() != 1){
            int movePosition = getPosition(movement);
            int illegalMove = updateBoard(playerCharacter, movePosition);
            if(illegalMove != 1){setLivingCells();}
            cout << "Living Cells:" << getLivingCells() << endl;
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
                movement = getMove(fileName);
                movePosition = getPosition(movement);
                illegalMove = updateBoard(playerCharacter, movePosition);
                if(illegalMove != 1){setLivingCells();}
                cout << "Living Cells:" << getLivingCells() << endl;
                check = checkAll(playerCharacter);
                if (check > 0) {
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
        cout << "Living Cells:" << getLivingCells() << endl;
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
            cout << "Living Cells:" << getLivingCells() << endl;
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

void ConnectFour::multiGameInitializer(){

    vector<ConnectFour> tempVector;
    for (int i = 0; i < 5 ; ++i) {
        ConnectFour temp(4);
        tempVector.push_back(temp);
        tempVector[i].setPlayers(playerTo());
    }
    setObjectVector(tempVector);

}

void ConnectFour::play() {

    string file;
    int objectNumber = chooseObject();
    cout << objectVector[objectNumber - 1 ].getPlayers()<< endl;
    int check = 0;
    for (int i = 0; i < 5 ; ++i) {
        check += objectVector[i].getWin();
    }
    while((objectNumber < 0 || objectNumber > 5) ){
        cout<< "Enter 1-5" << endl;
        objectNumber = chooseObject();
    }
    while(objectNumber > 0 && objectNumber <= 5 && check != 5){
        while(objectNumber < 0 || objectNumber > 5){
            cout<< "Enter 1-5" << endl;
            objectNumber = chooseObject();
        }
        if(objectVector[objectNumber - 1 ].getPlayers() == 'P' || objectVector[objectNumber - 1 ].getPlayers() == 'p'){
            if(objectVector[objectNumber - 1].getWin() != 1){
                objectVector[objectNumber - 1].printLetterBoard((objectVector[objectNumber - 1].getWidth()));
                objectVector[objectNumber - 1].printBoard((objectVector[objectNumber - 1].getWidth()), (objectVector[objectNumber - 1].getHeight()));
                objectVector[objectNumber - 1].setWin(objectVector[objectNumber - 1].player1(file,players ));
                if(objectVector[objectNumber - 1].getWin() != 1){
                    objectVector[objectNumber - 1].setWin(objectVector[objectNumber - 1].player2(file,players ));
                }
                cout << "Living Cells:" << getLivingCells() << endl;
                objectNumber = chooseObject();
                while(objectNumber < 0 || objectNumber > 5){
                    cout<< "Enter 1-5" << endl;
                    objectNumber = chooseObject();
                }
            }
            else{
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
                objectVector[objectNumber - 1].play(objectNumber);
                cout << "Living Cells:" << getLivingCells() << endl;
                objectNumber = chooseObject();
                while(objectNumber < 0 || objectNumber > 5){
                    cout<< "Enter 1-5" << endl;
                    objectNumber = chooseObject();
                }
            }
            else{
                cout << "This game is over." << endl;
                objectNumber = chooseObject();
                while(objectNumber < 0 || objectNumber > 5){
                    cout<< "Enter 1-5" << endl;
                    objectNumber = chooseObject();
                }
            }

        }check = 0;
        for (int i = 0; i < 5 ; ++i) {
            check += objectVector[i].getWin();
            if(check == 5)
            	cout << "All games are over" << endl;
        }
    }
}
int ConnectFour::play(int objectNumber) {
    string fileName;
    int win = 0;
        printLetterBoard(getWidth());
        printBoard(getWidth(), getHeight());
        setWin(computer('X', fileName, players));
}

ConnectFour::ConnectFour() {
    height = 4;
    width = 4;
    players = 'p';
    win = 0;
}

ConnectFour::ConnectFour(int widthOfBoard, int heightOfBoard, char player) {
    width = widthOfBoard;
    height = heightOfBoard;
    players = player;
}


ConnectFour::Cell::Cell() {
    positionOfCell = 0;
    rowNumber = 0;
    statusOfCell = '.';

}
ConnectFour::ConnectFour(int widthBoard) {
    heightFromUser();
    widthFromUser();
    int widthOfBoard = getWidth();
    int heightOfBoard = getHeight();
    vector<Cell> tempVec;
    Cell temp;

    for(int i=0; i<widthOfBoard; i++){
        tempVec.push_back(temp);
    }
    for (int j = 0; j < heightOfBoard ; ++j) {
        gameCells.push_back(tempVec);
    }

    for (int i = 0; i < heightOfBoard; ++i) {
        for (int j = 0; j < widthOfBoard; ++j) {
            gameCells[i][j].setStatusOfCell('.');
        }
    }
}

char ConnectFour::SingleOrMultipleGame()const {
    cout << "Please enter the game mode\nSingle: S or Multiple: M" << endl;
    char mode;
    cin >> mode;
    return mode;
}

int ConnectFour::chooseObject() {
    cout << "Please choose an object" << endl;
    int objectNumber;
    cin >> objectNumber;
    cin.ignore();
    return objectNumber;
}


bool ConnectFour::compare(ConnectFour anObject) {

    int thisObjectCells = getLivingCells();
    int anObjectCells = anObject.getLivingCells();
    if( thisObjectCells >= anObjectCells)
        return true;
    else return false;
}


