#include "user.h"


User::User(){ }

User::User( QString name,
            QString surname,
            QString login,
            QString password,
            QString ip_address)
{
    this->name = name;
    this->surname = surname;
    this->login = login;
    this->password = password;
    this->ip_address = ip_address;

    qDebug ()<< this->name;
    qDebug ()<< this->surname;
    qDebug ()<< this->login;
    qDebug ()<< this->password;
    qDebug ()<< this->ip_address;
    qDebug() << "LIB user.cpp s 20-25";
}

QString User::showLogin()
{
    return this->login;
}

QString User::showPassword()
{
    return this->password;
}

QString User::showName()
{
    return this->name;
}

