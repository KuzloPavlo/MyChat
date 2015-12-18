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

class ArrayOfUsers:public Community
{

public:

    ReturnValues addUser(QString *pname,
                         QString *psurname,
                         QString *plogin,
                         QString *ppassword,
                         QString *pipAddress);

    ReturnValues authorizeUser(QString *plogin,
                               QString *ppassword);
    QVector<User> seatrchFriend (QString *pdataFriend);

    User getUser(QString *pUserLogin);                  // !!!! Обсуди с Романом
    int showUsersLogin(QDataStream *pAuthoInfo);


    ReturnValues addFriend(QDataStream *pNewFriendInfo);
    QVector<User> getUserFriends(QDataStream *pUserInfo);
    ReturnValues removingFriend(QDataStream *pRemoveFriendInfo);
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
