#include "Functions.h"

using namespace std;

HexTable::HexTable() {
    val = 0;
    visited = false;
}

/*
    This constructor assigns the necessary informations in order for AI to keep track of its movement. Must be called properly.
*/
AI_POS_List::AI_POS_List(int hexSize) : colDifference(hexSize), rightColDifference(hexSize), leftColDifference(hexSize) {}

/*
    Assigns the location informations to corresponding variables to keep track of the progress.
*/
void AI_POS_List::SetPosition(int row, int col) {
    AI_ROW[size] = row;
    AI_COL[size] = col;
    size++;
}

// Made a global variable for time variable and random engine because we don't want to send or change the random engine.
// Also this is the case most of the times with random engines and time variables.
time_t now = chrono::system_clock::to_time_t(chrono::system_clock::now());
default_random_engine rng(now);

/*
    Starts the first frame and initialize the necessary informations.
    @Param1 hextable[][12]: main board
    @Param2 hexSize: board size
    @Param3 opponent: Who do you play against.

    return void
*/
void Start(HexTable hexTable[][12], int& hexSize, int& opponent) {

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
    // Assign this array to 0 to represent the elements of the table is dot all around.
    // Whenever the AI chooses a location to put 'x' this corresponds 1, or player chooses a location to put 'o' this corresponds 2.
    for(int i = 0; i < hexSize; ++i) 
        for(int j = 0; j < hexSize; ++j) 
            hexTable[i][j].val = 0;   

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

    DrawTable(hexTable, hexSize);
    Update(hexTable, hexSize, opponent);
}
/*
    DrawTable draws the last version of the table.
    @Param1 hexTable[][12]: actual table
    @Param2 hexSize: table size
    @Param3 winSituation: If winSituation is 1 We will highlight 'X'. If 2 highlight 'O'. For default it is 0.

    returns void
*/
void DrawTable(HexTable hexTable[][12], int hexSize, int winSituation) { 

    cout << " ";
    for( char l = 'a'; l < 'a'+hexSize; ++l) 
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
            switch(hexTable[i][j].val){
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
bool IsValidP1(HexTable hexTable[][12], int hexSize, int row, int col) {

    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && hexTable[row][col].val == 2 && !hexTable[row][col].visited){
        hexTable[row][col].visited = true;
        return true;
    }
    else if (hexTable[row][col].val == 0) {
        hexTable[row][col].visited = true;
    }
    return false;
}
/*
    Checks the Validity of the Move Played by Player 2. Return true if valid. Also we indicate the location we traveled to visited so we don't have to look again.
    @Param1 hexTable[][12]: To get the specific location's value
    @Param2 hexSize: table size used for checking the borders of the table. If exceeds the borders returns false.
    @Param3 row: row information 
    @Param4 col: column information

    returns bool
*/
bool IsValidP2(HexTable hexTable[][12], int hexSize, int row, int col) {

    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && hexTable[row][col].val == 1 && !hexTable[row][col].visited){
        hexTable[row][col].visited = true;
        return true;
    }
    else if (hexTable[row][col].val == 0) {
        hexTable[row][col].visited = true;
    }
    return false;
}
/*
    Checks the Validity of the Simulated Move by AI. Return true if valid. 
    @Param1 hexTable[][12]: To get the specific location's value
    @Param2 hexSize: table size used for checking the borders of the table. If exceeds the borders returns false.
    @Param3 row: row information 
    @Param4 col: column information

    returns bool
*/
bool IsValidAI(HexTable hexTable[][12], int hexSize, int row, int col) {

    if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && hexTable[row][col].val == 0)
        return true;
    
    return false;
}

