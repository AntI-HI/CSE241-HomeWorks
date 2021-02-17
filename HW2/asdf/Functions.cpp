#include "Functions.h"

using namespace std;

/*
    Sets the location value and its visited condition.
*/
HexTable::HexTable() : val(0), visited(false) {}
/*
    This constructor assigns the necessary informations in order for AI to keep track of its movement. Must be called properly.
*/
AI_POS_List::AI_POS_List(const int& hexSize) : size(0), rightColDifference(hexSize), leftColDifference(hexSize) {}

/*
    Assigns the location informations to corresponding variables to keep track of the progress.
*/
void AI_POS_List::SetPosition(int row, int col) {
    
    AI_ROW[size] = row;
    AI_COL[size] = col;
    size++;
}
/*
    Initializes the game informations.
*/
HEX::HEX (const int& hexSize) : hexSize(hexSize), opponent(0), turn(0), posList(hexSize){
    for (int i=0; i < 12; ++i) {
        for (int j=0; j < 12; ++j) {
            hexTable[i][j] = HexTable();
        }
    }
};

// Made a global variable for time variable and random engine because we don't want to send or change the random engine.
// Also this is the case most of the times with random engines and time variables.
time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
default_random_engine rng(now);

/*
    Starts the first frame and initialize the necessary informations.

    return void
*/
void Start() {

    int hexSize;                    // Indicates the table size for row and column.

    cout << "Welcome to the Game HEX." << endl;
    cout << "Please Enter the Size of the Board (Minimum 8, Maximum 12): ";
    
    do {
        while (!(cin >> hexSize)){
            cout << "Enter in appropriate format (Integer): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (hexSize < 8 || hexSize > 12)  
            cout << "Please enter the size in between limits: ";
    }while(hexSize < 8 || hexSize > 12);

    HEX Hex(hexSize);      // Statically allocated board.

    // Assign this array to 0 to represent the elements of the table is dot all around.
    // Whenever the AI chooses a location to put 'x' this corresponds 1, or player chooses a location to put 'o' this corresponds 2.
    for(int i = 0; i < hexSize; ++i) 
        for(int j = 0; j < hexSize; ++j) 
            Hex.hexTable[i][j].val = DOT;   

    cout << "Who Do You Play Against (Type 0 for AI, Type 1 for Player): ";
    do {
        while (!(cin >> Hex.opponent)){
            cout << "Enter in appropriate format (Integer): ";
            cin.clear();
            cin.ignore(100, '\n');
        }
        if (!(Hex.opponent == 0 || Hex.opponent == 1))  
            cout << "Please enter 0 or 1: ";
    }while(!(Hex.opponent == 0 || Hex.opponent == 1));

    DrawTable(Hex);
    Update(Hex);
}
/*
    DrawTable draws the last version of the table.
    @Param1 Hex: actual table
    @Param2 winSituation: If winSituation is 1 We will highlight 'X'. If 2 highlight 'O'.
                        For default it is 0 which represents nobody has won yet.
    returns void
*/
void DrawTable(HEX& Hex, int winSituation) { 

    cout << " ";
    for( char l = 'a'; l < 'a' + Hex.hexSize; ++l) 
        cout << l << " ";   
    cout << endl;

    for (int i = 0; i < Hex.hexSize; ++i) {       
        cout << 1 + i;
        if(i < 9)   
            for (int k = 0; k < i; ++k)     
                cout <<  " ";
        else 
            for (int k = 1; k < i; ++k)
                cout << " ";      
            
        for (int j = 0; j < Hex.hexSize; ++j) 
            switch(Hex.hexTable[i][j].val){
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
    Checks the Validity of the Move Played by Player 1. Return true if valid. Also we indicate the location we traveled to visited so we don't have to look again.
    @Param1 hexTable[][12]: To get the specific location's value
    @Param2 hexSize: table size used for checking the borders of the table. If exceeds the borders returns false.
    @Param3 row: row information 
    @Param4 col: column information

    returns bool
*/
bool IsValidP1(HEX& Hex, const int& row, const int& col) {

    if (row >= 0 && row < Hex.hexSize && col >= 0 && col < Hex.hexSize && Hex.hexTable[row][col].val == O && !Hex.hexTable[row][col].visited){
        Hex.hexTable[row][col].visited = true;
        return true;
    }
    else if (Hex.hexTable[row][col].val == DOT) {
        Hex.hexTable[row][col].visited = true;
    }
    return false;
}
/*
    Checks the Validity of the Move Played by Player 2. Return true if valid. Also we indicate the location we traveled to visited so we don't have to look again.
    @Param1 Hex: To get the specific location's value
    @Param2 row: row information 
    @Param3 col: column information

    returns bool
*/
bool IsValidP2(HEX& Hex, const int& row, const int& col) {

    if (row >= 0 && row < Hex.hexSize && col >= 0 && col < Hex.hexSize && Hex.hexTable[row][col].val == X && !Hex.hexTable[row][col].visited){
        Hex.hexTable[row][col].visited = true;
        return true;
    }
    else if (Hex.hexTable[row][col].val == DOT) {
        Hex.hexTable[row][col].visited = true;
    }
    return false;
}
/*
    Checks the Validity of the Simulated Move by AI. Return true if valid. 
    @Param1 Hex: To get the specific location's value
    @Param2 row: row information 
    @Param3 col: column information

    returns bool
*/
bool IsValidAI(HEX& Hex, const int row, const int col) {

    if (row >= 0 && row < Hex.hexSize && col >= 0 && col < Hex.hexSize && Hex.hexTable[row][col].val == DOT)
        return true;
    
    return false;
}

/*
    Traverses the board for Player 1. If Player 1 completed the game it returns true. Otherwise returns false.
    @Param1 Hex: Board which we will traverse.
    @Param2 row: Starting row point where we will traverse the tree.
    @Param3 col: Starting col point where we will traverse the tree.
    @Param4 found: Default Parameter which indicates if CheckP1 founds the end of the game.

    returns bool(found)
*/
bool CheckP1(HEX& Hex, int row, int col, bool found) {

    if (!IsValidP1(Hex, row, col))
        return false;
    
    if (row == Hex.hexSize-1 && Hex.hexTable[row][col].val == O) {
        Hex.hexTable[row][col].visited = true;
        return true;
    }
   
    found = CheckP1(Hex, row-1, col, found) ||
            CheckP1(Hex, row-1, col+1, found) ||
            CheckP1(Hex, row, col+1, found) ||
            CheckP1(Hex, row+1, col, found) ||
            CheckP1(Hex, row+1, col-1, found) ||
            CheckP1(Hex, row, col-1, found); 
    
    return found;
}

/*
    Traverses the board for Player 2. If Player 2 completed the game it returns true. Otherwise returns false.
    @Param1 Hex: Board which we will traverse.
    @Param2 row: Starting row point where we will traverse the tree.
    @Param3 col: Starting col point where we will traverse the tree.
    @Param4 found: Default Parameter which indicates if CheckP1 founds the end of the game.

    returns bool(found)
*/
bool CheckP2(HEX& Hex, int row, int col, bool found) {

    if (!IsValidP2(Hex, row, col))
            return false;
        
    if (col == Hex.hexSize-1 && Hex.hexTable[row][col].val == X) {
        Hex.hexTable[row][col].visited = true;
        return true;
    }

    found = CheckP2(Hex, row-1, col, found) ||
            CheckP2(Hex, row-1, col+1, found) ||
            CheckP2(Hex, row, col+1, found) ||
            CheckP2(Hex, row+1, col, found) ||
            CheckP2(Hex, row+1, col-1, found) ||
            CheckP2(Hex, row, col-1, found); 

    return found;
}
/*
    This function is a wrapper function for CheckP1 and CheckP2 functions. It finds a starting point for both sides. 
    If it founds then calls the CheckP1 or CheckP2 functions to start traversing. Returns true if game is over. Otherwise false.

    @Param1 Hex: Checking the entry point on the board.

    returns bool
*/
bool IsGameOver(HEX& Hex) {

    bool finished = false;

    int row = 0;
    int col = 0;

    if (Hex.turn == 0) {    // Which means check if player1 finished the game         
        while (col < Hex.hexSize && !finished) {
            if(Hex.hexTable[0][col].val == O) 
                finished = CheckP1(Hex, 0, col);

            if (finished) {
                ResetVisiteds(Hex);
                break;
            }
            else col++;
            
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds(Hex);
        }

        if(finished) {
            cout << "Player1 WIN!" << endl;
            DrawTable(Hex, 2);
        }

        Hex.turn = 1;
    }
    else if (Hex.turn == 1) {   // Which means check if player2 or AI finished the game      
        while (row < Hex.hexSize && !finished) {
            if(Hex.hexTable[row][col].val == X) {
                finished = CheckP2(Hex, row, col);
            }
            if (finished) {
                
                ResetVisiteds(Hex);
                break;
            }
            else row++;
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds(Hex);
        }

        if(finished) {
            cout << "Player2 WIN!" << endl;
            DrawTable(Hex, 1);
        }
        Hex.turn = 0;
    }
    return finished;
}
/*
    This function Resets the visited informations to 0 whenever the checking the board operation is complete.

    @Param1 Hex: Set every nodes visited info to zero

    returns void
*/
void ResetVisiteds(HEX& Hex) {
    for (int i = 0; i < Hex.hexSize; ++i)
        for (int j = 0; j < Hex.hexSize; ++j)
            Hex.hexTable[i][j].visited = false;    
}

/*
    If User Enters a SAVE or LOAD command, this function will evaluate those commands.

    @Param1 Hex: Saving or Loading the informations from this Object.
    @Param2 command: string command to be parsed.

    return void
*/
void ParseCommand(HEX& Hex, const string& command) {

    if (command.substr(0, command.find(" ")) == "SAVE") {
        ofstream outfile;
        
        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));
        outfile.open(parsedCommand);

        outfile << Hex.hexSize << endl;
        outfile << Hex.turn << endl;
        outfile << Hex.opponent << endl;

        for (int i=0; i < Hex.hexSize; ++i)
            for (int j=0; j < Hex.hexSize; ++j)
                outfile << Hex.hexTable[i][j].val;
        outfile << endl;
        
        if (Hex.opponent == 0){
            outfile << Hex.posList.size << endl;
            outfile << Hex.posList.rightColDifference << endl;
            outfile << Hex.posList.leftColDifference << endl;

            for (int i=0; i < Hex.posList.size; ++i){
                outfile << Hex.posList.AI_ROW[i] << " ";
                if (i == Hex.posList.size-1)
                    outfile << Hex.posList.AI_COL[i];
                else
                    outfile << Hex.posList.AI_COL[i] << " ";
            }   
        }
	outfile.close();
    }
    else if (command.substr(0, command.find(" ")) == "LOAD") {

        ifstream infile; 

        string parsedCommand = command.substr(command.find(" ")+1, command.find('\n'));
        infile.open(parsedCommand); 

        infile >> Hex.hexSize;
        infile >> Hex.turn;
        infile >> Hex.opponent;

        string dummy;
        infile >> dummy;

        for (int i=0; i < Hex.hexSize; ++i)
            for (int j=0; j < Hex.hexSize; ++j)
                Hex.hexTable[i][j].val = dummy.at(j + i*Hex.hexSize) - '0';
        if (Hex.opponent == 0) {
            infile >> Hex.posList.size;
            infile >> Hex.posList.rightColDifference;
            infile >> Hex.posList.leftColDifference;
            
            for (int i=0; i<Hex.posList.size; ++i){
                infile >> Hex.posList.AI_ROW[i];
                infile >> Hex.posList.AI_COL[i];
            }

        }
        DrawTable(Hex);
	infile.close();
    }
}
/*
    This function used for Getting the move from player1 or player2 (Not AI), After getting input, parsing it and checking the validity of the move.
    @Param1 Hex: Table which will be used. 

    returns void
*/
void ParseMove(HEX& Hex) {

    string alphabet = "abcdefghijkl";
    bool alpha = true;
    int row, col;
    bool breakLoop = false;
    string move;
    bool isCommand; //This becames true if input entered is LOAD or SAVE Command.
    int tempTurn = Hex.turn;
    do {
        alpha = true;
        isCommand = false;
        move = GetMove(Hex.hexSize, isCommand);

        if (isCommand) {
            ParseCommand(Hex, move);
            if (tempTurn != Hex.turn) 
                return;
            if (Hex.turn == 0)  // Player 1
                cout << "Player 1! Make Your Move: ";

            else if (Hex.turn == 1)  // Player 2
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
            if (Hex.turn == 0 && Hex.hexTable[row-1][col].val == DOT){
                Hex.hexTable[row-1][col].val = O;
                breakLoop = true;
            }
            else if (Hex.turn == 1 && Hex.hexTable[row-1][col].val == DOT) {
                Hex.hexTable[row-1][col].val = X;
                breakLoop = true;
            }
            else { cout << "Make a valid Move: "; }
        }
    }while(!breakLoop);
}

/*
    This function is called by ParseMove function to get the necessary move data from P1 or P2. Returns the move.
    @Param1 hexSize: Table size is used for checking the validity of the movement.
    @Param2 isCommand: If the input corresponds to a command then this flag is set to true.

    returns string
*/
string GetMove(const int& hexSize, bool& isCommand) {

    string move;
    bool breakloop = false;
    cin >> ws;
    do {

        getline(cin, move);
         
        if (move.length() > 3 && move.find(" ") > 0) {
            
            if (move.substr(0, move.find(" ")) == "LOAD" || move.substr(0, move.find(" ")) == "SAVE") {
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
    This function is Wrapper function for ParseMove function for P1 and P2 (not AI).
    @Param1 Hex: Pass the Board to ParseMove and DrawTable.
    
    return void
*/
void MakeMove(HEX& Hex) {

    if (Hex.turn == 0)  // Player 1
        cout << "Player 1! Make Your Move: ";

    else if (Hex.turn == 1)  // Player 2
        cout << "Player 2! Make Your Move: ";
    
    ParseMove(Hex);
    DrawTable(Hex);

}

/*
    This functions simulates the best possible move for AI(not best actually since it is simulating only one step after)
    Returns the Final Move.
    @Param1 Hex: Checking the board.

    returns Finalmove
*/
FinalMove SimulateMoves(HEX& Hex){

    int col;
    int row;
    int finalRowMove;
    int finalColMove;
    int leftCol = Hex.posList.AI_COL[Hex.posList.size-1];
    decltype(leftCol) rightCol = leftCol;
    bool foundMove = false;

    FinalMove finalMove;
    
    for(int i = Hex.posList.size-1; i >= 0; --i) {
        row = Hex.posList.AI_ROW[i];
        col = Hex.posList.AI_COL[i];
        
        if (IsValidAI(Hex, row, col-1)){
            leftCol = col-1;
            if (leftCol < Hex.posList.leftColDifference) {
                Hex.posList.leftColDifference = leftCol;
                            
                finalRowMove = row;
                finalColMove = col-1;

                foundMove = true;

                break;
            }
        }
        if(IsValidAI(Hex, row+1, col-1)){

            leftCol = col-1;
            if (leftCol < Hex.posList.leftColDifference) {
                Hex.posList.leftColDifference = leftCol;

                finalRowMove = row+1;
                finalColMove = col-1;

                foundMove = true;
                
                break;              
            }
        }
        if(IsValidAI(Hex, row, col+1)){
            rightCol = col+1;
            if (rightCol > Hex.posList.rightColDifference) {
                Hex.posList.rightColDifference = rightCol;

                finalRowMove = row;
                finalColMove = col+1;
                foundMove = true;
    
                break;
            }
        }
        if(IsValidAI(Hex, row-1, col+1)){
            rightCol = col+1;
            if (rightCol > Hex.posList.rightColDifference) {
                Hex.posList.rightColDifference = rightCol;

                finalRowMove = row-1;
                finalColMove = col+1;
                foundMove = true;

                //break;
            }
        }
    }

    if (!foundMove){
        int row;
        int col;
        uniform_int_distribution<int> dist(0, Hex.hexSize-1);
        
        do {
            row = dist(rng);
            col = dist(rng);
        }while (Hex.hexTable[row][col].val != DOT);

        Hex.posList.leftColDifference = col;
        Hex.posList.rightColDifference = Hex.hexSize-col;
        
        finalRowMove = row;
        finalColMove = col;
    }
    
    Hex.posList.SetPosition(finalRowMove, finalColMove);
    
    finalMove.row = finalRowMove;
    finalMove.col = finalColMove;

    cout << "AI made move: " << char('a' + finalMove.col) << " " << finalMove.row + 1 << endl;

    return finalMove;
}
/*
    Parses the move for AI. Function generates the first move. For other moves it simulates the possibles moves adjacent to the moves made before.

    @Param1 Hex: Table we will proceed.
    
    return void 
*/
void ParseMove_AI(HEX& Hex) {
    
    int row;
    int col;
    uniform_int_distribution<int> dist(0, Hex.hexSize-1);

    if(Hex.posList.size == 0){
        do {
            row = dist(rng);
            col = dist(rng);
        }while (Hex.hexTable[row][col].val != DOT);

        Hex.posList.SetPosition(row, col);
        Hex.posList.leftColDifference = col;
        Hex.posList.rightColDifference = col;
        Hex.hexTable[row][col].val = X;
    }
    else {
        auto finalMove = SimulateMoves(Hex);
        Hex.hexTable[finalMove.row][finalMove.col].val = X;
    }
}

/*
    Wrapper Function for ParseMove and ParseMove_AI functions.
    @Param1 Hex: Pass to the functions

    return void
*/
void MakeMove_AI(HEX& Hex) {

    if (Hex.turn == 0) { // Player 1
        cout << "Player 1! Make Your Move: ";
        ParseMove(Hex);
    }
    else if (Hex.turn == 1) { // AI
        cout << "AI! Make Your Move: " << endl;
        ParseMove_AI(Hex);
    }
    DrawTable(Hex); 

}
/*
    Updates whenever the one of the players make a move. It ends until the game is over.
    @Param1 Hex: Game Board

    return void
*/
void Update(HEX& Hex) {

    // We don't have to ask the player which side he/she wants to choose. It will always be Red side (Trying to connect bottom and up.)
    // Similarly AI or Player 2 will always trying to connect the left and right side (So They are in Blue side.)
    // Player 1 always start first. (I may implement the selection functionality if I want in future.)

    while (true) {

        if (Hex.opponent == 1) {
            MakeMove(Hex);
            if(IsGameOver(Hex))
                break;
        }
        else {
            MakeMove_AI(Hex);
            if(IsGameOver(Hex))
                break;
        }
    }
}
