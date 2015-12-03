#include "server.h"
#include <QDataStream>
#include "clientsocket.h"

Server::Server(QObject *parent) : QObject(parent)
{

    server = new QTcpServer(this);

    connect (server,
             SIGNAL (newConnection ()),
             this,
             SLOT (SlotnewConnection ()));

    if (!server->listen (QHostAddress::Any,3030)) {

        qDebug () << "Server could not start!" << endl;

    }

    else {

        qDebug () << "Server started!" << endl;
    }
}

void Server::SlotnewConnection (){

    QTcpSocket *socket = server->nextPendingConnection ();

    connect (socket, SIGNAL (readyRead ()),this, SLOT (slotReadClient()));

    nextBlockSize = 0;
}

void Server::slotReadClient ()
{
    quint8 requestType;
    QString name;
    QString surname ;
    QString login ;
    QString password ;
    QString ip_address;

    QTcpSocket *pClientSocket = (QTcpSocket*) sender();

    QDataStream in (pClientSocket);
    in.setVersion (QDataStream::Qt_5_5);




    if (nextBlockSize == 0)
    {
        if (pClientSocket->bytesAvailable ()< sizeof (quint16))
            return;

        in>>nextBlockSize;
    }

    if (pClientSocket->bytesAvailable ()< nextBlockSize)
        return;

    in>>requestType >> name >> surname >> login >> password;

    qDebug () << requestType;
    qDebug () << name;
    qDebug () << surname;
    qDebug () << login;
    qDebug () << password;

    nextBlockSize = 0;
}
