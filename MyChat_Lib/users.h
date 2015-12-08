#pragma once
#ifndef USERS_H
#define USERS_H
#include "community.h"
#include <QDebug>
#include <QVector>
#include <user.h>
#include <QDataStream>
//#include <QString>

class Users:public Community
{
private:
    // 12:30
    QVector<User> UserVector;
public:
     int addUser(QDataStream *newUserInfo);
     int showUsersLogin(QDataStream *AuthoInfo);
signals:
     //registration signals
     void signalRegistered (QString login, QString password);
     void signalLoginBusu ();

     //authorization signals
     void Authorized (); // в етом сигнале будет отправлятся многое ПОМНИ
     void LoginWrong ();
     void PasswordWrong();
};

#endif // USERS_H
