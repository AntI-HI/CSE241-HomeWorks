#include "hex.h"

using namespace std;

int main(int argc, char *argv[]){

    cout << endl << "Welcome to Drive File. " << endl << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "First and Second GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    HEX Hex1(8, 0);
    HEX::setNumberOfGames();
    HEX::setGame(Hex1);
    HEX::setCurrentGame();

    // Testing play(int, int) function for Hex1 object
    Hex1.play(1,1);
    cout << "Testing play(int, int) function for Hex1 object" << endl;
    // Testing DrawTable()const function for Hex1 object
    cout << "Testing DrawTable()const function for Hex1 object" << endl;
    Hex1.DrawTable();
    // Testing play() function for Hex1 object
    cout << "Testing play() function for Hex1 object" << endl;
    Hex1.play();
    // Testing DrawTable()const function for Hex1 object
    cout << "Testing DrawTable()const function for Hex1 object" << endl;
    Hex1.DrawTable();

    cout << "Creating Hex2 object using Copy Constructor." << endl;
    HEX Hex2(Hex1);
    HEX::setNumberOfGames();
    HEX::setGame(Hex2);
    HEX::setCurrentGame();
    // Testing play(int, int) function for Hex2 object
    cout << "Testing play(int, int) function for Hex2 object" << endl;
    Hex2.play(2,1);
    // Testing DrawTable()const function for Hex2 object
    cout << "Testing DrawTable()const function for Hex2 object" << endl;
    Hex2.DrawTable();
    // Testing play() function for Hex2 object
    cout << "Testing play() function for Hex2 object" << endl;
    Hex2.play();
    // Testing DrawTable()const function for Hex2 object
    cout << "Testing DrawTable()const function for Hex2 object" << endl;
    Hex2.DrawTable();

    // Testing SaveGame(const std::string&)const function and LoadGame(const std:: string&) functions.
    cout << "Testing SaveGame(const std::string&)const function and LoadGame(const std:: string&) functions." << endl;
    cout << "Saving Hex1 object to file.txt..." << endl;
    Hex1.SaveGame("file.txt");
    cout << "Loading the game from file2.txt to Hex2 object." << endl;
    Hex2.LoadGame("file2.txt");
    
    // Testing compareGames(const HEX&)const function.
    cout << "Comparing Hex1 and Hex2..." << endl;
    cout << Hex1.compareGames(Hex2) << endl;
    cout << "Comparing Hex1 and Hex2 using == operator." << endl;
    cout << (Hex1 == Hex2) << endl;
    // Testing getNumberOfMarked() static function.
    cout << "Getting the number of Marked Cells from all HEX games..." << endl;
    cout << HEX::getNumberOfMarked() << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Third GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;

    HEX Hex3;
    HEX::setNumberOfGames();
    HEX::setGame(Hex3);
    HEX::setCurrentGame();
    cout << "Testing LoadGame." << endl;
    Hex3.LoadGame("file3.txt");
    // Testing the getGame(int) function
    cout << "Testing the getGame(int) function" << endl;
    HEX& aux = HEX::getGame(2);
    aux.DrawTable();
    //Test for IsGameOver() function
    cout << "Test for IsGameOver() function." << endl;
    cout << Hex3.IsGameOver() << endl;

    cout << "Test for Assignment operator." << endl;
    Hex3 = Hex2;
    cout << Hex3;

    cout << "Testing score for Third Game: ";
    cout << Hex3.getScore() << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Fourth GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    
    HEX Hex4;
    HEX::setNumberOfGames();
    HEX::setGame(Hex4);
    HEX::setCurrentGame();
    ifstream input;
    input.open("file3.txt");
    cout << "Testing overloaded stream extraction operator." << endl;
    input >> Hex4;
    cout << "Testing overloaded stream insertion operator." << endl;
    cout << Hex4;

    cout << "Testing prefix decrement operator." << endl;
    cout << --Hex4;
    cout << "Testing postfix decrement operator." << endl;
    cout << Hex4--;

    cout << "Writing to a file using stream insertion operator." << endl;
    ofstream output;
    output.open("file4.txt");
    output << Hex4;

    // Fifth Game covers all the functionality that I implement within the HEX class.
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Fifth GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;

    HEX Hex5;
    HEX::setNumberOfGames();
    HEX::setGame(Hex5);
    HEX::setCurrentGame();
    Hex5.playGame();
    
    while(!HEX::getTerminate() && HEX::getNumberOfEndGame() < HEX::getNumberOfGames()) {
        HEX::getGame(HEX::getCurrentGame()-1).DrawTable();
        HEX::getGame(HEX::getCurrentGame()-1).Update();
    }

    cout << "All games are finished. Goodbye. " << endl;

    delete [] HEX::getGames();
        
    return 0;
}
