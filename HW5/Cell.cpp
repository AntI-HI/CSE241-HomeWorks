#include "Cell.h"

using namespace std;

namespace KAYA_GTU {

Cell::Cell() : row(-1), col(-1), val(-1), visited(false) {}
Cell::Cell(int Row, int Col) : row(Row), col(Col), val(0), visited(false) {}
Cell::Cell(int Row, int Col, int val) : row(Row), col(Col), val(val), visited(false) {}
int Cell::getVal() const { return val; }
bool Cell::getVisited() const { return visited; }
int Cell::getRow() const { return row; }
int Cell::getCol() const { return col; }
void Cell::setRowCol(int Row, int Col) { row = Row; col = Col; }
void Cell::setRowColVal(int Row, int Col, int Val) { row = Row; col = Col; val = Val;}
void Cell::setVal(int newVal) { val = newVal; }
void Cell::setVisited(int newVal) { visited = newVal; }
    
}