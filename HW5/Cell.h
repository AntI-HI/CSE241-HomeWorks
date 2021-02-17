#ifndef CELL_H_
#define CELL_H_
#include <iostream>

namespace KAYA_GTU {

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
    Cell(int, int, int);
    int getRow() const;
    int getCol() const;
    int getVal() const;
    bool getVisited() const;

    void setRowCol(int, int);
    void setRowColVal(int, int, int);
    void setVal(int);
    void setVisited(int);

    Cell (const Cell& other) {

        row = other.row;
        col = other.col;
        val = other.val;
        visited = other.visited;

    }

    ~Cell(){ }
};

}
#endif