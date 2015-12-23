#pragma once
#ifndef USERS_H
#define USERS_H

#include <QDebug>
#include <QVector>
#include <QDataStream>

#include "user.h"
#include "community.h"
#include "messagetypes.h"
#include "returnvalues.h"

class UsersArray:public Community
{

public:

    ReturnValues addUser(const QString &name,
                         const QString &surname,
                         const QString &login,
                         const QString &password,
                         const QString &ipAddress);

    ReturnValues authorizeUser(const QString &login, const QString &password);

    QVector<User> findFriend (const QString &tokenFriend);

    User getUser(const QString &login);                  // !!!! Обсуди с Романом
    int showUsersLogin(QDataStream *pAuthoInfo);


    ReturnValues addFriend(const QString &userLogin, const QString &friendLogin);

    ReturnValues removeFriend(const QString &userLogin, const QString &friendLogin);

    QVector<User> getUserFriends(QDataStream *pUserInfo);

signals:
    //registration signals
    // void signalRegistered (QString login, QString password);
    void signalLoginBusu ();

    //authorization signals
    void signalAuthorized (); // в етом сигнале будет отправлятся многое ПОМНИ
    void signalLoginWrong ();
    void signalPasswordWrong();

private:
    // 12:30
    QVector<User> m_users;

};

#endif // USERS_H
