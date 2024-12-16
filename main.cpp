#include <iostream>
#include "BoardGame_Classes.h"
#include "Pyramid tic tac toe.h"
#include "MinMax_Pyramid.h"
#include "Word tic tac toe.h"
#include "Numerical tic tac toe.h"
#include "inverse_tic_tac_toe.h"
#include "5x5_tic_tac_toe.h"
#include "Four_In_Row.h"

template<typename T>
Player<T>* setupPlayer(const string& gameName,  Board<T>* board, char symbol){


    string playerName;
    cout << "Enter Player " << symbol << " name(with no spaces): ";
    cin >> playerName;
    cout << "Choose Player " << symbol << "type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    if(gameName == "Pyramid tic tac toe" ) {
        cout << "3. Smart Computer (AI)\n";
    }

    string type;
    while(true) {
        string choice;
        cin >> choice;
        if (choice == "1") {
            type = "Human";
            break;
        }
        else if (choice == "2") {
            type = "Random Computer";
            break;
        }
        else if (choice == "3") {
            type = "Smart Computer (AI)";
            break;
        }
        else{
            cout << "Choose a valid option\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

        }
    }

    if(gameName == "Pyramid tic tac toe"){
        if(type == "Human"){
            return new Pyramid_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new Pyramid_Random_Player<T>(symbol);
        }
        else{
            auto* player =  new Pyramid_MinMax_Player<T>(symbol);
            player->setBoard(board);
            return player;
        }
    }
    else if(gameName == "Word tic tac toe"){
        if(type == "Human"){
            return new Word_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new Word_Random_Player<T>(symbol);
        }
        else{

        }
    }
    else if(gameName == "Inverse tic tac toe"){
        if(type == "Human"){
            return new Inverse_X_O_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new Inverse_X_O_Random_Player<T>(symbol);
        }
        else{

        }
    }
    else if(gameName == "Numerical tic tac toe"){
        if(type == "Human"){
            return new Numerical_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new Numerical_Random_Player<T>(symbol);
        }
        else{

        }
    }
    else if(gameName == "5X5 tic tac toe"){
        if(type == "Human"){
            return new _5x5_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new _5x5_Random_Player<T>(symbol);
        }
        else{

        }
    }
    else if(gameName == "Connect 4 tic tac toe"){
        if(type == "Human"){
            return new Four_in_Row_Player<T>(playerName,symbol);
        }
        else if(type == "Random Computer"){
            return new Four_in_Row_Random_Player<T>(symbol);
        }
        else{

        }
    }

}



void mainMenu(){
    cout << setfill('-') << setw(37) << "" <<'\n';
    cout << "Welcome to the Board Games simulator\n";
    cout << setfill('-') << setw(37) << "" <<'\n';

    while(true){
        cout << "Choose one of the following options:\n";
        cout << "1- Pyramid tic tac toe\n";
        cout << "2- Word tic tac toe\n";
        cout << "3- Inverse tic tac toe\n";
        cout << "4- Numerical tic tac toe\n";
        cout << "5- 5X5 tic tac toe\n";
        cout << "6- Connect 4 tic tac toe\n";
        cout << "7- Exit\n";
        string choice;
        cin >> choice;

        if(choice == "1"){
            Player<char>* players[2];
            Board<char>* board;
            board = new Pyramid_Board<char>;
            players[0] = setupPlayer<char>("Pyramid tic tac toe",board,'X');
            players[1] = setupPlayer<char>("Pyramid tic tac toe",board,'O');
            GameManager<char> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
        }
        else if(choice == "2"){
            Player<char>* players[2];
            Board<char>* board;
            board = new Word_Board<char>;
            players[0] = setupPlayer<char>("Word tic tac toe",board,'X');
            players[1] = setupPlayer<char>("Word tic tac toe",board,'O');
            GameManager<char> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;

        }
        else if(choice == "3"){
            Player<char>* players[2];
            Board<char>* board;
            board = new Inverse_X_O_Board<char>;
            players[0] = setupPlayer<char>("Inverse tic tac toe",board,'X');
            players[1] = setupPlayer<char>("Inverse tic tac toe",board,'O');
            GameManager<char> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
        }
        else if(choice == "4"){
            Player<int>* players[2];
            Board<int>* board;
            board = new Numerical_Board<int>;
            players[0] = setupPlayer<int>("Numerical tic tac toe",board,'X');
            players[1] = setupPlayer<int>("Numerical tic tac toe",board,'O');
            GameManager<int> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
        }
        else if(choice == "5"){
            Player<char>* players[2];
            Board<char>* board;
            board = new _5x5_Board<char>;
            players[0] = setupPlayer<char>("5X5 tic tac toe",board,'X');
            players[1] = setupPlayer<char>("5X5 tic tac toe",board,'O');
            GameManager<char> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
        }
        else if(choice == "6"){
            Player<char>* players[2];
            Board<char>* board;
            board = new Four_in_Row_Board<char>;
            players[0] = setupPlayer<char>("Connect 4 tic tac toe",board,'X');
            players[1] = setupPlayer<char>("Connect 4 tic tac toe",board,'O');
            GameManager<char> game(board, players);
            game.run();
            delete board;
            for (int i = 0; i < 2; ++i) {
                delete players[i];
            }
            board = nullptr;
            players[0] = nullptr;
            players[1] = nullptr;
        }
        else if(choice == "7"){
            break;
        }
        else {
            cout << "Please choose a valid choice\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

        }



    }
}


int main() {

mainMenu();



    return 0;
}

