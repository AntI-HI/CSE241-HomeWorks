#include "hex.h"
using namespace std;

// Made a global variable for time variable and random engine because we don't want to send or change the random engine.
// Also this is the case most of the times with random engines and time variables.
time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
default_random_engine rng(now);

int HEX::numberOfMarked = 0;
int HEX::numberOfGames = 0;
vector<HEX*> HEX::games;
bool HEX::terminate = false;
int HEX::currentGame;
int HEX::numberOfEndGame = 0;

// Static Functions.

int HEX::getNumberOfMarked() { return numberOfMarked; }

void HEX::setNumberOfMarked(int i) { numberOfMarked += i; }

int HEX::getNumberOfGames() { return numberOfGames; }

HEX& HEX::getGame(int i) { return *games[i]; }

bool HEX::getTerminate() { return terminate; }

int HEX::getCurrentGame() { return currentGame; }

int HEX::getNumberOfEndGame() { return numberOfEndGame; }
/*
    Initializes the game informations.
    @Param1 hexSize: Size of the game table
    @Param2 opponent: Who do you play against. 0 for AI 1 for User.
*/
HEX::HEX (const int hexSize, const int opponent) : hexSize(hexSize), opponent(opponent),
         turn(0), winSituation(0), userMarked(0), opponentMarked(0), end(false), posList(hexSize){
    
    createCells();
    numberOfGames++;
    games.push_back(this);
    currentGame = numberOfGames;
}

/*
    Default Constructor
*/
HEX::HEX() : hexSize(0), opponent(0), turn(0), winSituation(0),
             userMarked(0), opponentMarked(0), end(false) {
    
    playGame();
    numberOfGames++;
    games.push_back(this);
    currentGame = numberOfGames;
}

/*
    This constructor takes a fileName and initializes the object by loading that file.
*/
HEX::HEX(const string& fileName) : hexSize(0), opponent(0), turn(0), winSituation(0),
                                    userMarked(0), opponentMarked(0), end(false) {

    LoadGame(fileName);
    numberOfGames++;
    games.push_back(this);
    currentGame = numberOfGames;
}

void HEX::setSize(const int newSize) {
    if(newSize < 5){
        cerr << "Sorry. You Entered the wrong value!! Terminating";
        exit(EXIT_FAILURE);
    }    
    hexSize = newSize;
}

void HEX::setOpponent(const int newOpponent) {
    if (newOpponent != 0 || newOpponent != 1) {
        cerr << "You can only type 0 or 1!! Terminating";
        exit(EXIT_FAILURE);
    }
    opponent = newOpponent;
}

void HEX::setTurn(const int newTurn) {
    if (newTurn != 0 || newTurn != 1) {
        cerr << "You can only type 0 or 1!! Terminating";
        exit(EXIT_FAILURE);
    }
    turn = newTurn;
}

void HEX::setWinSituation(int newVal) { winSituation = newVal; }

/*
    Compares to Hex games. If current game has more User Marked cells then returns true,
    otherwise returns false.
    @Param1 other: HEX object to be compared with current object.

    return bool
*/
bool HEX::compareGames(const HEX& other) const { return userMarked > other.userMarked ? true : false; }
/*
    Assigns the location informations to corresponding variables to keep track of the progress.
*/
void HEX::AI_POS_List::SetPosition(int row, int col) {
    
    AI_ROW[size] = row;
    AI_COL[size] = col;
    size++;
}

/*
    Saves the current game to a file.
    @Param1 fileName: file to be saved.
*/
void HEX::SaveGame(const string& fileName) const{

    ofstream outfile;
        
    outfile.open(fileName);

    outfile << hexSize << endl;
    outfile << turn << endl;
    outfile << opponent << endl;
    outfile << userMarked << endl;
    outfile << opponentMarked << endl;
    outfile << end << endl;

    for (int i=0; i < hexSize; ++i)
        for (int j=0; j < hexSize; ++j)
            outfile << hexCells[i][j].getVal();
    outfile << endl;
    
    if (opponent == 0){
        outfile << posList.getSize() << endl;
        outfile << posList.getRightColDifference() << endl;
        outfile << posList.getLeftColDifference() << endl;

        for (int i=0; i < posList.getSize(); ++i){
            outfile << posList.getRow(i) << " ";
            if (i == posList.getSize()-1)
                outfile << posList.getRow(i);
            else
                outfile << posList.getRow(i) << " ";
        }   
    }
	outfile.close();
    cout << "Game Saved Succesfully!" << endl;
}

