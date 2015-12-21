#pragma once

#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>
#include "returnvalues.h"

class User
{
public:
    User();
    User( const QString &pname,
          const QString &psurname,
          const QString &plogin,
          const QString &ppassword,
          const QString &pipAddress);

    QString getName();
    QString getSurname();
    QString getLogin();
    QString getPassword();
    QString getIPAddress();

    void setName(QString *pname);          //  Make a copy constructor!!!
    void setSurname(QString *psurname);    //  Make a copy constructor!!!
    void setLogin(QString *plogin);        //  Make a copy constructor!!!
    void setPassword(QString *ppassword);  //  Make a copy constructor!!!
    void setIPAddress(QString *pipAddress);

    void addFriend(User *pfriend);
    QVector<User> getFriends();
    void removingFriend(QString* friendLogin);



private:
    QString m_name;
    QString m_surname ;
    QString m_login ;
    QString m_password ;
    QString m_ipAddress;

    QVector<User*> m_friends;
};

#endif // USER_H
