#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "user.h"
#include "usersarray.h"
#include "participantschat.h"
#include "friends.h"
#include "community.h"
#include <serv_connect.h>
#include <user.h>


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

    void slotRegistered(const QString &plogin, const QString &ppassword);

    void slotLoginBusy();

    void slotAuthorized(
            const QString &name,
            const QString &surname,
            const QString &login);

    void slotWrongLogin();

    void slotWrongPassword();

    void slotIsEmty();





    void slotFoundFriend(QVector<User> potentialFriends);



    void on_MainConnBut_clicked();

    void on_MainChatsBut_clicked();

    void on_MainCloseSearchButt_clicked();

    void on_MainSearchEdit_textChanged(const QString &arg1);

    void on_MainSearchBut_clicked();

    void on_MainListWidget_currentTextChanged(const QString &currentText);

    void on_MainAddFrinedBut_clicked();

    void on_MainUserBut_clicked();


    void on_ConntactsListWidget_currentTextChanged(const QString &currentText);

signals:

    void signalAddDataUser(QString *pname,
                           QString *psurname,
                           QString *plogin,
                           QString *ppassword,
                           QString *pipAddress);

private:

    Serv_Connect *m_pSERVER;

     QVector<User> m_potentialFriends;

    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