/*
    Loads the game inside the file specified to a HEX object.
    @Param1 fileName: file name to be loaded.
*/
void HEX::LoadGame(const string& fileName) {

    ifstream infile; 
    
    infile.open(fileName); 

    setNumberOfMarked(-(userMarked + opponentMarked));

    infile >> hexSize;
    infile >> turn;
    infile >> opponent;
    infile >> userMarked;
    infile >> opponentMarked;
    infile >> end;

    string dummy;
    infile >> dummy;

    createCells();
    for (int i=0; i < hexSize; ++i)
        for (int j=0; j < hexSize; ++j)
            hexCells[i][j].setVal(dummy.at(j + i * hexSize) - '0');

    if (opponent == 0) {
        int temp;

        infile >> temp;
        posList.setSize(temp);
        infile >> temp;
        posList.setRightColDifference(temp);
        infile >> temp;
        posList.setLeftColDifference(temp);
        
        for (int i=0; i<posList.getSize(); ++i){
            infile >> temp;
            posList.setRow(i, temp);
            infile >> temp;
            posList.setCol(i, temp);
        }
    }

    infile.close();
    setNumberOfMarked(userMarked + opponentMarked);
    cout << "Game Loaded Succesfully!" << endl;
    DrawTable();
}

/* 
    Prints the mainMenu.
*/
void HEX::mainMenu() {

    cout << "1-) To Compare another game, Type \"Compare -gameID-\": " << endl;
    cout << "2-) To Save the game, Type \"Save -filename-\": " << endl;
    cout << "3-) To Load the game, Type \"Load -filename-\": " << endl;
    cout << "4-) To Get the number of Active Games, Type \"numberOfGames\": " << endl;
    cout << "5-) To Get the number of Marked Cells in all games, Type \"numberOfMarked\": " << endl;
    cout << "6-) To pass another game, Type \"getGame -gameID-\": " << endl;
    cout << "7-) To end the game, Type \"quit\"" << endl; 
    cout << "8-) To terminate the program. Type \"terminate\" " << endl;

    GetCommand();
}

/*
    Makes the move for AI.
*/
void HEX::play() {
   
    ParseMove_AI();

    setNumberOfMarked();
    setOpponentMarked();
}

