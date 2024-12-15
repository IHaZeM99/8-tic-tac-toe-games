
//
// Created by Hazem Ahmed on 12/13/2024.
//

#ifndef X_0_INVERSE_TIC_TAC_TOE_H
#define X_0_INVERSE_TIC_TAC_TOE_H
#include "BoardGame_Classes.h"
bool ISWIN = false;
int COUNT = 0;
bool END = false;


template <typename T>
class Inverse_X_O_Board:public Board<T> {
private:
    int game_over;
public:
    Inverse_X_O_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};

template <typename T>
class Inverse_X_O_Player : public Player<T> {
public:
    Inverse_X_O_Player (string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Inverse_X_O_Random_Player : public RandomPlayer<T>{
public:
    Inverse_X_O_Random_Player (T symbol);
    void getmove(int &x, int &y) ;
};





//--------------------------------------- IMPLEMENTATION

#include <iostream>
#include <iomanip>
#include <cctype>  // for toupper()

using namespace std;

// Constructor for X_O_Board
template <typename T>
Inverse_X_O_Board<T>::Inverse_X_O_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    game_over = 0;
    ISWIN = false;
    COUNT = 0;
    END = false;
}

template <typename T>
bool Inverse_X_O_Board<T>::update_board(int x, int y, T mark) {
    if(!END) {
        if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0 || mark == 0)) {
            if (mark == 0) {
                this->n_moves--;
                this->board[x][y] = 0;
            } else {
                this->n_moves++;
                this->board[x][y] = toupper(mark);
            }

            return true;
        }
        return false;
    }
    return true;
}

// Display the board and the pieces on it
template <typename T>
void Inverse_X_O_Board<T>::display_board() {
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
bool Inverse_X_O_Board<T>::is_win() {
    //Check rows and columns
    for (int i = 0; i < this->rows; i++) {
        // Check horizontal win
        if (this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] != 0) {
            //this->n_moves++;
            ISWIN = true;

            if(this->board[i][0] == 'O'&& game_over == 1){
                game_over = 0;
                END = true;
                return false;
            }

            if (COUNT >= 1) {
                return true;
            }
            END = true;
            COUNT++;
        }


        if (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] != 0) {
            ISWIN = true;


            if (this->board[0][i] == 'O' && game_over == 1) {
                game_over = 0;
                END = true;
                return false;
            }

            if (COUNT >= 1) {
                return true;
            }
            END = true;
            COUNT++;
        }
    }

    // Check diagonal from top-left to bottom-right
    if (this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] != 0) {
        //this->n_moves++;
        ISWIN = true;

        if(this->board[0][0] == 'O'&& game_over == 1){
            game_over = 0;
            END = true;
            return false;
        }

        if (COUNT >= 1) {
            END = true;
            return true;
        }
        COUNT++;
        END = true;
    }

    // Check diagonal from top-right to bottom-left
    if (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] != 0) {
        //this->n_moves++;
        ISWIN = true;

        if(this->board[0][2] == 'O' && game_over == 1){
            game_over = 0;
            END = true;
            return false;
        }

        if (COUNT >= 1) {
            END = true;
            return true;
        }
        COUNT++;
        END = true;
    }
    game_over = 0;
    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Inverse_X_O_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Inverse_X_O_Board<T>::game_is_over() {
    game_over = 1;
    return is_win() || is_draw();
//    while(ISWIN) {
//
//        return is_win() || is_draw();
//    }
}

//--------------------------------------

// Constructor for X_O_Player
template <typename T>
Inverse_X_O_Player<T>::Inverse_X_O_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void Inverse_X_O_Player<T>::getmove(int& x, int& y) {
    if (END){
        x = rand() % 3;  // Random number between 0 and 2
        y = rand() % 3;
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
    cin >> x >> y;

}

// Constructor for X_O_Random_Player
template <typename T>
Inverse_X_O_Random_Player<T>::Inverse_X_O_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Inverse_X_O_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}







#endif //X_0_INVERSE_TIC_TAC_TOE_H
