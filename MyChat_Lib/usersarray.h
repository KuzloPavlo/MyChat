#pragma once
#include <QDebug>
#include <QVector>
#include <QDataStream>
#include <QTcpSocket>
#include "user.h"

#include "messagetypes.h"
#include "returnvalues.h"
#include "correspondence.h"
#include "message.h"

class UsersArray
{

public:

    ReturnValues addUser(const QString &name,
                         const QString &surname,
                         const QString &login,
                         const QString &password,
                         const QString &ipAddress);

    ReturnValues authorizeUser(const QString &login, const QString &password, QTcpSocket* pClientSocket);

    QVector<User> findFriend (const QString &tokenFriend);

    User getUser(const QString &login);                  // !!!! Обсуди с Романом

    int showUsersLogin(QDataStream *pAuthoInfo);

    ReturnValues addFriend(const QString &userLogin, const QString &friendLogin);

    ReturnValues removeFriend(const QString &userLogin, const QString &friendLogin);

    QVector<User> getUserFriends(const QString &userLogin);

    QVector<Correspondence> getUserCorrespondence(const QString &userLogin);

    QTcpSocket* getUserTcpSocket(const QString &userLogin);

    void receiveMessage(const Message &newmessage);

signals:
    //registration signals
    // void signalRegistered (QString login, QString password);
    void signalLoginBusu ();

    //authorization signals
    void signalAuthorized (); // в етом сигнале будет отправлятся многое ПОМНИ
    void signalLoginWrong ();
    void signalPasswordWrong();

private:
    QVector<User> m_users;
    QVector<Correspondence> m_Correspondence;
};
