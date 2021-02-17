#ifndef AI_POS_LIST_H_
#define AI_POS_LIST_H_
#include <iostream>

namespace KAYA_GTU {

/*
This class keeps the necessary informations whenever the AI Attempts to make a move.
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

/*
    This constructor assigns the necessary informations in order for AI to keep track of its movement. Must be called properly.
*/
inline AI_POS_List::AI_POS_List(const int& hexSize) : size(0), rightColDifference(hexSize), leftColDifference(hexSize) {}
inline AI_POS_List::AI_POS_List() {}

inline int AI_POS_List::getSize() const { return size; }
inline int AI_POS_List::getRightColDifference() const { return rightColDifference; }
inline int AI_POS_List::getLeftColDifference() const { return leftColDifference; }
inline int AI_POS_List::getRow(int idx) const { return AI_ROW[idx]; }
inline int AI_POS_List::getCol(int idx) const { return AI_COL[idx]; }

inline void AI_POS_List::setSize(int newSize) { size = newSize; }
inline void AI_POS_List::setRightColDifference(int newVal) { rightColDifference = newVal;}
inline void AI_POS_List::setLeftColDifference(int newVal) { leftColDifference = newVal; }
inline void AI_POS_List::setRow(int idx, int newVal) { AI_ROW[idx] = newVal; }
inline void AI_POS_List::setCol(int idx, int newVal) { AI_COL[idx] = newVal; }

}

#endif