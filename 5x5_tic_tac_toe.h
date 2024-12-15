#ifndef X_0_5X5_TIC_TAC_TOE_H
#define X_0_5X5_TIC_TAC_TOE_H

#include "BoardGame_Classes.h"
bool END_5x5 = false;

template <typename T>
class _5x5_Board:public Board<T> {
private:
    int xCount;
    int oCount;
    bool flag;
public:
    _5x5_Board();
    bool update_board (int x , int y , T symbol);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
    void counting();

};

template <typename T>
class _5x5_Player : public Player<T> {
private:
    int count;
public:
    _5x5_Player(string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class _5x5_Random_Player : public RandomPlayer<T>{
private:
    int count;
public:
    _5x5_Random_Player(T symbol);
    void getmove(int &x, int &y) ;
};


//--------------------------------------- IMPLEMENTATION----------------------//

#include <bits/stdc++.h>
using namespace std;

template <typename T>
_5x5_Board<T>::_5x5_Board() {
    xCount = 0;
    oCount = 0;
    this->rows = 5;
    this->columns = 5;
    this->board = new char *[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char [this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    flag = false;
    END_5x5 = false;
}

template <typename T>
bool _5x5_Board<T>::update_board(int x, int y, T mark) {
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
template <typename T>
void _5x5_Board<T>::counting() {
    // Check rows
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == 'X' && this->board[i][j + 1] == 'X' && this->board[i][j + 2] == 'X') {
                xCount++;
            }
            if (this->board[i][j] == 'O' && this->board[i][j + 1] == 'O' && this->board[i][j + 2] == 'O') {
                oCount++;
            }
        }
    }

    // Check columns
    for (int j = 0; j < this->columns; j++) {
        for (int i = 0; i <= this->rows - 3; i++) {
            if (this->board[i][j] == 'X' && this->board[i + 1][j] == 'X' && this->board[i + 2][j] == 'X') {
                xCount++;
            }
            if (this->board[i][j] == 'O' && this->board[i + 1][j] == 'O' && this->board[i + 2][j] == 'O') {
                oCount++;
            }
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 0; j <= this->columns - 3; j++) {
            if (this->board[i][j] == 'X' && this->board[i + 1][j + 1] == 'X' && this->board[i + 2][j + 2] == 'X') {
                xCount++;
            }
            if (this->board[i][j] == 'O' && this->board[i + 1][j + 1] == 'O' && this->board[i + 2][j + 2] == 'O') {
                oCount++;
            }
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= this->rows - 3; i++) {
        for (int j = 2; j < this->columns; j++) {
            if (this->board[i][j] == 'X' && this->board[i + 1][j - 1] == 'X' && this->board[i + 2][j - 2] == 'X') {
                xCount++;
            }
            if (this->board[i][j] == 'O' && this->board[i + 1][j - 1] == 'O' && this->board[i + 2][j - 2] == 'O') {
                oCount++;
            }
        }
    }
}


template <typename T>
bool _5x5_Board<T>::is_win() {
    if (this->n_moves == 24) {
        if (!flag) {
            counting();                            ///////////////////////////////////////
            flag = true;
        }
        if (oCount > xCount){
            //cout << "qDebug"<< xCount <<oCount << endl;
            return true;
        }
        END_5x5 = true;
        //return (xCount > 0 || oCount > 0);
    }
    if (this->n_moves == 25 && xCount>oCount){
        return true;
    }
    return false;
}

template <typename T>
bool _5x5_Board<T>::is_draw() {
    return (this->n_moves == 25 && xCount == oCount);
}

template <typename T>
bool _5x5_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

// Display the board and the pieces on it
template <typename T>
void _5x5_Board<T>::display_board() {
    if (!END_5x5) {
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
}

//--------------------------------------

template <typename T>
_5x5_Player<T>::_5x5_Player(string name, T symbol) : Player<T>(name, symbol) {}

template <typename T>
void _5x5_Player<T>::getmove(int& x, int& y) {
    if (END_5x5){
        x = rand() % 5;  // Random number between 0 and 2
        y = rand() % 5;
        return;
    }
    cout << "\nPlease enter your move x and y (0 to 4) separated by spaces: ";
    cin >> x >> y;
}

//--------------------------------------
template <typename T>
_5x5_Random_Player<T>::_5x5_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 5;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void _5x5_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
}






#endif //X_0_5X5_TIC_TAC_TOE_H
