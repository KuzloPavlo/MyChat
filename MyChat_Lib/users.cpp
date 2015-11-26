#include "users.h"

//Users::Users()
//{

//}




//--------------------------------------------------+
//  Add new User Function                           |
//--------------------------------------------------+
     int Users::addUser(
             QString name,
             QString surname,
             QString login,
             QString password,
             QString ip_address) {

         User newUser(name,surname,login,password,ip_address);

          UserVector.push_back (newUser);





return 0;

     }

//--------------------------------------------------+
//  Add new User Function                           |
//--------------------------------------------------+

void Users::Test (){


    qDebug () << "Hello from MyChat_Lib users";
}


