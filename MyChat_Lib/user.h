#pragma once

#include <QDebug>
#include <QString>
#include "returnvalues.h"
#include <correspondence.h>
#include <QTcpSocket>

class Correspondence;   // forward declaration

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
    QTcpSocket* getTcpSocket();

    void setName(QString *pname);          //  Make a copy constructor!!!
    void setSurname(QString *psurname);    //  Make a copy constructor!!!
    void setLogin(QString *plogin);        //  Make a copy constructor!!!
    void setPassword(QString *ppassword);  //  Make a copy constructor!!!
    void setIPAddress(QString *pipAddress);
    void setTcpSocket(QTcpSocket *pClientSocket);

    void addFriend(User *pfriend, Correspondence *correspondence);
    QVector<User> getFriends();
    QVector<Correspondence> getCorrespondence();
    void removeFriend(const QString &friendLogin);



private:
    QString m_name;
    QString m_surname ;
    QString m_login ;
    QString m_password ;
    QString m_ipAddress;
    QTcpSocket* m_pUserSocket;

    QVector<User*> m_friends;
    QVector<Correspondence*> m_correspondence;


};
