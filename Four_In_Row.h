
#ifndef FOUR_IN_ROW_H
#define FOUR_IN_ROW_H

#include "BoardGame_Classes.h"

template <typename T>
class Four_in_Row_Board: public Board<T> {
public:
    Four_in_Row_Board ();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    bool Row_valid(int x, int y);
};

template <typename T>
class Four_in_Row_Player : public Player<T> {
public:
    Four_in_Row_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Four_in_Row_Random_Player : public RandomPlayer<T>{
public:
    Four_in_Row_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Four_in_Row_Board
template <typename T>
Four_in_Row_Board<T>::Four_in_Row_Board() {
    this->rows = 6;
    this->columns = 7;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Four_in_Row_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)
        && Row_valid(x, y)) {
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

// Display the board and the pieces on it
template <typename T>
void Four_in_Row_Board<T>::display_board() {
    for (int i = this->rows - 1; i >=0 ; --i) {
        cout << "\n| ";
        for (int j = 0; j < this-> columns; ++j) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n--" << string(9*7, '-');
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Four_in_Row_Board<T>::is_win() {
    //Horizontal Checking
    for (int i = 0; i < this  ->rows; ++i) {
        for (int j = 0; j < this->columns - 3; ++j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i][j+1] && this->board[i][j+1] == this->board[i][j+2]
                && this->board[i][j+2] == this->board[i][j+3]){
                return true;
            }
        }
    }

    //Vertical Checking
    for (int i = 0; i < this  ->rows - 3; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i+1][j] && this->board[i+1][j] == this->board[i+2][j]
                && this->board[i+2][j] == this->board[i+3][j]){
                return true;
            }
        }
    }

    // Checking  Diagonals
    // this type of Diagonal (\)
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 4; ++j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i+1][j+1] && this->board[i+1][j+1] == this->board[i+2][j+2]
                && this->board[i+2][j+2] == this->board[i+3][j+3]){
                return true;
            }
        }
    }
    // this type of Diagonal (/)
    for (int i = 0; i < 3; ++i) {
        for (int j = this->columns -1; j >= 3; --j) {
            if (this->board[i][j] != 0 && this->board[i][j] == this->board[i+1][j-1] && this->board[i+1][j-1] == this->board[i+2][j-2]
                && this->board[i+2][j-2] == this->board[i+3][j-3]){
                return true;
            }
        }
    }


    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Four_in_Row_Board<T>::is_draw() {
    return (this->n_moves == 42 && !is_win());
}

template <typename T>
bool Four_in_Row_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Four_in_Row_Player
template <typename T>
Four_in_Row_Player<T>::Four_in_Row_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_in_Row_Player<T>::getmove(int& x, int& y) {
    while(true) {
        cout << "\nPlease enter your move x and y (0 to 6) separated by spaces: ";
        cin >> x >> y;

        if(cin.fail()){
            cout << "Invalid input. Please enter integers for x and y.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (x >= 0 && x <= 5 && y >= 0 && y <= 6) {
            break;
        }

        else{
            cout << "Invalid input. Please enter integers for x and y.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

        }

    }
}

// Constructor for Four_in_Row_Random_Player
template <typename T>
Four_in_Row_Random_Player<T>::Four_in_Row_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 6;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Four_in_Row_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % (this->dimension + 1);
}


template <typename T>
bool Four_in_Row_Board<T>::Row_valid(int x, int y){
    int lower = (x > 0) ? x-1 : 0;
    if (lower < x && this->board[lower][y] == 0){
        return false;
    }
    return true;
}




#endif //FOUR_IN_ROW_H

