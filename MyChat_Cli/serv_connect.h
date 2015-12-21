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

    void registerUser(const QString &name,
                      const QString &surname,
                      const QString &login,
                      const QString &password);

    void authorizationUser(const QString &login, const QString &password);


    void findFriend(const QString &tokenFriend);

    void addFriend (QString *pLoginFriend);

    void addDataUser(
            const QString &pname,
            const QString &psurname,
            const QString &plogin,
            const QString &ppassword,
            const QString &pipAddress);

    User getUser();
public:

    QVector<User> m_potentialFriends;          // ПИТАЙ!!!!!

signals:
    void signalRegistered(const QString &login, const QString &password);

    void signalLoginBusy();

    void signalAuthorized(
            const QString &name,
            const QString &surname,
            const QString &login);

    void signalWrongLogin();
    void signalWrongPassword();
    void signalIsEmty();

    void signalFoundFriend(QVector<User> potentialFriends);

private:
    QTcpSocket *m_psocket;
    quint16 m_nnextBlockSize;
    User m_user;
    QVector<User>m_friends;

    void processRegistrationResponse(QDataStream *in);
    void processAuthorizationResponse(QDataStream *in);
    void setAuthorizedUser(QDataStream *in);

    void processFindFriendResponse(QDataStream *in);

private slots:
    void slotReadServer();
    void slotSetUser(const QString &pname,
                     const QString &psurname,
                     const QString &plogin,
                     const QString &ppassword,
                     const QString &pipAddress);

   // void slotSearchFriendResponsFound(QVector<User> potentialFriends);

};

#endif // SERV_CONNECT_H
