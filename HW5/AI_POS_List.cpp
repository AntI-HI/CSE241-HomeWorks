#include "AI_POS_List.h"

using namespace std;

namespace KAYA_GTU {

/*
Assigns the location informations to corresponding variables to keep track of the progress.
*/
void AI_POS_List::SetPosition(int row, int col) {
    
    AI_ROW[size] = row;
    AI_COL[size] = col;
    size++;
}

}