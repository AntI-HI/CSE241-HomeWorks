#include "HexVector.h"

using namespace std;

namespace {
    // Made a global variable for time variable and random engine because we don't want to send or change the random engine.
    // Also this is the case most of the times with random engines and time variables.
    time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
    default_random_engine rng(now);
}

namespace KAYA_GTU {
/*
    No Parameter Constructor
*/
HexVector::HexVector() : AbstractHex(){

    playGame();

}

/*
    Initializes the game informations.
    @Param1 hexSize: Size of the game table
    @Param2 opponent: Who do you play against. 0 for AI 1 for User.
*/
HexVector::HexVector (const int hexSize, const int opponent) : AbstractHex(hexSize, opponent){
    
    createCells();
    
}

/*
    This constructor takes a fileName and initializes the object by loading that file.
*/
HexVector::HexVector(const string& fileName) : AbstractHex(0, 0) {

    ifstream infile; 
    infile.open(fileName);

    readFromFile(infile);

    infile.close();
    
}


/*
    It starts the game. Takes the game informations such as size of the board
    and opponent from user.
*/
void HexVector::playGame() {

    cout << "Welcome to the Game HEX." << endl;
    cout << "Please Enter the Size of the Board (Minimum 5, Maximum 26): ";
    
    do {
        while (!(cin >> size)){
            cout << "Enter in appropriate format (Integer): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (size < 5 || size > 26)  
            cout << "Please enter the size in between limits: ";
    }while(size < 5 || size > 26); 

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

    posList.setSize(0);
    posList.setRightColDifference(size);
    posList.setLeftColDifference(size);

    createCells();

    print(cout);

}

/*
    Makes the move for AI.
*/
void HexVector::play() {
   
    FinalMove fm = ParseMove_AI();
    hexCells[fm.getRow()][fm.getCol()].setVal(X);
    lastmove.setRowColVal(fm.getRow(), fm.getCol(), X);
    numOfMoves++;
    opponentMarked++;

}

/*
    Makes the move for player 1 or player2
*/
void HexVector::play(int row, int col) {

    if (turn == 0) {                    // Player 1
        hexCells[row][col].setVal(O);
        lastmove.setRowColVal(row, col, O);
        userMarked++;
    }
    else {                               // Player 2
        hexCells[row][col].setVal(X);
        lastmove.setRowColVal(row, col, X);
        opponentMarked++;
    }
    numOfMoves++;
}

/*
    Draws the Table to the Console.
*/
void HexVector::print(ostream& stream) const { 

    stream << " ";
    for( char l = 'a'; l < 'a' + size; ++l) 
        stream << l << " ";   
    stream << endl;

    for (int i = 0; i < size; ++i) {       
        stream << 1 + i;
        if(i < 9)   
            for (int k = 0; k < i; ++k)     
                stream <<  " ";
        else 
            for (int k = 1; k < i; ++k)
                stream << " ";      
            
        for (int j = 0; j < size; ++j) 
            switch(hexCells[i][j].getVal()){
                case 0:
                    stream << ". ";
                    break;
                case 1:
                    if (winSituation == 1)
                        stream << "X ";
                    else    
                        stream << "x ";
                    break;
                case 2:
                    if (winSituation == 2)
                        stream << "O ";
                    else    
                        stream << "o ";
                    break;
            }
        stream << endl;
    }
}

void HexVector::createCells() {

    hexCells.clear();   // First clear the vector so we can establish it from scratch.

    for (int i=0; i < size; ++i) {
        hexCells.push_back(vector<Cell>());
        for (int j=0; j < size; ++j) {
            hexCells[i].push_back(Cell(i, j));
        }
    }
}

void HexVector::reset() {

    for (int i=0; i < size; ++i)
        for (int j=0; j < size; ++j)
            hexCells[i][j].setVal(DOT);
    
    
}

/*
    Function gets the move for AI. It calls SimulateMoves() function to get the move.
*/
FinalMove HexVector::ParseMove_AI() {
    
    int row;
    int col;
    uniform_int_distribution<int> dist(0, size-1);

    if(posList.getSize() == 0){
        do {
            row = dist(rng);
            col = dist(rng);
        }while (hexCells[row][col].getVal() != DOT);

        posList.SetPosition(row, col);
        posList.setLeftColDifference(col);
        posList.setRightColDifference(col);
        FinalMove finalmove(row, col);
        return finalmove;
    }
    else {
        auto finalmove = SimulateMoves();
        return finalmove;
    }
    
}

/*
    This function gets the move and parses the move for player1 and player2.
*/
void HexVector::ParseMove() {

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    bool alpha = true;
    int row, col;
    bool breakLoop = false;
    string move;
    bool isCommand; //This becames true if input entered is LOAD or SAVE or MENU Command.
    int currentTurn = turn;
    do {
        alpha = true;
        isCommand = false;
        move = GetMove(isCommand);

        if (isCommand) {
            ParseCommand(move);
            if (currentTurn != turn || end) 
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
    Gets the move from user. If it is a move than isCommand flag becomes true. 
    Then it returns the move to the ParseMove() function.

    @Param1 isCommand: If we type a command to the console than this is true.

    return const string.
*/
const string HexVector::GetMove(bool& isCommand) const {

    string move;
    bool breakloop = false;
    cin >> ws;
    do {

        getline(cin, move);
         
        if (move.length() > 3 && move.find(" ") > 0) {
            if (move.substr(0, move.find(" ")) == "LOAD" ||
                 move.substr(0, move.find(" ")) == "SAVE" ||
                 move.substr(0, move.find(" ")) == "LASTMOVE" ||
                 move.substr(0, move.find(" ")) == "RESET") {

                isCommand = true;
                return move;
            }
            else if (move.length() < 2 || move.length() > 3) {
                cerr << "Invalid Move! Make Your Move Again: "; 
            }
        }
        else if (move.length() < 2 || move.length() > 3) {
            cerr << "Invalid Move! Make Your Move Again: "; 
        }
        else if (move.length() == 2 && move.at(0) >= 'a' && move.at(0) < 'a' + size && 
                move.at(1) >= '1' && move.at(1) < '1' + size)
                
            breakloop = true;
        
        else if (size > 9 && move.length() == 3 && move.at(0) >= 'a' && move.at(0) < 'a' + size && move.at(1) >= '1' &&
                 move.at(1) < '1'+size && move.at(2) >= '0' && move.at(2) < '0' + size)

            breakloop = true;
        
        else cerr << "Invalid Move! Make Your Move Again: ";
           
    } while (!breakloop);


    return move; 
}

void HexVector::ParseCommand(const std::string& command) {

    if (command.substr(0, command.find(" ")) == "SAVE") {
        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));

        ofstream outfile;
        outfile.open(parsedCommand);

        writeToFile(outfile);

        outfile.close();
        cout << "Game Saved Succesfully!" << endl;
    }
    else if(command.substr(0, command.find(" ")) == "LOAD") {
        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));

        ifstream infile; 
        infile.open(parsedCommand); 

        readFromFile(infile);

        infile.close();
        cout << "Game Loaded Succesfully!" << endl;
        print(cout);
    }
    else if(command.substr(0, command.find(" ")) == "LASTMOVE") { 
        cout << "Last Move You Made is: " << lastMove().getVal() << endl;
    }
    else if(command.substr(0, command.find(" ")) == "RESET") { 
        cout << "Game is resetted... " << endl;
        reset();
        print(cout);
    }

}

/*
    Saves the current game to a file.
    @Param1 fileName: file to be saved.
*/
void HexVector::writeToFile(ofstream& outfile) const{

    outfile << size << endl;
    outfile << turn << endl;
    outfile << opponent << endl;
    outfile << numOfMoves << endl;
    outfile << userMarked << endl;
    outfile << opponentMarked << endl;
    outfile << end << endl;
    outfile << lastmove.getRow() << endl;
    outfile << lastmove.getCol() << endl;
    outfile << lastmove.getVal() << endl;

    for (int i=0; i < size; ++i)
        for (int j=0; j < size; ++j)
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
	
}

/*
    Loads the game inside the file specified to a HEX object.
    @Param1 fileName: file name to be loaded.
*/
void HexVector::readFromFile(ifstream& infile) {

    int row, col, val;

    infile >> size;
    infile >> turn;
    infile >> opponent;
    infile >> numOfMoves;
    infile >> userMarked;
    infile >> opponentMarked;
    infile >> end;
    infile >> row;
    infile >> col;
    infile >> val;

    lastmove.setRowColVal(row, col, val);

    string dummy;
    infile >> dummy;

    createCells();
    for (int i=0; i < size; ++i)
        for (int j=0; j < size; ++j)
            hexCells[i][j].setVal(dummy.at(j + i * size) - '0');

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
    
}


/*
    Simulates the move that can be played by AI. Than chooses an appropriate move for AI.
    Returns that move to the ParseMove_AI() function.

    return FinalMove;
*/
FinalMove HexVector::SimulateMoves(){

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
        uniform_int_distribution<int> dist(0, size-1);
        
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
bool HexVector::IsValidAI(int row, int col) const {
    if (row >= 0 && row < size && col >= 0 && col < size && hexCells[row][col].getVal() == DOT)
        return true;
    
    return false;
}

/*
    Resets the Visiteds nodes everytime we finish a traversal.
*/
void HexVector::ResetVisiteds() {
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            hexCells[i][j].setVisited(false);    
}

/*
    Performs a recursion searching to analyze the game for player1 if it ends.
    @Param1 row: Row
    @Param2 col: Column
    @Param3 found: true if it reaches the destination. Otherwise false.

    return bool
*/
bool HexVector::CheckP1(int row, int col, bool found) {
    
    if (!IsValidP1(row, col))
        return false;
    
    if (row == size-1 && hexCells[row][col].getVal() == O) {
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
bool HexVector::CheckP2(int row, int col, bool found) {

    if (!IsValidP2(row, col))
        return false;
    
    if (col == size-1 && hexCells[row][col].getVal() == X) {
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
bool HexVector::IsValidP1(const int& row, const int& col) {

    if (row >= 0 && row < size && col >= 0 && col < size && 
        hexCells[row][col].getVal() == O && !hexCells[row][col].getVisited()){

        hexCells[row][col].setVisited(true);
        return true;
    }
    else if (row >= 0 && row < size && col >= 0 &&
            col < size && hexCells[row][col].getVal() == DOT) {

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
bool HexVector::IsValidP2(const int& row, const int& col) {

    if (row >= 0 && row < size && col >= 0 && col < size && 
        hexCells[row][col].getVal() == X && !hexCells[row][col].getVisited()){

        hexCells[row][col].setVisited(true);
        return true;
    }
    else if (row >= 0 && row < size && col >= 0 &&
            col < size && hexCells[row][col].getVal() == DOT) {

        hexCells[row][col].setVisited(true);
    }
    return false;
}

/*
    Checks if one of the players and the game.
    If the game ends it returns true, otherwise returns false.

    @return bool
*/
bool HexVector::isEnd() {

    bool finished = false;
    
    int col = 0;
    int row = 0;
    
    if (turn == 0) {    // Which means check if player1 finished the game         
        while (col < size && !finished) {
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
            print(cout);
            end = true;
        }
        turn = 1;
    }
    else if (turn == 1) {   // Which means check if player2 or AI finished the game  
        
        while (row < size && !finished) {
            
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
            print(cout);
            end = true;
        }
        turn = 0;
    }
    
    return finished;

}


/*
    This function is Wrapper function for ParseMove function for P1 and P2 (not AI).
    return void
*/
void HexVector::MakeMove() {

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
void HexVector::MakeMove_AI() {

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
void HexVector::Update() {

    // We don't have to ask the player which side he/she wants to choose. It will always be Red side (Trying to connect bottom and up.)
    // Similarly AI or Player 2 will always trying to connect the left and right side (So They are in Blue side.)
    // Player 1 always start first. (I may implement the selection functionality if I want in future.)

    

    if (opponent == 1) {
        cout << "UPDATE" << endl;
        MakeMove();
        print(cout);
        if(isEnd() || end) {
            end = true;
        }
    }
    else if (opponent == 0){
        MakeMove_AI();
        print(cout);
        if(isEnd() || end) {
            end = true;
        }
    }
}

int HexVector::operator()(int row, int col) const throw (MyException) {

    if (row >= size || col >= size){
        throw MyException();
    }
    return hexCells[row][col].getVal();
}

bool HexVector::operator==(const AbstractHex& AH) {

    for (int i=0; i < size; i++){
        for (int j=0; j < size; j++) {
            if (this->operator()(i,j) != AH.operator()(i,j)) {
                return false;
            }
        }
    }
    return true;
}

}


