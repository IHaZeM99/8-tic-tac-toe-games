#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "BoardGame_Classes.h"
#include "Pyramid_tic_tac_toe.h"
#include "4X4_tic_tac_toe.h"
#include "3x3X_O.h"
#include <QMessageBox>
#include <qpixmap>
#include <QSoundEffect>


QString regular_btn_style = "QPushButton{    color: rgb(255, 255, 255);font: 14pt ""MS Reference Sans Serif"";background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 #4682B4, stop:1 #5F9EA0);border-radius: 5px;}QPushButton:hover {    background-color: #5F9EA0;}";

QString X_btn_Style = "background-color: #FF4500;    color: white; font: bold; border-radius: 5px;font: 14pt ""MS Reference Sans Serif"";";

QString O_btn_Style = "background-color: #32CD32;    color: white; font: bold; border-radius: 5px;font: 14pt ""MS Reference Sans Serif"";";

QString Tie_btn_Style = "background-color: #4f524f;    color: white; font: bold; border-radius: 5px;font: 14pt ""MS Reference Sans Serif"";";

QString X_label_style = "color: #FF4500;     font: bold; border-radius: 5px;font: 14pt ""MS Reference Sans Serif"";";

QString O_label_style = "color: #0d540d;     font: bold; border-radius: 5px;font: 14pt ""MS Reference Sans Serif"";";



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , Board_ptr(nullptr)
{
    ui->setupUi(this);
    Players_ptr[0] = nullptr;
    Players_ptr[1] = nullptr;
    ui->gridLayoutWidget_19->setGeometry(ui->gridLayoutWidget_16->geometry());
    ui->gridLayoutWidget_19->hide();
    ui->player_turn->hide();

    ui->P_1_A->hide();
    ui->P_2_A->hide();
    ui->human_p1_lbl->hide();
    ui->human_p2_lbl->hide();
    ui->AI_p1_lbl->hide();
    ui->AI_p2_lbl->hide();
    ui->random_p1_lbl->hide();
    ui->random_p2_lbl->hide();
    ui->P1_line->setText("Player 1");
    ui->P2_line->setText("Player 2");
    ui->info_btn->hide();
    ui->logo_main->show();
    QPixmap pix(":/Resource/img/logo_main.png");
    ui->logo_main->setPixmap(pix);

    mainButtonSound->setSource(QUrl::fromLocalFile(":/sound/sound/sound_main.wav"));
    mainButtonSound->setVolume(0.5);

    xTurnSound->setSource(QUrl::fromLocalFile(":/sound/sound/sound_X.wav"));
    xTurnSound->setVolume(0.5);

    oTurnSound->setSource(QUrl::fromLocalFile(":/sound/sound/sound_O.wav"));
    oTurnSound->setVolume(0.5);

    drawSound->setSource(QUrl::fromLocalFile(":/sound/sound/draw_sound_wav.wav"));
    drawSound->setVolume(0.3);

    winSound->setSource(QUrl::fromLocalFile(":/sound/sound/win.wav"));
    winSound->setVolume(0.3);

}

MainWindow::~MainWindow()
{
    delete ui;

    if (Board_ptr) {
        delete Board_ptr;
    }

    for (int i = 0; i < 2; ++i) {
        if (Players_ptr[i]) {
            delete Players_ptr[i];
        }
    }
}



void MainWindow::handleMove(int x, int y, char symbol,int btn) {
    if (Board_ptr->update_board(x, y, symbol)) {
        qDebug () <<"check";
        QString buttonName;
        if(btn == 3){
            buttonName = QString("pyramic_%1_%2").arg(x).arg(y);
        }
        if(btn == 8){
            buttonName = QString("misere_%1_%2").arg(x).arg(y);
        }
        QPushButton* button = findChild<QPushButton*>(buttonName);
        qDebug() << buttonName;                                                     //for debuging
        if (button) {
            button->setText(QString(QChar(Players_ptr[currentPlayer]->getsymbol())));
            button->setEnabled(false);
            //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            if(Players_ptr[currentPlayer]->getsymbol() == 'X'){
                button->setStyleSheet(X_btn_Style);
            }else if (Players_ptr[currentPlayer]->getsymbol() == 'O'){
                button->setStyleSheet(O_btn_Style);
            }
        }

        if (Board_ptr->is_win()) {
            QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(Players_ptr[currentPlayer]->getname().c_str()));
            if(btn == 3){
                ui->pyramic_0_2->setText("");
                ui->pyramic_0_2->setEnabled(true);
                ui->pyramic_0_2->setStyleSheet(regular_btn_style);
                for (int var = 1; var < 4; ++var) {
                    buttonName = QString("pyramic_%1_%2").arg(1).arg(var);
                    button = findChild<QPushButton*>(buttonName);
                    if (button) {
                        button->setText("");
                        button->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button->setStyleSheet(regular_btn_style);
                    }
                }
                for (int var = 0; var < 5; ++var) {
                    buttonName = QString("pyramic_%1_%2").arg(2).arg(var);
                    button = findChild<QPushButton*>(buttonName);
                    if (button) {
                        button->setText("");
                        button->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button->setStyleSheet(regular_btn_style);
                    }
                }
            }
            delete Board_ptr;
            for(int i = 0 ; i < 2 ; i++){
                delete Players_ptr[i];
            }
            return;
        }

        if (Board_ptr->is_draw()) {
            QMessageBox::information(this, "Game Over", "It's a draw!");
            if(btn == 3){
                ui->pyramic_0_2->setText("");
                ui->pyramic_0_2->setEnabled(true);
                button->setStyleSheet(regular_btn_style);
                for (int var = 1; var < 4; ++var) {
                    buttonName = QString("pyramic_%1_%2").arg(1).arg(var);
                    button = findChild<QPushButton*>(buttonName);
                    if (button) {
                        button->setText("");
                        button->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button->setStyleSheet(regular_btn_style);
                    }
                }
                for (int var = 0; var < 5; ++var) {
                    buttonName = QString("pyramic_%1_%2").arg(2).arg(var);
                    button = findChild<QPushButton*>(buttonName);
                    if (button) {
                        button->setText("");
                        button->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button->setStyleSheet(regular_btn_style);
                    }
                }
            }
            delete Board_ptr;
            for(int i = 0 ; i < 2 ; i++){
                delete Players_ptr[i];
            }
            return;
        }

        currentPlayer = (currentPlayer + 1) % 2; // Switch players
    } else {
        QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
    }
}
void MainWindow::Four_x_Four_handle_move(int x1 , int y1){
    // Board_ptr->s     /////////////////////////////////////////////////////////////////
    // if (Board_ptr->update_board(x, y, symbol))
}

