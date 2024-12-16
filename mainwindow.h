#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "BoardGame_Classes.h"
#include "Pyramid_tic_tac_toe.h"
#include "4X4_tic_tac_toe.h"
#include <QSoundEffect>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void handleMove(int x, int y, char symbol,int btn);
    void handleMove_ult(int x, int y, char symbol);
    void connectMisereButtons();
    void connectPyramidButtons();
    void connect_4x4_first_Buttons();
    void connect_4x4_second_Buttons();
    void get_first_index_4x4(int i, int j , QString symp_str);
    void get_second_index_4x4(int i, int j , QString symp_str);
    void to_next_index_4x4();
    void Four_x_Four_handle_move(int x1 , int y1);
    void Four_x_Four_set(int x1, int y1);

    void connect_ult_Buttons();
    void style_buttons_ult(int x , int y);

    QSoundEffect *mainButtonSound = new QSoundEffect(this);


    QSoundEffect *xTurnSound = new QSoundEffect(this);


    QSoundEffect *oTurnSound = new QSoundEffect(this);

    QSoundEffect *drawSound = new QSoundEffect(this);

    QSoundEffect *winSound = new QSoundEffect(this);


private slots:
    void on_Play_btn_clicked();

    void on_Pyramic_btn_clicked();

    void on_Four_in_row_btn_clicked();

    void on__5x5_tic_tac_toe_btn_clicked();

    void on_word_tic_tac_toe_btn_clicked();

    void on_numerical_tic_tac_toe_btn_clicked();

    void on_misere_tic_tac_toe_btn_clicked();

    void on__4x4_tic_tac_toe_btn_clicked();

    void on_ultimate_tic_tac_toe_btn_clicked();

    void on_misere_0_0_clicked();
    void on_P_1_H_clicked();

    void on_P_1_R_clicked();

    void on_P_2_H_clicked();

    void on_P_2_R_clicked();

    void on_P_1_Ready_clicked();

    void on_P_2_Ready_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    bool p1_done = false;
    bool p2_done = false;
    Player<char> *Players_ptr[2];
    Board<char> *Board_ptr;
    int currentPlayer;
    string player1_name = "";
    string player2_name = "";
    string player1;
    string player2;
    bool ready_p1;
    bool ready_p2;

    int x1;
    int y1;
    int x2;
    int y2;
    string symp;
    bool first = true;

    Board<char> *Board_ptr_ult_0_0;
    Board<char> *Board_ptr_ult_0_1;
    Board<char> *Board_ptr_ult_0_2;
    Board<char> *Board_ptr_ult_1_0;
    Board<char> *Board_ptr_ult_1_1;
    Board<char> *Board_ptr_ult_1_2;
    Board<char> *Board_ptr_ult_2_0;
    Board<char> *Board_ptr_ult_2_1;
    Board<char> *Board_ptr_ult_2_2;
};
#endif // MAINWINDOW_H
