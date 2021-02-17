#ifndef HEXVECTOR_H_
#define HEXVECTOR_H_
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <fstream>
#include <sstream>
#include "AbstractHex.h"
#include "Cell.h"
#include "AI_POS_List.h"
#include "FinalMove.h"
#include "states.h"

namespace KAYA_GTU {

class HexVector : public AbstractHex {
    
public:

    HexVector();
    HexVector(const int, const int);
    HexVector(const std::string&);

    void print(std::ostream&) const;
    void readFromFile(std::ifstream&);
    void writeToFile(std::ofstream&) const;
    bool isEnd();
    void reset();
    void play();
    void play(int row, int col);
    int operator()(int row, int col) const throw(MyException);
    bool operator==(const AbstractHex&);

    void playGame();
    void Update();

    ~HexVector() {std::cout << "HexVector Destructor Called." << std::endl; }

private:
    //AI_POS_List posList;
    std::vector<std::vector<Cell>> hexCells;
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