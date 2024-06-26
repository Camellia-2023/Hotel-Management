#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_test_621.h"
#include <iostream>
#include <QTableView>
#include <qstandarditemmodel.h>
#include "room_manager.h" 

class test_621 : public QMainWindow
{
    Q_OBJECT

public:
    test_621(QWidget *parent = nullptr);
    ~test_621();
    int state = 0;

private slots:
    void on_display_clicked();
    void on_delete_2_clicked();
    void on_seting_clicked();
    void on_adding_clicked();
    void on_close_clicked();
    //void on_pushButton_inputok_clicked();
    void on_pushButton_inputok_clicked();

private:
    GuestRoomManager m_grm;   //客房管理对象 
    string name="";
    int price=0;
    int bed_num=0;
    int area=0;

    string room_number="";


    string number="";
    Ui::test_621Class ui;
};
