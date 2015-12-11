#include "user.h"


User::User()
{

}

User::User( QString *pname,
            QString *psurname,
            QString *plogin,
            QString *ppassword,
            QString *pipAddress)
{
    this->m_name = *pname;
    this->m_surname = *psurname;
    this->m_login = *plogin;
    this->m_password = *ppassword;
    this->m_ipAddress = *pipAddress;

    qDebug()<< this->m_name;
    qDebug()<< this->m_surname;
    qDebug()<< this->m_login;
    qDebug()<< this->m_password;
    qDebug()<< this->m_ipAddress;
    qDebug()<< "LIB user.cpp s 20-25";
}

QString User::showName()
{
    return this->m_name;
}

QString User::showSurname()
{
    return this->m_surname;
}

QString User::showLogin()
{
    return this->m_login;
}

QString User::showPassword()
{
    return this->m_password;
}

QString User::showIPAddress()
{
    return this->m_ipAddress;
}
