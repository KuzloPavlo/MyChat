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
    Server server;

    return a.exec();
}
