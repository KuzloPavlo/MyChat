#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "arrayofusers.h"
#include "participantschat.h"
#include "friends.h"
#include "community.h"
#include <serv_connect.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0, Serv_Connect *pSERVER = 0);
    ~MainWindow();




private slots:

    void on_WelOkBut_clicked();

    void on_LogRegistrationBut_clicked();

    void on_RegBackBut_clicked();

    void on_Close_clicked();

    void on_Roll_up_clicked();

    void on_RegRegistrationBut_clicked();

    void on_LogLoginBut_clicked();

    void slotRegServerResponseRegistered();

    void slotRegServerResponseLoginBusy();

    void slotAuthServerResponseAuthorized();

    void slotAuthServerResponseWrongLogin();

    void slotAuthServerResponseWrongPassword();

    void slotAuthServerResponseIsEmty();


private:

    Serv_Connect *m_pSERVER;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
