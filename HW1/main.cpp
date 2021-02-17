#include "Functions.h"

using namespace std;

int main(){
 
    int hexSize;                    // Indicates the table size for row and column.
    int opponent;                   // opponent indicates which one we are playing against.
    HexTable hexTable[12][12];      // Statically alocated board.

    Start(hexTable, hexSize, opponent); //fLet's trigger the engine :)

    return 0;
}
