#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "users.h"
#include "participantschat.h"
#include "friends.h"
#include "community.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:



    void on_WelOkBut_clicked();

    void on_LogRegistrationBut_clicked();


    void on_RegBackBut_clicked();

    void on_Close_clicked();

    void on_Roll_up_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
