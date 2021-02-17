#include <iostream>
#include "AbstractHex.h"
#include "HexVector.h"
#include "MyException.h"
#include "HexAdapter.cpp"
#include "HexArray1D.h"
#include "states.h"

using namespace std;
using namespace KAYA_GTU;

bool isValid(AbstractHex** Games, int numberOfGames) {

    for (int i=0; i < numberOfGames; ++i){
        if (Games[i]->getSize() < 5 || Games[i]->getSize() > 26){
            cout << "Game " << "i" << " size = " << Games[i]->getSize() << endl;
            return false;
        }
        if (Games[i]->getUserMarked() != Games[i]->getOpponentMarked() && !Games[i]->getEnd()) {
            cout << "Game " << i << " UserMarked = " << Games[i]->getUserMarked() << ", OpponentMarked = " << Games[i]->getOpponentMarked() << endl;
            return false;
        }
    }
    return true;

}

int main(int argc, char *argv[]){

    cout << "\n_________________________________________________________" << endl;
    cout << "Drive File" << endl;
    cout << "_________________________________________________________" << endl << endl;


    cout << "Creating array of AbstractHex pointers... " << endl;

    AbstractHex* Games[5];

    cout << "HexArray1D Class Testing..." << endl;
    Games[0] = new HexArray1D("file1.txt");
    Games[0]->print(cout);
    

    cout << "Testing Copy Constructor for HexArray1D Class...\n Before Assignment:" << endl;
    Games[1] = new HexArray1D(Games[0]);
    Games[1]->print(cout);
    cout << "After Assignment:" << endl;

    Games[0]->print(cout);

    cout << "Testing operator== for HexArray1D Class..." << endl;
    cout << Games[0]->operator==(*Games[1]) << endl;

    cout << "HexAdapter Class Testing..." << endl;
    Games[2] = new HexAdapter<vector, Cell>("file1.txt");
    Games[2]->print(cout);
    cout << endl;
    cout << "lastMove() method: ";    
    try {
        cout << Games[2]->lastMove().getVal() << endl;
        cout << "Operator() testing: " << Games[2]->operator()(0,0) << endl;
    }
    catch(MyException ME){
        cerr << "Error Occured. Exception Handled. Terminating..." << endl;
        exit(EXIT_FAILURE);
    }

    cout << "HexVector Class Testing using AbstractHex as base class as reference..." << endl;
    Games[3] = new HexVector(10,0);
    Games[3]->play(1,2);
    Games[3]->setTurn(1);
    Games[3]->print(cout);
    Games[3]->play(2,2);
    Games[3]->play();
    Games[3]->print(cout);
    Games[3]->setTurn(0);

    cout << "Testing isValid function (Game number 3 is not valid so returns 0): " << isValid(Games, 4) << endl;

    cout << "I am making Game Number 3 valid again..." << endl;
    Games[3]->play(1,1);
    Games[3]->setTurn(0);

    cout << "Testing numberOfMoves function... ";
    cout << Games[3]->numberOfMoves() << endl;

    cout << "Testing writeToFile Function..." << endl;
    ofstream out;
    out.open("file2.txt");
    Games[3]->writeToFile(out);
    cout << "File is written succesfully..." << endl;

    cout << "Testing readFromFile Function..." << endl;
    ifstream input;
    input.open("file1.txt");
    Games[3]->readFromFile(input);
    cout << "File is read succesfully..." << endl;
    Games[3]->print(cout);

    cout << "lastMove() method: ";    
    try {
        cout << Games[3]->lastMove().getVal() << endl;
        cout << "Operator() testing: " << Games[3]->operator()(5,5) << endl;
    }
    catch(MyException ME){
        cerr << "Error Occured. Exception Handled. Continuing..." << endl;
        //exit(EXIT_FAILURE);
    }


    cout << "HexVector Class Testing..." << endl;
    HexVector hv1;
    Games[4] = &hv1;
    cout << "setSize() method test." << endl;
    Games[4]->setSize(8);
    Games[4]->print(cout);
    
    try {
        cout << "lastmove Exception throwing test: " << Games[4]->lastMove().getVal() << endl;
    }
    catch (MyException ME){
        cerr << "Error Occured. Continuing" << endl;
        //exit(EXIT_FAILURE);
    }

    while(Games[4]->getEnd() == false) {
        Games[4]->Update();
    }   

    cout << "Global Function isValid Test(Every Game is valid this time.)... " << isValid(Games,5) << endl;
    cout << "Finished" << endl;

    for(int i = 0; i < 4; ++i)
        delete Games[i];
    
    cout << "Finished" << endl;

    
    return 0;
}
