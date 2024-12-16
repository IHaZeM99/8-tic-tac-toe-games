

#ifndef PYRAMID_TIC_TAC_TOE_PYRAMID_TIC_TAC_TOE_H
#define PYRAMID_TIC_TAC_TOE_PYRAMID_TIC_TAC_TOE_H


#include "BoardGame_Classes.h"

template <typename T>
class Pyramid_Board:public Board<T> {

public:
    Pyramid_Board();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Pyramid_Player : public Player<T> {
public:
    Pyramid_Player(string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Pyramid_Random_Player : public RandomPlayer<T>{
public:
    Pyramid_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;






// Constructor for X_O_Board
template <typename T>
Pyramid_Board<T>::Pyramid_Board() {
    this->rows = 5;  // Maximum number of rows
    this->columns = 5;  // Maximum number of columns
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char [this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;  // Initialize all cells to 0
        }
    }
    this->n_moves = 0;
}



template <typename T>
bool Pyramid_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if ((this->board[x][y] == 0|| mark == 0)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }

        return true;
    }
    return false;
}

// Returns true if there is any winner
template <typename T>
bool Pyramid_Board<T>::is_win() {

    if((this->board[1][1] == this->board[1][2] && this->board[1][2] == this->board[1][3]) && (  this->board[1][2] != 0)){
        return true;
    }
    if((this->board[0][2] == this->board[1][2] && this->board[1][2] == this->board[2][2]) && (this->board[1][2] != 0)){
        return true;
    }
    else {
        int cnt = 0;
        for (int i = 1; i < this->columns; ++i) {
            if (this->board[2][i] == this->board[2][i - 1] && (  this->board[2][i] != 0)) {
                cnt++;
            } else {
                cnt = 0;
            }
            if (cnt == 2) {
                return true;
            }
        }
    }

    if((this->board[1][1] == this->board[0][2] && this->board[1][1] == this->board[2][0] && (  this->board[1][1] != 0))
    || ((this->board[1][3] == this->board[0][2] && this->board[1][3] == this->board[2][4] && ( this->board[1][3] != 0)))){
        return true;
    }

    return false;
}



// Return true if 9 moves are done and no winner
template <typename T>
bool Pyramid_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}


template <typename T>
bool Pyramid_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Display the board and the pieces on it
template <typename T>
void Pyramid_Board<T>::display_board() {


    cout << "\n                     || (0,2) " << this->board[0][2] << " || ";
    cout << "\n------------------------------------------------------------\n";
    cout << "           ";
    for (int i = 1; i < 4; i++) {
        cout << "| ";

            cout << "(" << 1 << "," << i << ")";
            cout << setw(2) << this->board[1][i] << " |";

    }

    cout << "\n------------------------------------------------------------\n";

    for (int i = 0; i < 5; i++) {
        cout << "| ";

        cout << "(" << 2 << "," << i << ")";
        cout << setw(2) << this->board[2][i] << " |";

    }

    cout << "\n------------------------------------------------------------\n";

    cout << endl;
}

//--------------------------------------


// Constructor for Pyramid_Player
template <typename T>
Pyramid_Player<T>::Pyramid_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Pyramid_Player<T>::getmove(int& x, int& y) {
    while(true) {
        cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
        cin >> x >> y;

        if(cin.fail()){
            cout << "Invalid input. Please enter integers for x and y.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if((x == 0 && y != 2) || (x == 1 && (y == 0 || y == 4))){
            cout << "Invalid input. Please enter integers for x and y.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';
        }
        else if (x >= 0 && x <= 4 && y >= 0 && y <= 4 ) {
            break;
        }
        else{
            cout << "Invalid input. Please enter integers for x and y.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

        }

    }
}

// Constructor for X_O_Random_Player
template <typename T>
Pyramid_Random_Player<T>::Pyramid_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Pyramid_Random_Player<T>::getmove(int& x, int& y) {
    static vector<pair<int, int>> valid_positions = {{0, 2}, {1, 1}, {1, 2}, {1, 3},
                                                     {2, 0}, {2, 1}, {2, 2}, {2, 3}, {2, 4}};
    int idx = rand() % valid_positions.size(); // Pick a random valid position
    x = valid_positions[idx].first;
    y = valid_positions[idx].second;
}




#endif //PYRAMID_TIC_TAC_TOE_PYRAMID_TIC_TAC_TOE_H
