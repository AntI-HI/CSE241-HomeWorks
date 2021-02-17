#include "hex.h"

using namespace std;

int main(int argc, char *argv[]){

    cout << endl << "Welcome to Drive File. " << endl << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "First and Second GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    HEX Hex1(8, 0);
    HEX Hex2(10, 0);

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
    // Testing getNumberOfMarked() static function.
    cout << "Getting the number of Marked Cells from all HEX games..." << endl;
    cout << HEX::getNumberOfMarked() << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Third GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    HEX Hex3;
    Hex3.LoadGame("file3.txt");
    // Testing the getGame(int) function
    cout << "Testing the getGame(int) function" << endl;
    HEX& aux = HEX::getGame(2);
    aux.DrawTable();
    //Test for IsGameOver() function
    cout << "Test for IsGameOver() function." << endl;
    cout << Hex3.IsGameOver() << endl;

    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Fourth GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << "Testing the third constructor which takes fileName to Load the game from file." << endl;
    HEX Hex4("file3.txt");

    // Fifth Game covers all the functionality that I implement within the HEX class.
    cout << "/////////////////////////////////////////////////////////////////" << endl;
    cout << endl << "Fifth GAME" << endl << endl;
    cout << "/////////////////////////////////////////////////////////////////" << endl;

    HEX Hex5;
    
    while(!HEX::getTerminate() && HEX::getNumberOfEndGame() < HEX::getNumberOfGames()) {
        HEX::getGame(HEX::getCurrentGame()-1).DrawTable();
        HEX::getGame(HEX::getCurrentGame()-1).Update();
    }

        
    return 0;
}