/*
    Traverses the board for Player 1. If Player 1 completed the game it returns true. Otherwise returns false.
    @Param1 hexTable[][12]: Board which we will traverse.
    @Param2 hexSize: Table size to pass it on IsValidP1 function to check the borders exceeds.
    @Param3 row: Starting row point where we will traverse the tree.
    @Param4 col: Starting col point where we will traverse the tree.
    @Param5 found: Default Parameter which indicates if CheckP1 founds the end of the game.

    returns bool(found)
*/
bool CheckP1(HexTable hexTable[][12], int hexSize, int row, int col, bool found = false) {

    if (!IsValidP1(hexTable, hexSize, row, col))
        return false;
    
    if (row == hexSize-1 && hexTable[row][col].val == 2) {
        hexTable[row][col].visited = true;
        return true;
    }
   
    found = CheckP1(hexTable, hexSize, row-1, col, found) ||
            CheckP1(hexTable, hexSize, row-1, col+1, found) ||
            CheckP1(hexTable, hexSize, row, col+1, found) ||
            CheckP1(hexTable, hexSize, row+1, col, found) ||
            CheckP1(hexTable, hexSize, row+1, col-1, found) ||
            CheckP1(hexTable, hexSize, row, col-1, found); 

    return found;
}

/*
    Traverses the board for Player 2. If Player 2 completed the game it returns true. Otherwise returns false.
    @Param1 hexTable[][12]: Board which we will traverse.
    @Param2 hexSize: Table size to pass it on IsValidP1 function to check the borders exceeds.
    @Param3 row: Starting row point where we will traverse the tree.
    @Param4 col: Starting col point where we will traverse the tree.
    @Param5 found: Default Parameter which indicates if CheckP2 founds the end of the game.

    returns bool(found)
*/
bool CheckP2(HexTable hexTable[][12], int hexSize, int row, int col, bool found = false) {

    if (!IsValidP2(hexTable, hexSize, row, col))
            return false;
        
    if (col == hexSize-1 && hexTable[row][col].val == 1) {
        hexTable[row][col].visited = true;
        return true;
    }

    found = CheckP2(hexTable, hexSize, row-1, col, found) ||
            CheckP2(hexTable, hexSize, row-1, col+1, found) ||
            CheckP2(hexTable, hexSize, row, col+1, found) ||
            CheckP2(hexTable, hexSize, row+1, col, found) ||
            CheckP2(hexTable, hexSize, row+1, col-1, found) ||
            CheckP2(hexTable, hexSize, row, col-1, found); 

    return found;
}
/*
    This function is a wrapper function for CheckP1 and CheckP2 functions. It finds a starting point for both sides. 
    If it founds then calls the CheckP1 or CheckP2 functions to start traversing. Returns true if game is over. Otherwise false.
    @Param1 hexTable[][12]: Checking the entry point on the board.
    @Param2 hexSize: Table Size.
    @Param3 *turn: indicates which player is in the checking for Game Over.

    returns bool
*/
bool IsGameOver(HexTable hexTable[][12], int hexSize, int *turn) {

    bool finished = false;
    int row = 0;
    int col = 0;

    if (*turn == 0) {    // Which means check if player1 finished the game         
        while (col < hexSize && !finished) {
            if(hexTable[row][col].val == 2) {
                finished = CheckP1(hexTable, hexSize, row, col, finished);
            }
            if (!finished) col++;
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds(hexTable, hexSize);
        }

        if(finished) {
            cout << "Player1 WIN!" << endl;
            DrawTable(hexTable, hexSize, 2);
        }

        *turn = 1;
    }
    else if (*turn == 1) {   // Which means check if player2 or AI finished the game      
        while (row < hexSize && !finished) {
            if(hexTable[row][col].val == 1) {
                finished = CheckP2(hexTable, hexSize, row, col);
            }
            if (!finished) row++;
            // Everytime we check the board first reset all the visited locations.
            ResetVisiteds(hexTable, hexSize);
        }

        if(finished) {
            cout << "Player2 WIN!" << endl;
            DrawTable(hexTable, hexSize, 1);
        }

        *turn = 0;
    }
    return finished;
}
/*
    This function Resets the visited informations to 0 whenever the checking the board operation is complete.
    @Param1 hexTable[][12]: Set every nodes visited info to zero
    @Param2 hexSize: Table size.

    returns void
*/
void ResetVisiteds(HexTable hexTable[][12], int hexSize) {
    for (int i = 0; i < hexSize; ++i)
        for (int j = 0; j < hexSize; ++j)
            hexTable[i][j].visited = false;    
}
/*
    This function used for Getting the move from player1 or player2 (Not AI), After getting input, parsing it and checking the validity of the move.
    @Param1 hexTable[][12]: Table which will be used. 
    @Param2 turn: Indicates which player is making move (Player1 or Player2)
    @Param3 hexSize: Table Size

    returns void
*/
void ParseMove(HexTable hexTable[][12], int turn, int hexSize) {

    string alphabet = "abcdefghijkl";
    bool alpha = true;
    int row, col;
    bool breakLoop = false;
    string move;
    do {
        move = GetMove(hexSize);
        alpha = true;
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
        if (turn == 0 && hexTable[row-1][col].val == 0){
            hexTable[row-1][col].val = 2;
            breakLoop = true;
        }
        else if (turn == 1 && hexTable[row-1][col].val == 0) {
            hexTable[row-1][col].val = 1;
            breakLoop = true;
        }
        else { cout << "Make a valid Move: "; }
    }while(!breakLoop);
}

