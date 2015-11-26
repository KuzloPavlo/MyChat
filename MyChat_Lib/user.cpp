#include "user.h"


User::User(){ }

User::User( QString name,
            QString surname,
            QString login,
            QString password,
            QString ip_address) {


    this->name = name;
    this->surname = surname;
    this->login = login;
    this->password = password;
    this->ip_address = ip_address;
}

void User::Test (){


    qDebug () << "Hello from MyChat_Lib user";
}
