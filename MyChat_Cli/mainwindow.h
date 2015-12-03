#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "users.h"
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


private:

    Serv_Connect *SERVER;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
