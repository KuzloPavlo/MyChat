#pragma once

#include <QDebug>
#include <QString>
#include "returnvalues.h"
#include "correspondence.h"
#include <interlocutor.h>
#include <QTcpSocket>

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

    void addFriend(const Interlocutor &pfriend);
    QVector<User> getFriends();
    void removeFriend(const QString &friendLogin);



private:
    QString m_name;
    QString m_surname ;
    QString m_login ;
    QString m_password ;
    QString m_ipAddress;
    QTcpSocket* m_pUserSocket;

    QVector<User*> m_friends;                   // DEL
    QVector<Correspondence*> m_correspondence;  // DEL

    QVector<Interlocutor> m_interlocutors;      // USE
};
