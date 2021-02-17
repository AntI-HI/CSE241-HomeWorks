#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_
#include <iostream>
#include <string>
//#include <math.h>
#include <random>
#include <chrono>


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
    int AI_ROW[72];             // Keeps the ROWs for Moves that's been played by AI 
    int AI_COL[72];             // Keeps the COLs for Moves that's been played by AI
    int size = 0;               // Keeps the AI_ROW and AI_COL's current sizes.
    int colDifference = 12;     // This attribute keeps the total column difference so it affects the overall movements for AI.
    int rightColDifference = 12;   // This attributs keeps the best position difference for right side of the board
    int leftColDifference = 12; // This attributs keeps the best position difference for left side of the board

    // Constructor that assigns necessary table informations.
    AI_POS_List(int);

    // Sets the positions to AI_ROW and AI_COL to save the AI progress.
    void SetPosition(int, int);
       
};

/*
    This struct used to return the final move that the AI is gonna perform.
*/
struct FinalMove
{
    int row;
    int col;
};

void Start(HexTable[][12], int&, int&);
void DrawTable(HexTable[][12], int, int = 0);
void Update(HexTable[][12], int, int);
bool IsGameOver(HexTable[][12], int, int*);
void ParseMove(HexTable[][12], int, int);
bool CheckP1(HexTable[][12], int, int, int, bool);
bool CheckP2(HexTable[][12], int, int, int, bool);
bool IsValidP1(HexTable[][12], int, int, int);
bool IsValidP2(HexTable[][12], int, int, int);
bool IsValidAI(HexTable[][12], int, int, int);
void ResetVisiteds(HexTable[][12], int);
void MakeMove(HexTable[][12], int, int);
void MakeMove_AI(HexTable[][12], AI_POS_List*, int, int);
void ParseMove_AI(HexTable[][12], AI_POS_List*, int, int);
FinalMove SimulateMoves(HexTable[][12], AI_POS_List*, int);
std::string GetMove(int);

#endif /* Functions.h */