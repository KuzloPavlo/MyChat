#pragma once
#ifndef SERV_CONNECT_H
#define SERV_CONNECT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

#include "user.h"
#include "messagetypes.h"
#include "returnvalues.h"

class Serv_Connect : public QObject
{
    Q_OBJECT
public:
    explicit Serv_Connect(QObject *parent = 0);

    void registration(QString *pname,
                      QString *psurname,
                      QString *plogin,
                      QString *ppassword);

    void authorization(QString *plogin, QString *ppassword);


    void searchFriend(QString *pdataFriend);

    void addFriend (QString *pLoginFriend);

    void addDataUser(
            QString *pname,
            QString *psurname,
            QString *plogin,
            QString *ppassword,
            QString *pipAddress);

    User getUser();
public:

    QVector<User> m_potentialFriends;          // ПИТАЙ!!!!!

signals:
    void signalRegRegistered(
            QString *pname,
            QString *psurname,
            QString *plogin,
            QString *ppassword,
            QString *pipAddress);
    void signalRegLoginBusy();

    void signalAuthAuthorized(
            QString *pname,
            QString *psurname,
            QString *plogin,
            QString *ppassword,
            QString *pipAddress);
    void signalAuthWrongLogin();
    void signalAuthWrongPassword();
    void signalAuthIsEmty();

    void signalSearchFriendResponsNotFound();
    void signalSearchFriendResponsFound(QVector<User> potentialFriends);

private:
    QTcpSocket *m_psocket;
    quint16 m_nnextBlockSize;
    User m_user;
    QVector<User>m_friends;
    // QVector<User> m_potentialFriends;


    void regServerResponding(QDataStream *pregInfo);
    void authServerResponding(QDataStream *pauthInfo);
    void searchFriendServerResponding(QDataStream *psearchInfo);

private slots:
    void slotReadServer();
    void slotSetUser(QString *pname,
                     QString *psurname,
                     QString *plogin,
                     QString *ppassword,
                     QString *pipAddress);

    void slotSearchFriendResponsFound(QVector<User> potentialFriends);

};

#endif // SERV_CONNECT_H
