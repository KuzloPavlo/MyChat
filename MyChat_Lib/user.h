#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>

class User
{
private:

    // 12:29
    QString name;
    QString surname ;
    QString login ;
    QString password ;
    QString ip_address;
public:
    User();
    //--------------------------------------------------+
    //  Add new User Function                           |
    //--------------------------------------------------+
    User( QString name,
          QString surname,
          QString login,
          QString password,
          QString ip_address);
    //--------------------------------------------------+
    //  Add new User Function                           |
    //--------------------------------------------------+


    QString showName();
    QString showSurname();
    QString showLogin();
    QString showPassword();
    QString showIP_address();
};

#endif // USER_H