/*
    Makes the move for player 1 or player2
*/
void HEX::play(int row, int col) {

    if (turn == 0)                      // Player 1
        hexCells[row][col].setVal(O);
    else                                // Player 2
        hexCells[row][col].setVal(X);

    setNumberOfMarked(); // Everytime we make a move increment the number of marked to 1.
    setUserMarked();    // Also set the User Marked for Comparing other games.
}
/*
    It starts the game. Takes the game informations such as size of the board
    and opponent from user.
*/
void HEX::playGame() {

    cout << "Welcome to the Game HEX." << endl;
    cout << "Please Enter the Size of the Board (Minimum 5, Maximum 26): ";
    
    do {
        while (!(cin >> hexSize)){
            cout << "Enter in appropriate format (Integer): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (hexSize < 5 || hexSize > 26)  
            cout << "Please enter the size in between limits: ";
    }while(hexSize < 5 || hexSize > 26); 

    cout << "Who Do You Play Against (Type 0 for AI, Type 1 for Player): ";
    do {
        while (!(cin >> opponent)){
            cout << "Enter in appropriate format (Integer): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (!(opponent == 0 || opponent == 1))  
            cout << "Please enter 0 or 1: ";
    }while(!(opponent == 0 || opponent == 1));

    cout << "To Reach the Main Menu, type \"MENU\" on console or simply make your move." << endl;

    posList.setSize(0);
    posList.setRightColDifference(hexSize);
    posList.setLeftColDifference(hexSize);

    createCells();

    DrawTable();

    //Update(Hex);

}

/*
    creates the game cells.
*/
void HEX::createCells() {

    hexCells.clear();   // First clear the vector so we can establish it from scratch.

    for (int i=0; i < hexSize; ++i) {
        hexCells.push_back(vector<Cell>());
        for (int j=0; j < hexSize; ++j) {
            hexCells[i].push_back(Cell(i, j));
        }
    }
}

/*
    Checks if one of the players and the game.
    If the game ends it returns true, otherwise returns false.

    @return bool
*/
bool HEX::IsGameOver() {

    bool finished = false;
    
    int col = 0;
    int row = 0;
    
    if (turn == 0) {    // Which means check if player1 finished the game         
        while (col < hexSize && !finished) {
            if(hexCells[0][col].getVal() == O)
                finished = CheckP1(0, col);
            
            if (finished) {
                ResetVisiteds();
                break;
            }
            else col++;
            
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds();
        }

        if(finished) {
            cout << "Player1 WIN!" << endl;
            winSituation = 2;
            DrawTable();
            end = true;
        }
        turn = 1;
    }
    else if (turn == 1) {   // Which means check if player2 or AI finished the game  
        
        while (row < hexSize && !finished) {
            
            if(hexCells[row][col].getVal() == X)    
                finished = CheckP2(row, 0);
            
            if (finished) {
                
                ResetVisiteds();
                break;
            }
            else row++;
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds();
        }

        if(finished) {
            cout << "Player2 WIN!" << endl;
            winSituation = 1;
            DrawTable();
            end = true;
        }
        turn = 0;
    }
    
    return finished;

}

/*
    Draws the Table to the Console.
*/
void HEX::DrawTable() const { 

    cout << " ";
    for( char l = 'a'; l < 'a' + hexSize; ++l) 
        cout << l << " ";   
    cout << endl;

    for (int i = 0; i < hexSize; ++i) {       
        cout << 1 + i;
        if(i < 9)   
            for (int k = 0; k < i; ++k)     
                cout <<  " ";
        else 
            for (int k = 1; k < i; ++k)
                cout << " ";      
            
        for (int j = 0; j < hexSize; ++j) 
            switch(hexCells[i][j].getVal()){
                case 0:
                    cout << ". ";
                    break;
                case 1:
                    if (winSituation == 1)
                        cout << "X ";
                    else    
                        cout << "x ";
                    break;
                case 2:
                    if (winSituation == 2)
                        cout << "O ";
                    else    
                        cout << "o ";
                    break;
            }
        cout << endl;
    }
}

/*
    Function gets the move for AI. It calls SimulateMoves() function to get the move.
*/
void HEX::ParseMove_AI() {
    
    int row;
    int col;
    uniform_int_distribution<int> dist(0, hexSize-1);

    if(posList.getSize() == 0){
        do {
            row = dist(rng);
            col = dist(rng);
        }while (hexCells[row][col].getVal() != DOT);

        posList.SetPosition(row, col);
        posList.setLeftColDifference(col);
        posList.setRightColDifference(col);
        hexCells[row][col].setVal(X);
    }
    else {
        auto finalMove = SimulateMoves();
        hexCells[finalMove.getRow()][finalMove.getCol()].setVal(X);
    }
}

/*
    This function gets the move and parses the move for player1 and player2.
*/
void HEX::ParseMove() {

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    bool alpha = true;
    int row, col;
    bool breakLoop = false;
    string move;
    bool isCommand; //This becames true if input entered is LOAD or SAVE or MENU Command.
    int currentTurn = turn;
    int currGame = currentGame;
    do {
        alpha = true;
        isCommand = false;
        move = GetMove(isCommand);

        if (isCommand) {
            ParseCommand(move);
            if (currentTurn != turn || end || currGame != currentGame || terminate) 
                return;
            if (turn == 0)  // Player 1
                cout << "Player 1! Make Your Move: ";

            else if (turn == 1)  // Player 2
                cout << "Player 2! Make Your Move: ";
        }
        else {
            if(move.length() == 2) 
                for (char c : move) 
                    if (alpha){          
                        col = alphabet.find(c);
                        alpha = false;
                    }
                    else 
                        row = atoi(&c);         
            else {
                row = atoi(&move.at(1));
                col = alphabet.find(move.at(0));          
            }
            if (turn == 0 && hexCells[row-1][col].getVal() == DOT){
                play(row-1, col);
                breakLoop = true;
            }
            else if (turn == 1 && hexCells[row-1][col].getVal() == DOT) {
                play(row-1, col);
                breakLoop = true;
            }
            else { cout << "Make a valid Move: "; }
        }
    }while(!breakLoop);
}

/*
    If user Enters a Command on console input, Then this function redirects the 
    particular commands to fulfill that command.

    @Param1 command: Command to be parsed.
*/
void HEX::ParseCommand(const std::string& command) {

    if (command.substr(0, command.find(" ")) == "SAVE") {
        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));
        SaveGame(parsedCommand);
    }
    else if(command.substr(0, command.find(" ")) == "LOAD") {
        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));
        LoadGame(parsedCommand);
    }
    else if(command.substr(0, command.find(" ")) == "MENU") {
        mainMenu();
    }
}

