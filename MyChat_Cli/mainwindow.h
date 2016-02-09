#pragma once

#include <QMainWindow>
#include "user.h"
#include "usersarray.h"
#include <Client.h>
#include <user.h>
#include "message.h"
#include <QDateTime>
#include <QTableWidget>
#include "correspondence.h"
#include "formmessage.h"
#include "incomingmessage.h"
#include "outgoingmessage.h"
#include "formparticipant.h"
#include "addparticipantdialog.h"
#include "formchat.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0, Client *pSERVER = 0);
    ~MainWindow();
    AddParticipantDialog *addParticipantDialog;

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

    void slotResizeTableWidgetRows(QTableWidget *tableWidget);

    void slotFoundFriend(QString login);

    void slotNewFriend();

    void slotNewGroupChat();

    void slotIncomingMessage(const QString &sender,
                             const QString &message,
                             const QString &time);

    void slotEarlierReceivedMessage(
            const QString &sender,
            const QString &message,
            const QString &time);

    void slotEarlierSendMessage(
            const QString &sender,
            const QString &message,
            const QString &time);

    void on_MainConnBut_clicked();

    void on_MainChatsBut_clicked();

    void on_MainCloseSearchButt_clicked();

    void on_MainSearchEdit_textChanged(const QString &arg1);

    void on_MainSearchBut_clicked();

    void on_MainListWidget_currentTextChanged(const QString &currentText);

    void on_MainAddFrinedBut_clicked();

    void on_MainUserBut_clicked();

    void on_ConntactsListWidget_currentTextChanged(const QString &currentText);

    void on_DeleteConBut_clicked();

    void on_NotRmoveFriendBut_clicked();

    void on_RemoveFriendBut_clicked();


    void on_SendMessageBut_clicked();

    void slotShowFriend(QString name,
                        QString surname,
                        QString login
                        );

    void slotShowPotentialFriend(QString name,
                                 QString surname,
                                 QString login);

    void slotAddFriendToList(QString login);

    void slotAddChatToList(const int &IDNumber);

    void on_CreateCahtBut_clicked();

    void slotclientdebug(const QString &str);

    void on_ChatListWidget_itemClicked(QListWidgetItem *item);

signals:

    void signalAddDataUser(QString *pname,
                           QString *psurname,
                           QString *plogin,
                           QString *ppassword,
                           QString *pipAddress);

    void signalShowListFriends();

    void signalShowListChats();

    void signalShowFriend(const QString &login);

    void signalShowPotentialFriend(const QString &login);

private:

    Client *m_pSERVER;

    QVector<User> m_potentialFriends;

    QVector<User>m_friends;
    QVector<Correspondence> m_Correspondence;

    void addNewMessage(QTableWidget *tableWidget,QWidget *message);

    void f(const QString &str);

    Ui::MainWindow *ui;
};