/*
    This function is called by ParseMove function to get the necessary move data from P1 or P2. Returns the move.
    @Param1 hexSize: Table size is used for checking the validity of the movement.

    returns string
*/
string GetMove(int hexSize) {

    string move;
    while (cin >> move) {
        if (move.length() < 2 || move.length() > 3) {
            cout << "Invalid Move! Make Your Move Again: "; 
            cin.clear();
            cin.ignore(100, '\n'); 
        }
        else if (move.length() == 2 && move.at(0) >= 'a' && move.at(0) <= 'a' + hexSize && 
                move.at(1) >= '1' && move.at(1) <= '1' + hexSize) { 
    
            break;
        }
        else if (hexSize > 9 && move.length() == 3 && move.at(0) >= 'a' && move.at(0) <= 'a' + hexSize && move.at(1) >= '1' &&
                 move.at(1) <= '1'+hexSize && move.at(2) >= '0' && move.at(2) <= '0' + hexSize) {
            
            break;
        }
           
    }       
    cin.clear();
    cin.ignore(100, '\n'); 
    return move; 
}

/*
    This function is Wrapper function for ParseMove function for P1 and P2 (not AI).
    @Param1 hexTable[][12]: Pass the Board to ParseMove and DrawTable.
    @Param2 hexSize: Pass the Table size to ParseMove and DrawTable.
    @Param3 turn: Which side we are making a move(P1 or P2)
*/
void MakeMove(HexTable hexTable[][12], int hexSize, int turn) {

    if (turn == 0) { // Player 1
        cout << "Player 1! Make Your Move: ";
        ParseMove(hexTable, turn, hexSize);
        DrawTable(hexTable, hexSize);
    }
    else if (turn == 1) { // Player 2
        cout << "Player 2! Make Your Move: ";
        ParseMove(hexTable, turn, hexSize);
        DrawTable(hexTable, hexSize);    
    }

}

