#include "server.h"


Server::Server(QObject *parent) : QObject(parent)
{

    server = new QTcpServer(this);

    connect (server,
             SIGNAL (newConnection ()),
             this,
             SLOT (newConnection ()));

    if (!server->listen (QHostAddress::Any,3030)) {

        qDebug () << "Server could not start!" << endl;

    }

    else {

        qDebug () << "Server started!" << endl;
    }

}

void Server::newConnection (){

    QTcpSocket *socket = server->nextPendingConnection ();

    socket -> write ("Hello client\r\n");

    socket->flush ();

    socket->waitForBytesWritten (3000);

 //   si

    socket->close ();

}
