#ifndef HEX_H_
#define HEX_H_
#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include "FinalMove.h"

enum States{DOT, X, O}; // Enumerator represents the which state/value is the current location is.
                        // DOT represents empty location, X Represents oppenents move, O represents your move.

// MAIN Game Class. Everything about Hex game is contained within this class.
class HEX
{
private:

    /*
    This Struct keeps the necessary informations whenever the AI Attempts to make a move.
    */
    class AI_POS_List  
    {
    private:
        int size;               // Keeps the AI_ROW and AI_COL's current sizes.
        int rightColDifference;   // This attributs keeps the best position difference for right side of the board
        int leftColDifference; // This attributs keeps the best position difference for left side of the board
        int AI_ROW[26*26/2];             // Keeps the ROWs for Moves that's been played by AI
        int AI_COL[26*26/2];             // Keeps the COLs for Moves that's been played by AI

    public:
        // Constructor that assigns necessary table informations.
        AI_POS_List(const int&);
        AI_POS_List();

        int getSize() const;
        int getRightColDifference() const;
        int getLeftColDifference() const;
        int getRow(int) const;
        int getCol(int) const;

        // Sets the positions to AI_ROW and AI_COL to save the AI progress.
        void SetPosition(int, int);
        void setSize(int);
        void setRightColDifference(int);
        void setLeftColDifference(int);
        void setRow(int, int);
        void setCol(int, int);
    };


public:
    // Public Inner Class Cell
    class Cell
    {
    private:
        int row;
        int col;
        int val;        // Keeps the corresponding value for the particular location on board.
        bool visited;   // Indicates the node has been visited or not. This is gonna help traverse the adjacents.

    public:
        Cell();
        Cell(int, int);
        int getRow() const;
        int getCol() const;
        int getVal() const;
        bool getVisited() const;

        void setRowCol(int, int);
        void setVal(int);
        void setVisited(int);

    };

private:
    int hexSize;
    int opponent;
    int turn;   // If turn is 0 then it is player1, if turn is 1 then it is AI.
    int winSituation;
    int userMarked;
    int opponentMarked;
    int score;
    bool end;
    AI_POS_List posList;
    Cell** hexCells;
    FinalMove* movesMade;
    int currentMoveMade;
    int totalMoveMade;
    
    static int numberOfMarked;
    static int numberOfGames;
    static bool terminate;
    static int currentGame;
    static int numberOfEndGame;
    static HEX** games;

    FinalMove ParseMove_AI();
    void ParseMove();
    const std::string GetMove(bool&) const;
    void GetCommand();
    void ParseCommand(const std::string&);
    FinalMove SimulateMoves();
    bool IsValidAI(int row, int col) const;
    bool IsValidP1(const int&, const int&);
    bool IsValidP2(const int&, const int&);
    void ResetVisiteds();
    bool CheckP1(int, int, bool = false);
    bool CheckP2(int, int, bool = false);
    void MakeMove_AI();
    void MakeMove();
    void createCells(bool = true);

public:
    
    /* Constructors */
    HEX();
    explicit HEX(const int, const int);
    explicit HEX(const std::string&);

    /* Copy Constructor */
    HEX(const HEX&);

    static int getNumberOfMarked();
    static void setNumberOfMarked(int = 1);
    static int getNumberOfGames();
    static void setNumberOfGames();
    static void setCurrentGame();
    static void setGame(HEX&);
    static HEX& getGame(int);
    static HEX** getGames();
    static bool getTerminate();
    static int getCurrentGame();
    static int getNumberOfEndGame();

    int getSize() const{ return hexSize; }
    int getOpponent() const{ return opponent; }
    int getTurn() const{ return turn; } 
    int getWinSituation() const { return winSituation; }  
    AI_POS_List& getPosList() { return posList; }
    Cell** getHexCells() { return hexCells; }
    int getWidth() const { return hexSize; }
    int getHeight() const { return hexSize; }
    int getUserMarked() const { return userMarked; };
    int getOpponentMarked() const { return opponentMarked; }
    int getScore() const { return score; }
    int getEnd() const { return end; }
    
    void setSize(const int);
    void setOpponent(const int);
    void setTurn(const int);
    void setWinSituation(int);
    void setUserMarked() { ++userMarked; }
    void setOpponentMarked() { ++opponentMarked; }

    void SaveGame(const std::string&) const;
    void LoadGame(const std::string&);
    void LoadFromInputStream(std::istream&);
    void mainMenu();

    void DrawTable(std::ostream& = std::cout) const;

    bool compareGames(const HEX&) const;
    void calculateScore();

    const Cell& play();
    void play(int, int);

    void playGame(std::istream& = std::cin);
    bool IsGameOver();
    
    void Update();

    /* Operator Overloadings */

    // Assignment Operator Overloaded
    HEX& operator=(const HEX&);

    // Stream insertion and extraction operators.
    friend std::ostream& operator<<(std::ostream&, const HEX&);
    friend std::istream& operator>>(std::istream&, HEX&);

    HEX& operator--(); 
    HEX operator--(int);   

    bool operator==(const HEX& other) const { return compareGames(other); };

    // Destructor
    ~HEX();
};


//////////////////////////////////////////////////////////

/*
    Sets the location value and its visited condition.
*/
inline HEX::Cell::Cell() : val(0), visited(false) {}
inline HEX::Cell::Cell(int Row, int Col) : row(Row), col(Col), val(0), visited(false) {}
inline int HEX::Cell::getVal() const { return val; }
inline bool HEX::Cell::getVisited() const { return visited; }
inline int HEX::Cell::getRow() const { return row; }
inline int HEX::Cell::getCol() const { return col; }

inline void HEX::Cell::setRowCol(int Row, int Col) { row = Row; col = Col; }
inline void HEX::Cell::setVal(int newVal) { val = newVal; }
inline void HEX::Cell::setVisited(int newVal) { visited = newVal; }

/*
    This constructor assigns the necessary informations in order for AI to keep track of its movement. Must be called properly.
*/
inline HEX::AI_POS_List::AI_POS_List(const int& hexSize) : size(0), rightColDifference(hexSize), leftColDifference(hexSize) {}
inline HEX::AI_POS_List::AI_POS_List() {}

inline int HEX::AI_POS_List::getSize() const { return size; }
inline int HEX::AI_POS_List::getRightColDifference() const { return rightColDifference; }
inline int HEX::AI_POS_List::getLeftColDifference() const { return leftColDifference; }
inline int HEX::AI_POS_List::getRow(int idx) const { return AI_ROW[idx]; }
inline int HEX::AI_POS_List::getCol(int idx) const { return AI_COL[idx]; }

inline void HEX::AI_POS_List::setSize(int newSize) { size = newSize; }
inline void HEX::AI_POS_List::setRightColDifference(int newVal) { rightColDifference = newVal;}
inline void HEX::AI_POS_List::setLeftColDifference(int newVal) { leftColDifference = newVal; }
inline void HEX::AI_POS_List::setRow(int idx, int newVal) { AI_ROW[idx] = newVal; }
inline void HEX::AI_POS_List::setCol(int idx, int newVal) { AI_COL[idx] = newVal; }

#endif /* hex.h */