/*
    Fulfills the Commands that are typed from user in Main Menu. 
*/
void HEX::GetCommand() {

    string move;
    int temp;
    bool breakloop = false;
    cin >> ws;
    do {
        getline(cin, move);
         
        if (move.substr(0, move.find(" ")) == "Compare") {
            if (move.substr(move.find(" ")+1, move.find('\n')) != "") {
                temp = stoi(move.substr(move.find(" ")+1, move.find('\n')));
                if (temp <= numberOfGames && temp > 0){
                    cout << compareGames(*games.at(temp-1)) << endl;
                    breakloop = true;
                }
                else { cerr << "Given value is too much. Terminating!!!"; exit(EXIT_FAILURE); }
            }
        }
        else if (move.substr(0, move.find(" ")) == "Save") {
            string ParseCommand = move.substr(move.find(" ")+1, move.find('\n'));
            SaveGame(ParseCommand);
            breakloop = true;
        }
        else if (move.substr(0, move.find(" ")) == "Load") {
            string ParseCommand = move.substr(move.find(" ")+1, move.find('\n'));
            LoadGame(ParseCommand);
            breakloop = true;
        }
        else if (move.substr(0, move.find(" ")) == "numberOfGames") {
            cout << getNumberOfGames() << endl;
            breakloop = true;
        }
        else if (move.substr(0, move.find(" ")) == "numberOfMarked") {
            cout << getNumberOfMarked() << endl;
            breakloop = true;
        }
        else if (move.substr(0, move.find(" ")) == "getGame"){
            if (move.substr(move.find(" ")+1, move.find('\n')) != "") {
                temp = stoi(move.substr(move.find(" ")+1, move.find('\n')));
                if (temp <= numberOfGames && temp > 0){
                    currentGame = temp;
                    cout << "You have passed to game number " << currentGame << endl;
                    breakloop = true;
                }
                else { cerr << "Given value is too much. Terminating!!!"; exit(EXIT_FAILURE); }
            }
        }
        else if (move.substr(0, move.find(" ")) == "quit") {
            end = true;
            breakloop = true;
        }
        else if (move.substr(0, move.find(" ")) == "terminate") {
            terminate = true;
            breakloop = true;
        }
    }while (!breakloop);
}

/*
    Gets the move from user. If it is a move than isCommand flag becomes true. 
    Then it returns the move to the ParseMove() function.

    @Param1 isCommand: If we type a command to the console than this is true.

    return const string.
*/
const string HEX::GetMove(bool& isCommand) const {

    string move;
    bool breakloop = false;
    cin >> ws;
    do {

        getline(cin, move);
         
        if (move.length() > 3 && move.find(" ") > 0) {
            if (move.substr(0, move.find(" ")) == "LOAD" || move.substr(0, move.find(" ")) == "SAVE"
                || move.substr(0, move.find(" ")) == "MENU") {

                isCommand = true;
                return move;
            }
        }
        else if (move.length() < 2 || move.length() > 3) {
            cerr << "Invalid Move! Make Your Move Again: "; 
        }
        else if (move.length() == 2 && move.at(0) >= 'a' && move.at(0) < 'a' + hexSize && 
                move.at(1) >= '1' && move.at(1) < '1' + hexSize)
                
            breakloop = true;
        
        else if (hexSize > 9 && move.length() == 3 && move.at(0) >= 'a' && move.at(0) < 'a' + hexSize && move.at(1) >= '1' &&
                 move.at(1) < '1'+hexSize && move.at(2) >= '0' && move.at(2) < '0' + hexSize)

            breakloop = true;
        
        else cerr << "Invalid Move! Make Your Move Again: ";
           
    } while (!breakloop);


    return move; 
}

