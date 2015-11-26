#ifndef USER_H
#define USER_H

#include <QDebug>
#include <QString>

class User
{
private:
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


    void Test();
};

#endif // USER_H