///////////////////////////////////ultimate/////////////////////

void MainWindow::style_buttons_ult(int x , int y){
    QString buttonName = QString("ultimate_%1_%2").arg(x).arg(y);
    QPushButton* button = findChild<QPushButton*>(buttonName);
    if(button){
        button->setText(QString(QChar(Players_ptr[currentPlayer]->getsymbol())));
        button->setEnabled(false);
        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        if(Players_ptr[currentPlayer]->getsymbol() == 'X'){
            button->setStyleSheet(X_btn_Style);
        }else if (Players_ptr[currentPlayer]->getsymbol() == 'O'){
            button->setStyleSheet(O_btn_Style);
        }
        //currentPlayer = (currentPlayer + 1) % 2; // Switch players
    }
}

void MainWindow::handleMove_ult(int x, int y , char symbol){
    if(currentPlayer == 0){
        xTurnSound->play();
    }else{
        oTurnSound->play();
    }
    ui->player_turn->show();
    if(x < 3 && y < 3){                                      //0_0
        if (Board_ptr_ult_0_0->update_board(x, y, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_0_0->is_win()){
                ui->ultimate_big_0_0->show();
                ui->ultimate_big_0_0->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_0_0->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_0_0->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(0, 0, symbol);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_0_0->is_draw()){
                ui->ultimate_big_0_0->show();
                ui->ultimate_big_0_0->setText(QString("Tie"));
                ui->ultimate_big_0_0->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(0,0,'T');
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }
    else if(x < 6 && y < 3){                                       //1_0
        if (Board_ptr_ult_1_0->update_board(x-3, y, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_1_0->is_win()){
                ui->ultimate_big_1_0->show();
                ui->ultimate_big_1_0->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_1_0->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_1_0->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(1, 0, symbol);
                for (int i = 3; i < 6; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_1_0->is_draw()){
                ui->ultimate_big_1_0->show();
                ui->ultimate_big_1_0->setText(QString("Tie"));
                ui->ultimate_big_1_0->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(1,0,'T');
                for (int i = 3; i < 6; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if(x < 9 && y < 3){                               //2_0
        if (Board_ptr_ult_2_0->update_board(x-6, y, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_2_0->is_win()){
                ui->ultimate_big_2_0->show();
                ui->ultimate_big_2_0->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_2_0->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_2_0->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(2, 0, symbol);
                for (int i = 6; i < 9; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_2_0->is_draw()){
                ui->ultimate_big_2_0->show();
                ui->ultimate_big_2_0->setText(QString("Tie"));
                ui->ultimate_big_2_0->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(2,0,'T');
                for (int i = 6; i < 9; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if(x < 3 && y < 6){                                  //0_1
        if (Board_ptr_ult_0_1->update_board(x, y-3, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_0_1->is_win()){
                ui->ultimate_big_0_1->show();
                ui->ultimate_big_0_1->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_0_1->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_0_1->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(0, 1, symbol);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_0_1->is_draw()){
                ui->ultimate_big_0_1->show();
                ui->ultimate_big_0_1->setText(QString("Tie"));
                ui->ultimate_big_0_1->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(0,1,'T');
                for (int i = 0; i < 3; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if (x < 6 && y < 6){                                 //1_1
        if (Board_ptr_ult_1_1->update_board(x-3, y-3, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_1_1->is_win()){
                ui->ultimate_big_1_1->show();
                ui->ultimate_big_1_1->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_1_1->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_1_1->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(1, 1, symbol);
                for (int i = 3; i < 6; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_1_1->is_draw()){
                ui->ultimate_big_1_1->show();
                ui->ultimate_big_1_1->setText(QString("Tie"));
                ui->ultimate_big_1_1->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(1,1,'T');
                for (int i = 3; i < 6; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if(x < 9 && y < 6){                                     //2_1
        if (Board_ptr_ult_2_1->update_board(x-6, y-3, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_2_1->is_win()){
                ui->ultimate_big_2_1->show();
                ui->ultimate_big_2_1->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_2_1->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_2_1->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(2, 1, symbol);
                for (int i = 6; i < 9; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_2_1->is_draw()){
                ui->ultimate_big_2_1->show();
                ui->ultimate_big_2_1->setText(QString("Tie"));
                ui->ultimate_big_2_1->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(2,1,'T');
                for (int i = 6; i < 9; ++i) {
                    for (int j = 3; j < 6; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if (x < 3 && y < 9){                                  //0_2
        if (Board_ptr_ult_0_2->update_board(x, y-6, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_0_2->is_win()){
                ui->ultimate_big_0_2->show();
                ui->ultimate_big_0_2->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_0_2->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_0_2->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(0, 2, symbol);
                for (int i = 0; i < 3; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_0_2->is_draw()){
                ui->ultimate_big_0_2->show();
                ui->ultimate_big_0_2->setText(QString("Tie"));
                ui->ultimate_big_0_2->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(0,2,'T');
                for (int i = 0; i < 3; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if(x < 6 && y <9){                                                 //1_2
        if (Board_ptr_ult_1_2->update_board(x-3, y-6, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_1_2->is_win()){
                ui->ultimate_big_1_2->show();
                ui->ultimate_big_1_2->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_1_2->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_1_2->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(1, 2, symbol);
                for (int i = 3; i < 6; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_1_2->is_draw()){
                ui->ultimate_big_1_2->show();
                ui->ultimate_big_1_2->setText(QString("Tie"));
                ui->ultimate_big_1_2->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(1,2,'T');
                for (int i = 3; i < 6; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }else if(x < 9 && y < 9){                                               //2_2
        if (Board_ptr_ult_2_2->update_board(x-6, y-6, symbol)){
            style_buttons_ult(x,y);
            if(Board_ptr_ult_2_2->is_win()){
                ui->ultimate_big_2_2->show();
                ui->ultimate_big_2_2->setText(QString(symbol));
                if(symbol == 'X'){
                    ui->ultimate_big_2_2->setStyleSheet(X_btn_Style);
                }else if (symbol == 'O'){
                    ui->ultimate_big_2_2->setStyleSheet(O_btn_Style);
                }
                Board_ptr->update_board(2, 2, symbol);
                for (int i = 6; i < 9; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString(symbol));
                        }
                    }
                }
            }
            if(Board_ptr_ult_2_2->is_draw()){
                ui->ultimate_big_2_2->show();
                ui->ultimate_big_2_2->setText(QString("Tie"));
                ui->ultimate_big_2_2->setStyleSheet(Tie_btn_Style);
                Board_ptr->update_board(2,2,'T');
                for (int i = 6; i < 9; ++i) {
                    for (int j = 6; j < 9; ++j) {
                        QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                        QPushButton* button = findChild<QPushButton*>(buttonName);
                        if(button){
                            button->setText(QString('T'));
                        }
                    }
                }
            }

        }else{
            QMessageBox::warning(this, "Invalid Move", "This move is not valid!");
        }
    }

    if (Board_ptr->is_win()) {
        winSound->play();
        QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(Players_ptr[currentPlayer]->getname().c_str()));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                qDebug() << buttonName;
                if (button) {
                    button->setText("");
                    button->setEnabled(true);
                    //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    button->setStyleSheet(regular_btn_style);
                }
            }
        }
        ui->ultimate_big_0_0->hide();
        ui->ultimate_big_1_0->hide();
        ui->ultimate_big_2_0->hide();
        ui->ultimate_big_0_1->hide();
        ui->ultimate_big_1_1->hide();
        ui->ultimate_big_2_1->hide();
        ui->ultimate_big_0_2->hide();
        ui->ultimate_big_1_2->hide();
        ui->ultimate_big_2_2->hide();

        // if (Board_ptr) {
        //     delete Board_ptr;
        //     Board_ptr = nullptr;
        //     if (Board_ptr_ult_0_0){
        //         delete Board_ptr_ult_0_0;
        //         Board_ptr_ult_0_0 = nullptr;
        //         delete Board_ptr_ult_0_1;
        //         Board_ptr_ult_0_1 = nullptr;
        //         delete Board_ptr_ult_0_2;
        //         Board_ptr_ult_0_2 = nullptr;
        //         delete Board_ptr_ult_1_0;
        //         Board_ptr_ult_1_0 = nullptr;
        //         delete Board_ptr_ult_1_1;
        //         Board_ptr_ult_1_1 = nullptr;
        //         delete Board_ptr_ult_1_2;
        //         Board_ptr_ult_1_2 = nullptr;
        //         delete Board_ptr_ult_2_0;
        //         Board_ptr_ult_2_0 = nullptr;
        //         delete Board_ptr_ult_2_1;
        //         Board_ptr_ult_2_1 = nullptr;
        //         delete Board_ptr_ult_2_2;
        //         Board_ptr_ult_2_2 = nullptr;
        //     }
        // }
        // for (int i = 0; i < 2; ++i) {
        //     if (Players_ptr[i]) {
        //         delete Players_ptr[i];
        //         Players_ptr[i] = nullptr;
        //     }
        // }
        ui->stackedWidget->setCurrentIndex(1);
        ui->player_turn->hide();
        return;
    }
    if (Board_ptr->is_draw()) {
        drawSound->play();
        QMessageBox::information(this, "Game Over", "It's a draw!");
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                qDebug() << buttonName;
                if (button) {
                    button->setText("");
                    button->setEnabled(true);
                    //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    button->setStyleSheet(regular_btn_style);
                }
            }
        }
        ui->ultimate_big_0_0->hide();
        ui->ultimate_big_1_0->hide();
        ui->ultimate_big_2_0->hide();
        ui->ultimate_big_0_1->hide();
        ui->ultimate_big_1_1->hide();
        ui->ultimate_big_2_1->hide();
        ui->ultimate_big_0_2->hide();
        ui->ultimate_big_1_2->hide();
        ui->ultimate_big_2_2->hide();
        ui->player_turn->hide();

        // delete Board_ptr;
        // delete Board_ptr_ult_0_0;
        // delete Board_ptr_ult_0_1;
        // delete Board_ptr_ult_0_2;
        // delete Board_ptr_ult_1_0;
        // delete Board_ptr_ult_1_1;
        // delete Board_ptr_ult_1_2;
        // delete Board_ptr_ult_2_0;
        // delete Board_ptr_ult_2_1;
        // delete Board_ptr_ult_2_2;
        // for(int i = 0 ; i < 2 ; i++){
        //     delete Players_ptr[i];
        // }
        ui->stackedWidget->setCurrentIndex(1);
        ui->player_turn->hide();
        return;
    }

    currentPlayer = (currentPlayer + 1) % 2; // Switch players
    QString PlayerName = QString("%1_turn").arg(QString::fromStdString(Players_ptr[currentPlayer]->getname()));
    ui->player_turn->setText(PlayerName);
    if(currentPlayer == 0){
        ui->player_turn->setStyleSheet(X_label_style);
    }else{
        ui->player_turn->setStyleSheet(O_label_style);
    }

    if(currentPlayer == 0 && player1 == "random"){
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
        int x_first = rand() % 9;
        int y_first = rand() % 9;                   /////////////////////////////////////////////////////////////
        QString get_symb;
        QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(button){
            get_symb = button->text();
        }
        while (!get_symb.isEmpty()) {
            x_first = rand() % 9;
            y_first = rand() % 9;
            QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
        }
        handleMove_ult(x_first,y_first,'X');
    }
    if(currentPlayer == 1 && player2 == "random"){
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
        int x_first = rand() % 9;
        int y_first = rand() % 9;                   /////////////////////////////////////////////////////////////
        QString get_symb;
        QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(button){
            get_symb = button->text();
        }
        while (!get_symb.isEmpty()) {
            x_first = rand() % 9;
            y_first = rand() % 9;
            QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
        }
        handleMove_ult(x_first,y_first,'O');
    }
}

void MainWindow::connect_ult_Buttons(){
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            QString buttonName = QString("ultimate_%1_%2").arg(i).arg(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            qDebug() << buttonName;
            if (button) {
                connect(button, &QPushButton::clicked, this, [=]() {
                    handleMove_ult(i,j,currentPlayer == 0 ? 'X' : 'O');
                });
            }
        }
    }
}

/////////////////////misere/////////////


void MainWindow::connectMisereButtons() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            QString buttonName = QString("misere_%1_%2").arg(i).arg(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if (button) {
                connect(button, &QPushButton::clicked, this, [=]() {
                    handleMove(i, j, currentPlayer == 0 ? 'X' : 'O',3);
                });
            }
        }
    }
}



///////////////////////4x4_connect/////////

/////////////////////////////////////first/////////////

void MainWindow::get_first_index_4x4(int i , int j , QString symp_Str){
    string str = symp_Str.toStdString();
    if((str == "X" && currentPlayer == 0) || (str == "O" && currentPlayer == 1)){
        if(currentPlayer == 0){
            xTurnSound->play();
        }else{
            oTurnSound->play();
        }
        x1 = i;
        y1 = j;
        symp = currentPlayer == 0 ? 'X' : 'O';
        qDebug() << "done";
        qDebug() << x1 << y1 <<symp;
        ui->choose->setText("Select the new position");
        QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        button->setText("");
        button->setStyleSheet(regular_btn_style);
        if(first){
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
                    QPushButton* button = findChild<QPushButton*>(buttonName);
                    QString buttonName_2 = QString("_4x4_%1_%2").arg(i+4).arg(j);
                    QPushButton* button_2 = findChild<QPushButton*>(buttonName_2);
                    //qDebug() << buttonName;
                    if (button) {
                        button_2->setText(button->text());
                        button_2->setStyleSheet(button->styleSheet());
                    }
                    // if(button){
                    //     button->setText(button_2->text());
                    //     button->setStyleSheet(button_2->styleSheet());
                    // }
                }
            }
        }
        ui->gridLayoutWidget_16->hide();
        ui->gridLayoutWidget_19->show();
        if(currentPlayer == 0 && player1 == "random"){
            int x_second;
            int y_second;
            if (currentPlayer == 0 && player1 == "random") {
                // Seed the random number generator (done only once, ideally at the start of the program)
                static bool seeded = false;
                if (!seeded) {
                    srand(static_cast<unsigned int>(time(0)));
                    seeded = true;
                }

                // Generate all potential moves
                vector<pair<int, int>> valid_positions = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};

                // Filter valid positions
                vector<pair<int, int>> filtered_positions;
                for (const auto& pos : valid_positions) {
                    int x = pos.first;
                    int y = pos.second;

                    // Check bounds
                    if (x >= 0 && x <= 3 && y >= 0 && y <= 3) {
                        QString buttonName = QString("_4x4_%1_%2").arg(x).arg(y);
                        QPushButton* button = findChild<QPushButton*>(buttonName);

                        // Check if button is not null and empty
                        if (button && button->text().isEmpty()) {
                            filtered_positions.push_back(pos);
                        }
                    }
                }

                // If there are no valid positions, break the loop
                if (filtered_positions.empty()) {
                    qDebug() << "No valid moves available!";
                    return; // No move possible
                }

                // Pick a random valid position
                int idx = rand() % filtered_positions.size();
                x_second = filtered_positions[idx].first;
                y_second = filtered_positions[idx].second;

                // Make the move
                QString buttonName = QString("_4x4_%1_%2").arg(x_second).arg(y_second);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                if (button) {
                    button->setText("X"); // Or the symbol for the current player
                    qDebug() << "Random move made at:" << buttonName;
                }
            }

            //}
            qDebug() << x_second << y_second;
            get_second_index_4x4(x_second+4,y_second,"");

        }if(currentPlayer == 1 && player2 == "random"){
            int x_second;
            int y_second;
            // Seed the random number generator (done only once, ideally at the start of the program)
            static bool seeded = false;
            if (!seeded) {
                srand(static_cast<unsigned int>(time(0)));
                seeded = true;
            }

            // Generate all potential moves
            vector<pair<int, int>> valid_positions = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};

            // Filter valid positions
            vector<pair<int, int>> filtered_positions;
            for (const auto& pos : valid_positions) {
                int x = pos.first;
                int y = pos.second;

                // Check bounds
                if (x >= 0 && x <= 3 && y >= 0 && y <= 3) {
                    QString buttonName = QString("_4x4_%1_%2").arg(x).arg(y);
                    QPushButton* button = findChild<QPushButton*>(buttonName);

                    // Check if button is not null and empty
                    if (button && button->text().isEmpty()) {
                        filtered_positions.push_back(pos);
                    }
                }
            }

            // If there are no valid positions, break the loop
            if (filtered_positions.empty()) {
                qDebug() << "No valid moves available!";
                return; // No move possible
            }

            // Pick a random valid position
            int idx = rand() % filtered_positions.size();
            x_second = filtered_positions[idx].first;
            y_second = filtered_positions[idx].second;

            // Make the move
            QString buttonName = QString("_4x4_%1_%2").arg(x_second).arg(y_second);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if (button) {
                button->setText("O"); // Or the symbol for the current player
                qDebug() << "Random move made at:" << buttonName;
            }
        //}
        qDebug() << x_second << y_second;
        get_second_index_4x4(x_second+4,y_second,"");
        }
        //first = false;
    }else{
        QMessageBox::warning(this, "Invalid Move", "Choose a valid position");
    }
}

void MainWindow::connect_4x4_first_Buttons() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            qDebug() << buttonName;
            // if(currentPlayer == 0){
            //     xTurnSound->play();
            // }else{
            //     oTurnSound->play();
            // }
            if (button) {
                connect(button, &QPushButton::clicked, this, [=]() {
                    get_first_index_4x4(i , j , button->text());
                });
                //ui->gridLayoutWidget_16->hide();
                //ui->gridLayoutWidget_19->show();
                qDebug() << x1 << y1 <<symp;
            }
        }
    }
}

void MainWindow::connect_4x4_second_Buttons(){
    for (int i = 4; i < 8; ++i) {
        for (int j = 0; j < 4; ++j) {
            QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            qDebug() << buttonName;

            if (button) {
                connect(button, &QPushButton::clicked, this, [=]() {
                    get_second_index_4x4(i , j , button->text());
                });
            }
        }
    }
}

void MainWindow::get_second_index_4x4(int i , int j , QString symp_Str){

    string str = symp_Str.toStdString();
    x2 = i-4;
    if(str.empty() &&((x1 == x2 && y1 == j+1)||(x1 == x2 && y1 == j-1)||(x1 == x2+1 && y1 == j)||(x1 == x2-1 && y1 == j))){
        if(currentPlayer == 0){
            xTurnSound->play();
        }else{
            oTurnSound->play();
        }
        x2 = i;
        y2 = j;
        // x1 = i;
        // y1 = j;
        qDebug() << "done";
        qDebug() << x2 << y2 <<symp;
        ui->choose->setText("Choose the position you want to move");
        Four_x_Four_set(i-4,j);
        QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        button->setText(QString(currentPlayer == 0? "X" : "O"));
        if(currentPlayer == 0){
            button->setStyleSheet(X_btn_Style);
        }else{
            button->setStyleSheet(O_btn_Style);
        }
        // QString buttonName_2 = QString("_4x4_%1_%2").arg(i-4).arg(j);
        // QPushButton* button_2 = findChild<QPushButton*>(buttonName_2);
        // //qDebug() << buttonName;
        // if (button_2) {
        //     button_2->setText(QString(currentPlayer == 0? "X" : "O"));
        //     button_2->setStyleSheet(currentPlayer == 0?X_btn_Style:O_btn_Style);
        // }

        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                QString buttonName_2 = QString("_4x4_%1_%2").arg(i+4).arg(j);
                QPushButton* button_2 = findChild<QPushButton*>(buttonName_2);
                //qDebug() << buttonName;
                if (button) {
                    button->setText(button_2->text());
                    button->setStyleSheet(button_2->styleSheet());
                }
            }
        }
        Board_ptr->update_board(x1,y1,currentPlayer == 0? 'X' : 'O');
        if(Board_ptr->is_win()){
            winSound->play();
            QMessageBox::information(this, "Game Over", QString("%1 wins!").arg(Players_ptr[currentPlayer]->getname().c_str()));
            for (int i = 0; i < 4; ++i) {
                for (int j = 0; j < 4; ++j) {
                    QString buttonName = QString("_4x4_%1_%2").arg(i).arg(j);
                    QPushButton* button = findChild<QPushButton*>(buttonName);
                    QString buttonName_2 = QString("_4x4_%1_%2").arg(i+4).arg(j);
                    QPushButton* button_2 = findChild<QPushButton*>(buttonName_2);
                    //qDebug() << buttonName;
                    if (button) {
                        button->setText("");
                        button->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button->setStyleSheet(regular_btn_style);
                    }
                    if (button_2) {
                        button_2->setText("");
                        button_2->setEnabled(true);
                        //stylesheet!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                        button_2->setStyleSheet(regular_btn_style);
                    }
                }
            }
            // delete Board_ptr;
            // for (int var = 0; var < 2; ++var) {
            //     delete Players_ptr[var];
            // }
            ui->stackedWidget->setCurrentIndex(1);
            currentPlayer = (currentPlayer + 1) % 2; // Switch players

            ui->gridLayoutWidget_19->hide();
            ui->gridLayoutWidget_16->show();
            return;
        }
        currentPlayer = (currentPlayer + 1) % 2; // Switch players

        ui->gridLayoutWidget_19->hide();
        ui->gridLayoutWidget_16->show();
        if(currentPlayer == 0 && player1 == "random"){
            srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
            int x_first = rand() % 4;
            int y_first = rand() % 4;                   /////////////////////////////////////////////////////////////
            QString get_symb;
            QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
            while (!(get_symb == "X")) {
                x_first = rand() % 4;
                y_first = rand() % 4;
                QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                if(button){
                    get_symb = button->text();
                }
                qDebug() << "Checking button at" << x_first << y_first << "with text:" << get_symb;
            }
            get_first_index_4x4(x_first,y_first,"X");
        }
        if(currentPlayer == 1 && player2 == "random"){
            srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
            int x_first = rand() % 4;
            int y_first = rand() % 4;                   /////////////////////////////////////////////////////////////
            QString get_symb;
            QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
            while (!(get_symb == "O")) {
                x_first = rand() % 4;
                y_first = rand() % 4;
                QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
                QPushButton* button = findChild<QPushButton*>(buttonName);
                if(button){
                    get_symb = button->text();
                }
                qDebug() << "Checking button at" << x_first << y_first << "with text:" << get_symb;
            }
            get_first_index_4x4(x_first,y_first,"O");
        }
    }else{
        QMessageBox::warning(this, "Invalid Move", "Choose a valid position");
    }
}

void MainWindow::Four_x_Four_set(int x1, int y1){
    auto* derivedBoard = dynamic_cast<Four_X_Four_Board<char>*>(Board_ptr);
    if (derivedBoard) {
        derivedBoard->setNewPos(x1,y1);
        //derivedBoard->new_y = y1;

    } else {
        // Handle error if the cast fails
        qDebug() << "Invalid board pointer cast!";
    }
}
//////////////////////////////pyramid///////////////

void MainWindow::connectPyramidButtons() {
    connect(ui->pyramic_0_2, &QPushButton::clicked, this, [=]() {
        handleMove(0, 2, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_1_1, &QPushButton::clicked, this, [=]() {
        handleMove(1, 1, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_1_2, &QPushButton::clicked, this, [=]() {
        handleMove(1, 2, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_1_3, &QPushButton::clicked, this, [=]() {
        handleMove(1, 3, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_2_0, &QPushButton::clicked, this, [=]() {
        handleMove(2, 0, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_2_1, &QPushButton::clicked, this, [=]() {
        handleMove(2, 1, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_2_2, &QPushButton::clicked, this, [=]() {
        handleMove(2, 2, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_2_3, &QPushButton::clicked, this, [=]() {
        handleMove(2, 3, currentPlayer == 0 ? 'X' : 'O',3);
    });
    connect(ui->pyramic_2_4, &QPushButton::clicked, this, [=]() {
        handleMove(2, 4, currentPlayer == 0 ? 'X' : 'O',3);
    });
}



void MainWindow::on_Play_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);       //will go to (2) after doing the ai part //also need to ask for the name
    mainButtonSound->play();
}


void MainWindow::on_Pyramic_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    if (Board_ptr) {
        delete Board_ptr;
    }

    for (int i = 0; i < 2; ++i) {
        if (Players_ptr[i]) {
            delete Players_ptr[i];
        }
    }
    Board_ptr = new Pyramid_Board<char>;
    Players_ptr[0] = new Pyramid_Player<char>("name1",'X');
    Players_ptr[1] = new Pyramid_Random_Player<char>('O');

    currentPlayer = 0;
    player1 = "human";
    player2 = "random";

    static bool buttonsConnected_p = false;
    if (!buttonsConnected_p) {
        connectPyramidButtons();
        buttonsConnected_p = true;
    }
}


void MainWindow::on_Four_in_row_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::on__5x5_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_word_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(6);
}


void MainWindow::on_numerical_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);
}


void MainWindow::on_misere_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(8);
    delete Board_ptr;
    Board_ptr = nullptr;

    if (!Board_ptr) {
        Board_ptr = new Pyramid_Board<char>();
        Players_ptr[0] = new Pyramid_Player<char>("Player X", 'X');
        Players_ptr[1] = new Pyramid_Player<char>("Player O", 'O');
    }


    currentPlayer = 0;

    static bool buttonsConnected_m = false;
    if (!buttonsConnected_m) {
        connectMisereButtons();
        buttonsConnected_m = true;
    }
}


void MainWindow::on__4x4_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(9);
    mainButtonSound->play();

    // if (Board_ptr) {
    //     delete Board_ptr;
    //     Board_ptr = nullptr;
    //     if (Board_ptr_ult_0_0){
    //         delete Board_ptr_ult_0_0;
    //         Board_ptr_ult_0_0 = nullptr;
    //         delete Board_ptr_ult_0_1;
    //         Board_ptr_ult_0_1 = nullptr;
    //         delete Board_ptr_ult_0_2;
    //         Board_ptr_ult_0_2 = nullptr;
    //         delete Board_ptr_ult_1_0;
    //         Board_ptr_ult_1_0 = nullptr;
    //         delete Board_ptr_ult_1_1;
    //         Board_ptr_ult_1_1 = nullptr;
    //         delete Board_ptr_ult_1_2;
    //         Board_ptr_ult_1_2 = nullptr;
    //         delete Board_ptr_ult_2_0;
    //         Board_ptr_ult_2_0 = nullptr;
    //         delete Board_ptr_ult_2_1;
    //         Board_ptr_ult_2_1 = nullptr;
    //         delete Board_ptr_ult_2_2;
    //         Board_ptr_ult_2_2 = nullptr;
    //     }
    // }
    // for (int i = 0; i < 2; ++i) {
    //     if (Players_ptr[i]) {
    //         delete Players_ptr[i];
    //         Players_ptr[i] = nullptr;
    //     }
    // }


    if (Board_ptr) {
        delete Board_ptr;
        Board_ptr = nullptr;
    }
    for (int i = 0; i < 2; ++i) {
        if (Players_ptr[i]) {
            delete Players_ptr[i];
            Players_ptr[i] = nullptr;
        }
    }
    Board_ptr = new Four_X_Four_Board<char>;
    if(player1 == "human"){
        Players_ptr[0] = new Four_X_Four_Player<char>(player1_name,'X');
    }else if(player1 == "random"){
        Players_ptr[0] = new Four_X_Four_Random_Player<char>('X');
    }
    //Players_ptr[0] = new X_O_Player<char>(player1_name,'X');
    if(player2 == "human"){
        Players_ptr[1] = new Four_X_Four_Player<char>(player2_name,'X');
    }else if(player2 == "random"){
        Players_ptr[1] = new Four_X_Four_Random_Player<char>('O');
    }
    //Players_ptr[1] = new X_O_Player<char>(player2_name,'O');

    currentPlayer = 0;

    int ind = 0;
    for (int j = 0; j < 4; ++j) {
        QString buttonName = QString("_4x4_%1_%2").arg(ind).arg(j);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(j % 2 == 0){
            button->setText("O");
        }else{
            button->setText("X");
        }
    }
    ind = 3;
    for (int j = 0; j < 4; ++j) {
        QString buttonName = QString("_4x4_%1_%2").arg(ind).arg(j);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(j % 2 == 0){
            button->setText("X");
        }else{
            button->setText("O");
        }
    }
    first = true;

    static bool buttonsConnected_4 = false;
    if (!buttonsConnected_4) {
        connect_4x4_first_Buttons();
        connect_4x4_second_Buttons();
        buttonsConnected_4 = true;
    }
    if(player1 == "random"){
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
        int x_first = rand() % 4;
        int y_first = rand() % 4;                   /////////////////////////////////////////////////////////////
        QString get_symb;
        QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(button){
            get_symb = button->text();
        }
        while (!(get_symb == "X")) {
            x_first = rand() % 4;
            y_first = rand() % 4;
            QString buttonName = QString("_4x4_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
        }
        get_first_index_4x4(x_first,y_first,"X");
    }
}


void MainWindow::on_ultimate_tic_tac_toe_btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(10);
    mainButtonSound->play();
    //ui->player_turn->show();

    ui->ultimate_big_0_0->hide();
    ui->ultimate_big_1_0->hide();
    ui->ultimate_big_2_0->hide();
    ui->ultimate_big_0_1->hide();
    ui->ultimate_big_1_1->hide();
    ui->ultimate_big_2_1->hide();
    ui->ultimate_big_0_2->hide();
    ui->ultimate_big_1_2->hide();
    ui->ultimate_big_2_2->hide();

    if (Board_ptr) {
        delete Board_ptr;
        Board_ptr = nullptr;
        if (Board_ptr_ult_0_0){
            //delete Board_ptr_ult_0_0;
            Board_ptr_ult_0_0 = nullptr;
            //delete Board_ptr_ult_0_1;
            Board_ptr_ult_0_1 = nullptr;
            //delete Board_ptr_ult_0_2;
            Board_ptr_ult_0_2 = nullptr;
            //delete Board_ptr_ult_1_0;
            Board_ptr_ult_1_0 = nullptr;
            //delete Board_ptr_ult_1_1;
            Board_ptr_ult_1_1 = nullptr;
            //delete Board_ptr_ult_1_2;
            Board_ptr_ult_1_2 = nullptr;
            //delete Board_ptr_ult_2_0;
            Board_ptr_ult_2_0 = nullptr;
            //delete Board_ptr_ult_2_1;
            Board_ptr_ult_2_1 = nullptr;
            //delete Board_ptr_ult_2_2;
            Board_ptr_ult_2_2 = nullptr;
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (Players_ptr[i]) {
            delete Players_ptr[i];
            Players_ptr[i] = nullptr;
        }
    }
    Board_ptr = new X_O_Board<char>;
    if(player1 == "human"){
        Players_ptr[0] = new X_O_Player<char>(player1_name,'X');
    }else if(player1 == "random"){
        Players_ptr[0] = new X_O_Random_Player<char>('X');
    }
    //Players_ptr[0] = new X_O_Player<char>(player1_name,'X');
    if(player2 == "human"){
        Players_ptr[1] = new X_O_Player<char>(player2_name,'O');
    }else if(player2 == "random"){
        Players_ptr[1] = new X_O_Random_Player<char>('O');
    }
    //Players_ptr[1] = new X_O_Player<char>(player2_name,'O');

    Board_ptr_ult_0_0 = new X_O_Board<char>;
    Board_ptr_ult_0_1 = new X_O_Board<char>;
    Board_ptr_ult_0_2 = new X_O_Board<char>;
    Board_ptr_ult_1_0 = new X_O_Board<char>;
    Board_ptr_ult_1_1 = new X_O_Board<char>;
    Board_ptr_ult_1_2 = new X_O_Board<char>;
    Board_ptr_ult_2_0 = new X_O_Board<char>;
    Board_ptr_ult_2_1 = new X_O_Board<char>;
    Board_ptr_ult_2_2 = new X_O_Board<char>;

    currentPlayer = 0;

    static bool buttonsConnected_ult = false;
    if (!buttonsConnected_ult) {
        connect_ult_Buttons();
        buttonsConnected_ult = true;
    }
    if(player1 == "random"){
        srand(static_cast<unsigned int>(time(0)));  // Seed the random number generator
        int x_first = rand() % 9;
        int y_first = rand() % 9;                   /////////////////////////////////////////////////////////////
        QString get_symb;
        QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
        QPushButton* button = findChild<QPushButton*>(buttonName);
        if(button){
            get_symb = button->text();
        }
        while (!get_symb.isEmpty()) {
            x_first = rand() % 9;
            y_first = rand() % 9;
            QString buttonName = QString("ultimate_%1_%2").arg(x_first).arg(y_first);
            QPushButton* button = findChild<QPushButton*>(buttonName);
            if(button){
                get_symb = button->text();
            }
        }
        handleMove_ult(x_first,y_first,'X');
    }
}


void MainWindow::on_misere_0_0_clicked()
{

}

void MainWindow::on_P_1_H_clicked()
{
    player1 = "human";
    ui->human_p1_lbl->show();
    ui->random_p1_lbl->hide();
    mainButtonSound->play();
}


void MainWindow::on_P_1_R_clicked()
{
    player1 = "random";
    ui->random_p1_lbl->show();
    ui->human_p1_lbl->hide();
    mainButtonSound->play();
}


void MainWindow::on_P_2_H_clicked()
{
    player2 = "human";
    ui->human_p2_lbl->show();
    ui->random_p2_lbl->hide();
    mainButtonSound->play();
}


void MainWindow::on_P_2_R_clicked()
{
    player2 = "random";
    ui->random_p2_lbl->show();
    ui->human_p2_lbl->hide();
}


void MainWindow::on_P_1_Ready_clicked()
{
    player1_name = (ui->P1_line->text()).toStdString();
    if(player1.empty() || player1_name.empty()){
        QMessageBox::critical(this, "Choose type", QString("Choose the type and name of player 1 first."));
        return;
    }
    p1_done = true;
    mainButtonSound->play();
    if(p1_done && p2_done){
        ui->stackedWidget->setCurrentIndex(1);

    }
}

void MainWindow::on_P_2_Ready_clicked()
{
    player2_name = (ui->P2_line->text()).toStdString();
    if(player2.empty() || player2_name.empty()){
        QMessageBox::critical(this, "Choose type", QString("Choose the type and name of player 2 first."));
        return;
    }
    p2_done = true;
    mainButtonSound->play();
    if(p1_done && p2_done){
        ui->stackedWidget->setCurrentIndex(1);

    }
}


void MainWindow::on_pushButton_clicked()
{
    player1 = "";
    player2 = "";
    ui->P_1_A->hide();
    ui->P_2_A->hide();
    ui->human_p1_lbl->hide();
    ui->human_p2_lbl->hide();
    ui->AI_p1_lbl->hide();
    ui->AI_p2_lbl->hide();
    ui->random_p1_lbl->hide();
    ui->random_p2_lbl->hide();
    ui->P1_line->setText("Player 1");
    ui->P2_line->setText("Player 2");
    mainButtonSound->play();
    ui->stackedWidget->setCurrentIndex(2);

}