/*
    Simulates the move that can be played by AI. Than chooses an appropriate move for AI.
    Returns that move to the ParseMove_AI() function.

    return FinalMove;
*/
FinalMove HEX::SimulateMoves(){

    int col;
    int row;
    int finalRowMove;
    int finalColMove;
    int leftCol = posList.getCol(posList.getSize() - 1);
    decltype(leftCol) rightCol = leftCol;
    bool foundMove = false;

    FinalMove finalMove;
    
    for(int i = posList.getSize()-1; i >= 0; --i) {
        row = posList.getRow(i);
        col = posList.getCol(i);
        
        if (IsValidAI(row, col-1)){
            leftCol = col-1;
            if (leftCol < posList.getLeftColDifference()) {
                posList.setLeftColDifference(leftCol);
                            
                finalRowMove = row;
                finalColMove = col-1;

                foundMove = true;

                break;
            }
        }
        if(IsValidAI(row+1, col-1)){

            leftCol = col-1;
            if (leftCol < posList.getLeftColDifference()) {
                posList.setLeftColDifference(leftCol);

                finalRowMove = row+1;
                finalColMove = col-1;

                foundMove = true;
                
                break;              
            }
        }
        if(IsValidAI(row, col+1)){
            rightCol = col+1;
            if (rightCol > posList.getRightColDifference()) {
                posList.setRightColDifference(rightCol);

                finalRowMove = row;
                finalColMove = col+1;
                foundMove = true;
    
                break;
            }
        }
        if(IsValidAI(row-1, col+1)){
            rightCol = col+1;
            if (rightCol > posList.getRightColDifference()) {
                posList.setRightColDifference(rightCol);

                finalRowMove = row-1;
                finalColMove = col+1;
                foundMove = true;

                break;
            }
        }
    }

    if (!foundMove){
        int row;
        int col;
        uniform_int_distribution<int> dist(0, hexSize-1);
        
        do {
            row = dist(rng);
            col = dist(rng);
        }while (hexCells[row][col].getVal() != DOT);

        posList.setLeftColDifference(col);
        posList.setRightColDifference(getSize() - col);
        
        finalRowMove = row;
        finalColMove = col;
    }
    
    posList.SetPosition(finalRowMove, finalColMove);
    
    finalMove.setRow(finalRowMove);
    finalMove.setCol(finalColMove);

    cout << "AI made move: " << char('a' + finalMove.getCol()) << " " << finalMove.getRow() + 1 << endl;

    return finalMove;
}

/*
    Called by SimulateMoves() function it specify whether the simulated move is appropriate.
    @Param1 row: Row
    @Param2 col: Column

    return bool
*/
bool HEX::IsValidAI(int row, int col) const {
    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && hexCells[row][col].getVal() == DOT)
        return true;
    
    return false;
}

/*
    Resets the Visiteds nodes everytime we finish a traversal.
*/
void HEX::ResetVisiteds() {
    for (int i = 0; i < hexSize; ++i)
        for (int j = 0; j < hexSize; ++j)
            hexCells[i][j].setVisited(false);    
}

/*
    Performs a recursion searching to analyze the game for player1 if it ends.
    @Param1 row: Row
    @Param2 col: Column
    @Param3 found: true if it reaches the destination. Otherwise false.

    return bool
*/
bool HEX::CheckP1(int row, int col, bool found) {
    
    if (!IsValidP1(row, col))
        return false;
    
    if (row == hexSize-1 && hexCells[row][col].getVal() == O) {
        hexCells[row][col].setVisited(true);
        return true;
    }
   
    found = CheckP1(row-1, col, found) ||
            CheckP1(row-1, col+1, found) ||
            CheckP1(row, col+1, found) ||
            CheckP1(row+1, col, found) ||
            CheckP1(row+1, col-1, found) ||
            CheckP1(row, col-1, found); 
    
    return found;
}

