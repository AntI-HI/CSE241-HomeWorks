#ifndef FINALMOVE_H_
#define FINALMOVE_H_

//This struct used to return the final move that the AI is gonna perform.
class FinalMove
{
private:
    int row;
    int col;
public:
    FinalMove(){}
    FinalMove(int row, int col) : row(row), col(col) {}
    int getRow() const;
    int getCol() const;
    void setRow(int);
    void setCol(int);
};

#endif