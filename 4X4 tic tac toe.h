
#ifndef INC_4X4_TIC_TAC_TOE_4X4_TIC_TAC_TOE_H
#define INC_4X4_TIC_TAC_TOE_4X4_TIC_TAC_TOE_H



#include "BoardGame_Classes.h"

template <typename T>
class Four_X_Four_Board:public Board<T> {


public:
    int new_x{};
    int new_y{};
    Four_X_Four_Board();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void setNewPos(int&new_x1, int& new_y1);

};

template <typename T>
class Four_X_Four_Player : public Player<T> {
public:
    Four_X_Four_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Four_X_Four_Random_Player : public RandomPlayer<T>{
public:
    Four_X_Four_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for Four_X_Four_Board
template <typename T>
Four_X_Four_Board<T>::Four_X_Four_Board() {
    this->rows = this->columns = 4;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            if(i == 0){
                if(j == 0 || j%2 == 0){
                    this->board[i][j] = 'O';
                }
                else{
                    this->board[i][j] = 'X';
                }

            }
            else if(i == 3){
                if(j == 0 || j%2 == 0){
                    this->board[i][j] = 'X';
                }
                else{
                    this->board[i][j] = 'O';
                }

            }
            else {
                this->board[i][j] = 0;
            }
        }
    }
    this->n_moves = 0;
}

template <typename T>
bool Four_X_Four_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid

    int x1,y1;
    cout << "\nPlease enter the new position you want the symbol to go to (0 to 3): ";
    cin >> x1 >> y1;



    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && !(x1 < 0 || x1 >= this->rows || y1 < 0 || y1 >= this->columns) && (this->board[x][y] == mark)) {

        setNewPos(x1,y1);
       if(( (new_x == x+1 && new_y == y)  || (new_x == x-1 && new_y == y) || (new_x == x && new_y == y+1) || (new_x == x && new_y == y-1) )&& this->board[new_x][new_y] == 0 ){
           if(this->board[new_x][new_y] == 0){
               this->board[new_x][new_y] = mark;
               this->board[x][y] = 0;
               this->n_moves++;
               return true;
           }
       }


    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Four_X_Four_Board<T>::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            cout << "(" << i << "," << j << ")";
            cout << setw(2) << this->board[i][j] << " |";
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// Returns true if there is any winner
template <typename T>
bool Four_X_Four_Board<T>::is_win() {

    // Check rows
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) ||
            (this->board[i][1] == this->board[i][2] && this->board[i][2] == this->board[i][3] && this->board[i][1] != 0)) {
            return true;
        }
    }
    // Check columns
    for (int i = 0; i < this->columns; i++) {
        if ((this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) ||
            (this->board[1][i] == this->board[2][i] && this->board[2][i] == this->board[3][i] && this->board[1][i] != 0)) {
            return true;
        }
    }

    // Check diagonals

    // Top-left to bottom-right
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (this->board[i][j] == this->board[i + 1][j + 1] &&
                this->board[i + 1][j + 1] == this->board[i + 2][j + 2] &&
                this->board[i + 2][j + 2] != 0) {
                return true;
            }
        }
    }

    // Top-right to bottom-left
    for (int i = 0; i < 2; ++i) {
        for (int j = 2; j < 4; ++j) {
            if (this->board[i][j] == this->board[i + 1][j - 1] &&
                this->board[i + 1][j - 1] == this->board[i + 2][j - 2] &&
                this->board[i + 2][j - 2] != 0) {
                return true;
            }
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Four_X_Four_Board<T>::is_draw() {
    return (this->n_moves == 20 && !is_win());
}

template <typename T>
bool Four_X_Four_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

template <typename T>
void Four_X_Four_Board<T>::setNewPos(int &new_x1, int &new_y1) {
    this->new_x = new_x1;
    this->new_y = new_y1;
}

//--------------------------------------

// Constructor for Four_X_Four_Player
template <typename T>
Four_X_Four_Player<T>::Four_X_Four_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Four_X_Four_Player<T>::getmove(int& x, int& y) {
    cout << "\nPlease enter your move x and y (0 to 3) separated by spaces: ";
    cin >> x >> y;


}

// Constructor for Four_X_Four_Random_Player
template <typename T>
Four_X_Four_Random_Player<T>::Four_X_Four_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 4;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Four_X_Four_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}





#endif //INC_4X4_TIC_TAC_TOE_4X4_TIC_TAC_TOE_H
