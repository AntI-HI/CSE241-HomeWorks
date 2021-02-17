#ifndef ABSTRACTHEX_H_
#define ABSTRACTHEX_H_
#include <iostream>
#include "Cell.h"
#include "AI_POS_List.h"
#include "FinalMove.h"
#include "MyException.h"

namespace KAYA_GTU {

class AbstractHex {

public:
    AbstractHex() : turn(0), end(false), lastmove(), numOfMoves(0), userMarked(0), opponentMarked(0){}
    AbstractHex(const int size, const int opponent) : size(size), end(false), lastmove(),
                         numOfMoves(0), userMarked(0), opponentMarked(0), opponent(opponent), turn(0), posList(size){}

    virtual void print(std::ostream&) const = 0;
    virtual void readFromFile(std::ifstream&) = 0;
    virtual void writeToFile(std::ofstream&) const = 0;
    virtual void reset() = 0;
    virtual void play() = 0;
    virtual void play(int row, int col) = 0;
    virtual bool isEnd() = 0;
    virtual int operator()(int row, int col) const throw(MyException) = 0;
    virtual bool operator==(const AbstractHex&) = 0;
    virtual const Cell& lastMove() throw(MyException) { if (lastmove.getVal() == -1) throw MyException(); else return lastmove;}
    virtual int numberOfMoves() {return numOfMoves;}
    virtual int getSize() const { return size; }
    virtual void setSize(int newSize) {
        if(newSize < 5 || newSize > 26){
            std::cerr << "Sorry. You Entered the wrong value!! Terminating";
            exit(EXIT_FAILURE);
        }    
        size = newSize;
        posList.setLeftColDifference(size);
        posList.setRightColDifference(size);
        posList.setSize(0);
        createCells();
    }

    virtual int getUserMarked() const { return userMarked; }
    virtual int getOpponentMarked() const { return opponentMarked; }
    virtual int getTurn() const { return turn; }
    virtual void setTurn(int turn) { this->turn = turn; }
    virtual int getOpponent() const { return opponent; }
    virtual void setOpponent(int opp) { opponent = opp; }
    virtual int getWinSituation() const { return winSituation; }
    virtual void setWinSituation(int ws) { winSituation = ws; }
    virtual bool getEnd() const { return end; }
    virtual const AI_POS_List& getAI_POS_List() const { return posList; }
    //virtual const vector<FinalMove> getFinalMoves() const { return movesMade; }

    virtual void playGame() = 0;
    virtual void Update() = 0;

    virtual ~AbstractHex() { std::cout << "AbstractHex Destructor Called." << std::endl;}

    
protected:
    
    int size;
    bool end;
    Cell lastmove;
    int numOfMoves;
    int opponent;
    int turn;   // If turn is 0 then it is player1, if turn is 1 then it is AI.
    int winSituation;
    int userMarked;
    int opponentMarked;
    int score;
    AI_POS_List posList;
    //std::vector<FinalMove> movesMade;
    
    virtual void createCells() = 0;
};

}

#endif