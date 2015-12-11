#pragma once

#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>

class User
{
public:
    User();
    User( QString *pname,
          QString *psurname,
          QString *plogin,
          QString *ppassword,
          QString *pipAddress);

    QString showName();
    QString showSurname();
    QString showLogin();
    QString showPassword();
    QString showIPAddress();

private:
    QString m_name;
    QString m_surname ;
    QString m_login ;
    QString m_password ;
    QString m_ipAddress;


};

#endif // USER_H
