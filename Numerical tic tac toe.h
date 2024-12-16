

#ifndef NUMERICAL_TIC_TAC_TOE_H
#define NUMERICAL_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

template <typename T>
class Numerical_Board: public Board<T> {
private:
    vector<int> nums1 = {1, 3, 5, 7, 9};
    vector<int> nums2 = {2, 4, 6 ,8};
    bool found_in_available_nums(int num);
public:
    Numerical_Board();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();
};



template <typename T>
class Numerical_Player : public Player<T> {

public:
    Numerical_Player(string name, T symbol);
    void getmove(int& x, int& y) ;
};

template <typename T>
class Numerical_Random_Player : public RandomPlayer<T>{
public:
    Numerical_Random_Player (T symbol);
    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;



// Constructor for Numerical_Board
template <typename T>
Numerical_Board<T>::Numerical_Board() {
    this->rows = this->columns = 3;
    this->board = reinterpret_cast<int **>(new char *[this->rows]);
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = reinterpret_cast<int *>(new char[this->columns]);
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    
}
template<typename T>
bool Numerical_Board<T>::found_in_available_nums(int num){
    if (this-> n_moves % 2 == 0){ // Player1
        return find(this->nums1.begin(), this->nums1.end(), num) != this->nums1.end();
    }else{
        return find(this->nums2.begin(), this->nums2.end(), num) != this->nums2.end();
    }
}
template<typename T>
bool Numerical_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (y <= this->columns && x <= this->rows -1  && (this->board[x][y] == 0|| mark == 0) && found_in_available_nums(mark)) {
        if (mark == 0){
            this->n_moves--;
            this->board[x][y] = 0;
        }
        else {
            this->n_moves % 2 == 0 ? this->nums1.erase(remove(this->nums1.begin(), this->nums1.end(), mark), this->nums1.end()) : this->nums2.erase(remove(this->nums2.begin(), this->nums2.end(), mark), this->nums2.end());
            this->n_moves++;
            this->board[x][y] = toupper(mark);
        }
        return true;
    }
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Numerical_Board<T>::display_board() {
    cout << "\n-----------------------------";
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
bool Numerical_Board<T>::is_win() {

    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        if ((this->board[i][0] + this->board[i][1] + this->board[i][2] == 15 && this->board[i][0] != 0 && this->board[i][1] != 0 && this->board[i][2] != 0) ||
            (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15 && this->board[0][i] != 0 && this->board[1][i] != 0 && this->board[2][i] != 0)) {
            return true;
        }
    }

    // Check diagonals
    if ((this->board[0][0] + this->board[1][1] + this->board[2][2] == 15 && this->board[0][0] != 0 && this->board[1][1] != 0 && this->board[2][2] != 0) ||
        (this->board[0][2] + this->board[1][1] + this->board[2][0] && this->board[0][2] != 0 && this->board[1][1] != 0 && this->board[2][0] != 0)) {
        return true;
    }


    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Numerical_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Numerical_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Numerical_Player
template <typename T>
Numerical_Player<T>::Numerical_Player(std::string name, T symbol):Player<T>(name, symbol){}

template <typename T>
void Numerical_Player<T>::getmove(int& x, int& y) {
    while(true) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;

        if(cin.fail()){
            cout << "Invalid input. Please enter integers for x and y.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        if (x >= 0 && x <= 2 && y >= 0 && y <= 2) {
            break;
        }

        else{
            cout << "Invalid input. Please enter integers for x and y.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

        }

    }
    while (true) {

        int symb;
        cout << "\n\nPlease enter your number: ";
        cin >> symb;
        if(cin.fail()){
            cout << "Invalid input. Please enter a single character.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores incorrect input
        }
        else if(isdigit(symb)){

            this->symbol = symb;
            break;
        }
    }

}


// Constructor for Numerical_Random_Player
template <typename T>
Numerical_Random_Player<T>::Numerical_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Numerical_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    int randomChar = (rand() % 9) + 1; // numbers from 1 to 9
    this->symbol = randomChar;
}

#endif //NUMERICAL_TIC_TAC_TOE_H
