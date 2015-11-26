#include <QCoreApplication>
#include "server.h"
#include "user.h"
#include "users.h"
#include "friends.h"
#include "participantschat.h"
#include "community.h"
#include <QString>
#include <QDebug>



int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//---------------------------------------+
//  Test connect with library            |
//---------------------------------------+
    User us;
    us.Test ();
    Users usrs;
    usrs.Test ();
    Community comm;
    comm.Test ();
    Friends fr;
    fr.Test ();
    ParticipantsChat pr;
    pr.Test ();
//---------------------------------------+
//  Test connect with library            |
//---------------------------------------+
    Users users;
    Server server;
    return a.exec();
}
