#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>

enum States{DOT, X, O}; // Enumerator represents the which state/value is the current location is.
                        // DOT represents empty location, X Represents oppenents move, O represents your move.

struct HexTable
{
        int val;        // Keeps the corresponding value for the particular location on board.
        bool visited;   // Indicates the node has been visited or not. This is gonna help traverse the adjacents.

        HexTable();
};
/*
This Struct keeps the necessary informations whenever the AI Attempts to make a move.
*/
struct AI_POS_List  
{
    int size;               // Keeps the AI_ROW and AI_COL's current sizes.
    int rightColDifference;   // This attributs keeps the best position difference for right side of the board
    int leftColDifference; // This attributs keeps the best position difference for left side of the board
    int AI_ROW[72];             // Keeps the ROWs for Moves that's been played by AI 
    int AI_COL[72];             // Keeps the COLs for Moves that's been played by AI

    // Constructor that assigns necessary table informations.
    AI_POS_List(const int&);

    // Sets the positions to AI_ROW and AI_COL to save the AI progress.
    void SetPosition(int, int);
    
};
    
struct HEX
{
    int hexSize;
    int opponent;
    int turn;
    AI_POS_List posList;
    HexTable hexTable[12][12];

    HEX(const int&);
};

/*
    This struct used to return the final move that the AI is gonna perform.
*/
struct FinalMove
{
    int row;
    int col;
};

void Start();
void DrawTable(HEX&, int = 0);
void Update(HEX&);
bool IsGameOver(HEX&);
void ParseMove(HEX&);
bool CheckP1(HEX&, int, int, bool = false);
bool CheckP2(HEX&, int, int, bool = false);
bool IsValidP1(HEX&, const int&, const int&);
bool IsValidP2(HEX&, const int&, const int&);
bool IsValidAI(HEX&, const int&, int, int);
void ResetVisiteds(HEX&);
void MakeMove(HEX&);
void MakeMove_AI(HEX&);
FinalMove SimulateMoves(HEX&);
std::string GetMove(const int&, bool&);
void ParseCommand(HEX&, const std::string&);

#endif /* Functions.h */