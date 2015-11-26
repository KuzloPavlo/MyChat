#ifndef USERS_H
#define USERS_H
#include "community.h"
#include <QDebug>
#include <QVector>
#include <user.h>

class Users:public Community
{
private:
    QVector<User> UserVector;
public:
   // Users();

//--------------------------------------------------+
//  Add new User Function                           |
//--------------------------------------------------+
     int addUser(
             QString name ,
             QString surname,
             QString login,
             QString password,
             QString ip_address);
//--------------------------------------------------+
//  Add new User Function                           |
//--------------------------------------------------+

     void Test();

};

#endif // USERS_H
