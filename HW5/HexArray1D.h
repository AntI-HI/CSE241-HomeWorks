#ifndef HEXARRAY1D_H_
#define HEXARRAY1D_H_
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include "AbstractHex.h"
#include "states.h"

namespace KAYA_GTU {

class HexArray1D : public AbstractHex {

public:

    HexArray1D();
    HexArray1D(const int, const int);
    HexArray1D(const std::string&);
    // Copy Constructor
    HexArray1D(const AbstractHex*);

    void print(std::ostream&) const;
    void readFromFile(std::ifstream&);
    void writeToFile(std::ofstream&) const;
    bool isEnd();
    void reset();
    void play();
    void play(int row, int col);
    int operator()(int row, int col) const throw(MyException);
    bool operator==(const AbstractHex&);
    // Assignment Operator
    HexArray1D& operator=(AbstractHex*);

    void setCell(int row, int col, int val) { hexCells[row*size + col].setVal(val); }
    const Cell& getCell(int row, int col) { return hexCells[row*size +col]; }

    void playGame();
    void Update();

    //Destructor
    ~HexArray1D(){
        std::cout << "HexArray1D Destructor Called." << std::endl;

        for (int i = 0; i < size*size; ++i){
            hexCells[i].~Cell();
        }
        hexCells = nullptr;
    }

private:
    //AI_POS_List posList;
    Cell* hexCells;
    //std::vector<FinalMove> movesMade;

// private Functions
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
    void createCells();

};

}

#endif