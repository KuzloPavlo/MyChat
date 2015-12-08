#include "users.h"

int Users::addUser(QDataStream *newUserInfo)
{
    qDebug() << "LIB users.cpp 5";
    QString name ;
    QString surname;
    QString login;
    QString password;
    QString ip_address = "127.0.0.1";  // нужно реализовввать получение IP адреса

    newUserInfo->setVersion (QDataStream::Qt_5_5);
    *newUserInfo>> name >> surname >> login >> password;

    qDebug() << name;
    qDebug() << surname;
    qDebug() << login;
    qDebug() << password;
    qDebug() << "LIB users.cpp s 14-18";

    //-----------------------------------
    // проверка на свободній логін
    //----------------------------------

    if (UserVector.size ()) {
    for (int i = 0; i < UserVector.size (); i++)
    {
        if (login != UserVector[i].showLogin()) //if (strcmp (login, UserVector[i].showLogin ()))
        {
            User newUser(name,surname,login,password,ip_address);
            UserVector.push_back (newUser);
            signalRegistered (UserVector[UserVector.size ()-1].showLogin(),UserVector[UserVector.size ()-1].showPassword());
        }

    }
      }
    else {

        User newUser(name,surname,login,password,ip_address);
        UserVector.push_back (newUser);
        signalRegistered (UserVector[UserVector.size ()-1].showLogin(),UserVector[UserVector.size ()-1].showPassword());
    }
    //----------------------------------


    return 0;

}



int Users::showUsersLogin(QDataStream *AuthoInfo)
{
 for(int i = 0; i < UserVector.size(); i++)
     UserVector[i].showLogin();
 QString login;
 QString password;
 AuthoInfo->setVersion (QDataStream::Qt_5_5);
 *AuthoInfo>> login >> password;

 qDebug() << login;
 qDebug() << password;

 //------------------------------
 for (int i = 0; i < UserVector.size (); i++)
 {
   qDebug()<< UserVector[i].showLogin ();
 }

 //-----------------------------
 return 0;
}


void Users::signalRegistered (QString login, QString password){

}

void Users::signalLoginBusu (){

}