/*
    Performs a recursion searching to analyze the game for player2 if it ends.
    @Param1 row: Row
    @Param2 col: Column
    @Param3 found: true if it reaches the destination. Otherwise false.

    return bool
*/
bool HEX::CheckP2(int row, int col, bool found) {

    if (!IsValidP2(row, col))
        return false;
    
    if (col == hexSize-1 && hexCells[row][col].getVal() == X) {
        hexCells[row][col].setVisited(true);
        return true;
    }
   
    found = CheckP2(row-1, col, found) ||
            CheckP2(row-1, col+1, found) ||
            CheckP2(row, col+1, found) ||
            CheckP2(row+1, col, found) ||
            CheckP2(row+1, col-1, found) ||
            CheckP2(row, col-1, found); 
    
    return found;
}

/*
    Called by CheckP1() function it specify whether the player1 move is appropriate.
    @Param1 row: Row
    @Param2 col: Column

    return bool
*/
bool HEX::IsValidP1(const int& row, const int& col) {

    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && 
        hexCells[row][col].getVal() == O && !hexCells[row][col].getVisited()){

        hexCells[row][col].setVisited(true);
        return true;
    }
    else if (row >= 0 && row < hexSize && col >= 0 &&
            col < hexSize && hexCells[row][col].getVal() == DOT) {

        hexCells[row][col].setVisited(true);
    }
    return false;
}

/*
    Called by CheckP2() function it specify whether the player2 move is appropriate.
    @Param1 row: Row
    @Param2 col: Column

    return bool
*/
bool HEX::IsValidP2(const int& row, const int& col) {

    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && 
        hexCells[row][col].getVal() == X && !hexCells[row][col].getVisited()){

        hexCells[row][col].setVisited(true);
        return true;
    }
    else if (row >= 0 && row < hexSize && col >= 0 &&
            col < hexSize && hexCells[row][col].getVal() == DOT) {

        hexCells[row][col].setVisited(true);
    }
    return false;
}

/*
    This function is Wrapper function for ParseMove function for P1 and P2 (not AI).
    return void
*/
void HEX::MakeMove() {

    if (turn == 0)  // Player 1
        cout << "Player 1! Make Your Move: ";

    else if (turn == 1)  // Player 2
        cout << "Player 2! Make Your Move: ";
    
    ParseMove();

}

/*
    This function is Wrapper function for ParseMove function for P1 and AI.
    return void
*/
void HEX::MakeMove_AI() {

    if (turn == 0) { // Player 1
        cout << "Player 1! Make Your Move: ";
        ParseMove();
    }
    else if (turn == 1) { // AI
        cout << "AI! Make Your Move: " << endl;
        play();
    } 

}

/*
    Keeps playing every moves made by player until someone finishes the game.
*/
void HEX::Update() {

    // We don't have to ask the player which side he/she wants to choose. It will always be Red side (Trying to connect bottom and up.)
    // Similarly AI or Player 2 will always trying to connect the left and right side (So They are in Blue side.)
    // Player 1 always start first. (I may implement the selection functionality if I want in future.)

    if (end) {
        cout << "This game is already finished. We are directing you to Main Menu." << endl;
        mainMenu();
        return;
    }
    if (opponent == 1) {
        MakeMove();
        DrawTable();
        if(IsGameOver() || end) {
            numberOfEndGame++;
            cout << "Game " << currentGame << " is finished." << "Passing to the next game." << endl;
            do {
                if (!getGame(currentGame % numberOfGames).end) {
                    currentGame = currentGame % numberOfGames;
                    break;
                }
            }while (getNumberOfEndGame() < getNumberOfGames());
            cout << "Game number: " << ++currentGame << endl;
        }  
    }
    else if (opponent == 0){
        MakeMove_AI();
        DrawTable();
        if(IsGameOver() || end) {
            numberOfEndGame++;
            cout << "Game " << currentGame << " is finished." << "Passing to the next game." << endl;
            do {
                if (!getGame(currentGame % numberOfGames).end){
                    currentGame = currentGame % numberOfGames;
                    break;
                }
            }while (getNumberOfEndGame() < getNumberOfGames());
            cout << "Game number: " << ++currentGame << endl;
        }
    }
}