/*
    This functions simulates the best possible move for AI(not best actually since it is simulating only one step after)
    Returns the Final Move.
    @Param1 hexTable[][12]: Checking the board.
    @Param2 posList: Keep track of best moves.
    #Param3 hexSize: Table size.

    returns Finalmove
*/
FinalMove SimulateMoves(HexTable hexTable[][12], AI_POS_List* posList, int hexSize){

    int index;
    int row;
    int col;
    int currentColDifference;   
    int finalRowMove;
    int finalColMove;
    int leftCol = posList->AI_COL[posList->size-1];
    int rightCol = leftCol;
    FinalMove finalMove;
    currentColDifference = posList->colDifference;

    for (int i =0; i < posList->size; ++i)
        cout << posList->AI_ROW[i] << " " << posList->AI_COL[i] << endl;

    for(int i = posList->size-1; i >= 0; --i) {
        
        row = posList->AI_ROW[i];
        col = posList->AI_COL[i];
        
        if (IsValidAI(hexTable, hexSize, row, col-1)){
            leftCol = col-1;
            if (leftCol < posList->leftColDifference) {
                posList->leftColDifference = leftCol;
            
                posList->colDifference--;
                posList->leftColDifference = leftCol;
                finalRowMove = row;
                finalColMove = col-1;

                break;
            }
        }
        if(IsValidAI(hexTable, hexSize, row+1, col-1)){

            leftCol = col-1;
            if (leftCol < posList->leftColDifference) {
                posList->leftColDifference = leftCol;

                posList->colDifference--;
                posList->leftColDifference = leftCol;
                finalRowMove = row+1;
                finalColMove = col-1;
                
                break;              
            }
        }
        if(IsValidAI(hexTable, hexSize, row, col+1)){
            rightCol = col+1;
            if (rightCol > posList->rightColDifference) {
                posList->rightColDifference = rightCol;

                posList->colDifference--;
                posList->rightColDifference = rightCol;
                finalRowMove = row;
                finalColMove = col+1;
    
                break;
            }
        }
        if(IsValidAI(hexTable, hexSize, row-1, col+1)){
            rightCol = col+1;
            if (rightCol > posList->rightColDifference) {
                posList->rightColDifference = rightCol;
                
                posList->colDifference--;
                posList->rightColDifference = rightCol;
                finalRowMove = row-1;
                finalColMove = col+1;

                break;
            }
        }
    }
    posList->SetPosition(finalRowMove, finalColMove);
    
    finalMove.row = finalRowMove;
    finalMove.col = finalColMove;

    cout << "AI made move: " << char('a' + finalMove.col) << " " << finalMove.row + 1 << endl;

    return finalMove;
}
/*
    Parses the move for AI. Function generates the first move. For other moves it simulates the possibles moves adjacent to the moves made before.

    @Param1 hexTable[][12]: Table we will proceed.
    @Param2 posList: Checking the AI's movement list.
    @Param3 hexSize: Table Size.

    return void 
*/
void ParseMove_AI(HexTable hexTable[][12], AI_POS_List* posList, int turn, int hexSize) {
    
    int row;
    int col;
    uniform_int_distribution<int> dist(0, hexSize-1);

    if(posList->size == 0){
        do {
            row = dist(rng);
            col = dist(rng);
        }while (hexTable[row][col].val != 0);

        posList->SetPosition(row, col);
        posList->colDifference--;
        posList->leftColDifference = col;
        posList->rightColDifference = col;
        hexTable[row][col].val = 1;
    }
    else {
        FinalMove finalMove = SimulateMoves(hexTable, posList, hexSize);
        hexTable[finalMove.row][finalMove.col].val = 1;
    }
}

/*
    Wrapper Function for ParseMove and ParseMove_AI functions.
    @Param1 hexTable[][12]: Pass to the functions
    @Param2 posList: Pass it to the ParseMoveAI function
    @Param3 hexSize: Table Size
    @Param4 turn: Player turn.

    return void
*/
void MakeMove_AI(HexTable hexTable[][12], AI_POS_List* posList, int hexSize, int turn) {

    if (turn == 0) { // Player 1
        cout << "Player 1! Make Your Move: ";
        ParseMove(hexTable, turn, hexSize);
        DrawTable(hexTable, hexSize);
    }
    else if (turn == 1) { // AI
        cout << "AI! Make Your Move: " << endl;
        ParseMove_AI(hexTable, posList, turn, hexSize);
        DrawTable(hexTable, hexSize);    
    }

}
/*
    Updates whenever the one of the players make a move. It ends until the game is over.
    @Param1 hexTable: Game Board
    @Param2 hexSize: Table Size
    @Param3 opponent: Which opponent we playing against (Player2 or AI)

    return void
*/
void Update(HexTable hexTable[][12], int hexSize, int opponent) {

    // We don't have to ask the player which side he/she wants to choose. It will always be Red side (Trying to connect bottom and up.)
    // Similarly AI or Player 2 will always trying to connect the left and right side (So They are in Blue side.)
    // Player 1 always start first. (I may implement the selection functionality if I want in future.)

    int turn = 0;   // Player1 represent 0, Player 2 or AI represent 1;
    AI_POS_List posList(hexSize);

    switch (opponent) {

        case 1: // If Playing against another user.
            do {
                MakeMove(hexTable, hexSize, turn);
            } while (!IsGameOver(hexTable, hexSize, &turn));
            break;

        case 0: // If Playing Against AI.
            do {
                MakeMove_AI(hexTable, &posList, hexSize, turn);
            }while (!IsGameOver(hexTable, hexSize, &turn));
    }
}