

#ifndef WORD_TIC_TAC_TOE_WORD_TIC_TAC_TOE_H
#define WORD_TIC_TAC_TOE_WORD_TIC_TAC_TOE_H

#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

template <typename T>
class Word_Board:public Board<T> {
private:
    map<string, int> valid_words2;
    void loadProgramFile();
public:
    Word_Board();
    bool update_board (int x , int y , T mark);
    void display_board () ;
    bool is_win() ;
    bool is_draw();
    bool game_is_over();

};



template <typename T>
class Word_Player : public Player<T> {

public:
    Word_Player(string name, T symbol);
    void getmove(int& x, int& y) ;

};

template <typename T>
class Word_Random_Player : public RandomPlayer<T>{
public:
    Word_Random_Player (T symbol);
    void getmove(int &x, int &y) ;

};





//--------------------------------------- IMPLEMENTATION

#include <bits/stdc++.h>
using namespace std;



// Constructor for Word_Board
template <typename T>
Word_Board<T>::Word_Board() {
    this->rows = this->columns = 3;
    this->board = new char*[this->rows];
    for (int i = 0; i < this->rows; i++) {
        this->board[i] = new char[this->columns];
        for (int j = 0; j < this->columns; j++) {
            this->board[i][j] = 0;
        }
    }
    this->n_moves = 0;
    loadProgramFile();
}





template <typename T>
void Word_Board<T>::loadProgramFile() {

    string file_path = "dic.txt";
    ifstream file(file_path);

    if (!file) {
        cerr << "Error: Unable to open the file for reading: " << file_path.c_str() << endl;
        return;
    }

    string line;
    while (file >> line) {
        valid_words2[line] = 1;
    }


    file.close();
}


template<typename T>
bool Word_Board<T>::update_board(int x, int y, T mark) {
    // Only update if move is valid
    if (!(x < 0 || x >= this->rows || y < 0 || y >= this->columns) && (this->board[x][y] == 0|| mark == 0)) {
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
    cout << "Please enter a valid position\n";
    return false;
}

// Display the board and the pieces on it
template <typename T>
void Word_Board<T>::display_board() {
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
bool Word_Board<T>::is_win() {

    // Check rows from left to right and vice versa
    for (int i = 0; i < this->rows; i++) {
        if(!isdigit(this->board[i][0]) && !isdigit(this->board[i][1]) && !isdigit(this->board[i][2])) {
            string word;
            string word_2;
            word += this->board[i][0];
            word += this->board[i][1];
            word += this->board[i][2];

            word_2 += this->board[i][2];
            word_2 += this->board[i][1];
            word_2 += this->board[i][0];
            if (word.length() == 3) {
                if (valid_words2[word]) {
                    return true;
                }
            }
            if (word_2.length() == 3) {
                if (valid_words2[word_2]) {
                    return true;
                }
            }
        }

    }




    // Check columns from top to bottom and vice versa
    for (int i = 0; i < this->columns; i++) {
        if(!isdigit(this->board[0][i]) && !isdigit(this->board[1][i]) && !isdigit(this->board[2][i])) {
            string word;
            string word_2;
            word += this->board[0][i];
            word += this->board[1][i];
            word += this->board[2][i];

            word_2 += this->board[2][i];
            word_2 += this->board[1][i];
            word_2 += this->board[0][i];

            if (word.length() == 3) {
                if (valid_words2[word]) {
                    return true;
                }
            }
            if (word_2.length() == 3) {
                if (valid_words2[word_2]) {
                    return true;
                }
            }
        }
    }



    // Check diagonals from top left to bot right
    string word;
    word += this->board[0][0];
    word += this->board[1][1];
    word += this->board[2][2];
    if (word.length() == 3) {
        if (valid_words2[word]) {
            return true;
        }
    }


    // Check diagonals from bot left to top right
    string word2;
    word2 += this->board[2][0];
    word2 += this->board[1][1];
    word2 += this->board[0][2];
    if (word2.length() == 3) {
        if (valid_words2[word2]) {
            return true;
        }
    }

    // Check diagonals from bot right to top left
    string word3;
    word3 += this->board[2][2];
    word3 += this->board[1][1];
    word3 += this->board[0][0];
    if(word3.length() == 3){
        if(valid_words2[word3]){
            return true;
        }
    }

    // Check diagonals from top right to bot left
    string word4;
    word4 += this->board[0][2];
    word4 += this->board[1][1];
    word4 += this->board[2][0];
    if(word4.length() == 3){
        if(valid_words2[word4]){
            return true;
        }
    }

    return false;
}

// Return true if 9 moves are done and no winner
template <typename T>
bool Word_Board<T>::is_draw() {
    return (this->n_moves == 9 && !is_win());
}

template <typename T>
bool Word_Board<T>::game_is_over() {
    return is_win() || is_draw();
}

//--------------------------------------

// Constructor for Word_Player
template <typename T>
Word_Player<T>::Word_Player(std::string name, T symbol):Player<T>(name,symbol) {}

template <typename T>
void Word_Player<T>::getmove(int& x, int& y) {

    while(true) {
        cout << "\nPlease enter your move x and y (0 to 2) separated by spaces: ";
        cin >> x >> y;

        if(cin.fail()){
            cout << "Invalid input. Please enter integers for x and y.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
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

        char symb;
        cout << "\n\nPlease enter your letter: ";
        cin >> symb;
        if(cin.fail()){
            cout << "Invalid input. Please enter a single character.\n";
            cout << setfill('-') << setw(37) << "" <<'\n';

            cin.clear(); // Clears the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignores incorrect input
        }
        else if(isalpha(symb)){

             this->symbol = toupper(symb);
            break;
        }
    }
}



// Constructor for Word_Random_Player
template <typename T>
Word_Random_Player<T>::Word_Random_Player(T symbol) : RandomPlayer<T>(symbol) {
    this->dimension = 3;
    this->name = "Random Computer Player";
    srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
}

template <typename T>
void Word_Random_Player<T>::getmove(int& x, int& y) {
    x = rand() % this->dimension;  // Random number between 0 and 2
    y = rand() % this->dimension;
    char randomChar = 'A' + std::rand() % 26; // 26 letters in the alphabet
    this->symbol = randomChar;
}



#endif //WORD_TIC_TAC_TOE_WORD_TIC_TAC_TOE_H
