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

    if (!server->listen (QHostAddress::Any,3030))
    {
        qDebug () << "Server could not start!" << endl;
    }
    else
    {
        qDebug () << "Server started!" << endl;
    }
}

void Server::SlotnewConnection()
{
    QTcpSocket *socket = server->nextPendingConnection ();
    connect (socket, SIGNAL (readyRead ()),this, SLOT (slotReadClient()));

    nextBlockSize = 0;  // ??????????????
}

void Server::slotReadClient()
{
    quint8 requestType;
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
    in>>requestType;

    qDebug() << (char)requestType;  // здесь печатаю
    qDebug()<< "Server server.cpp stroka 53";

    switch (static_cast<char>(requestType))
    {

    case 'R':/*int resultcode = */users.addUser (&in);
        // метод которій будет обрабатівать возращ значение
        break;
    case 'A': users.showUsersLogin(&in); // перероби на норм

        break;
    default:
        break;
    }

    requestType =0;
    nextBlockSize = 0;
}
