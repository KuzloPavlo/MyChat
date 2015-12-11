#include <QDataStream>
#include "clientsocket.h"
#include "server.h"


Server::Server(QObject *parent) : QObject(parent)
{
    m_pserver = new QTcpServer(this);

    connect(m_pserver, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    if (!m_pserver->listen (QHostAddress::Any,3030))
    {
        qDebug() << "Server could not start!" << endl;
    }
    else
    {
        qDebug() << "Server started!" << endl;
    }
}



void Server::slotNewConnection()
{
    QTcpSocket *pSocket = m_pserver->nextPendingConnection();

    connect(pSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    m_nnextBlockSize = 0;  // ??????????????
}




void Server::slotReadClient()
{
    quint8 requestType;
    QTcpSocket *pclientSocket = (QTcpSocket*) sender();
    QDataStream in (pclientSocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_nnextBlockSize == 0)
    {
        if (pclientSocket->bytesAvailable() < sizeof(quint16))
            return;
        in >> m_nnextBlockSize;
    }

    if (pclientSocket->bytesAvailable() < m_nnextBlockSize)
        return;
    in >> requestType;

    qDebug() << static_cast<MagicNumber> (requestType);  // здесь печатаю
    qDebug() << "Server server.cpp stroka 53";

    switch (static_cast<MagicNumber>(requestType))
    {

    case REGISTRATION:
        regProcessingResponses(m_users.addUser(&in), pclientSocket);
        break;

    case AUTHORIZATION:
        authProcessingResponses(m_users.authorizeUser(&in), pclientSocket);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}




void Server::regProcessingResponses(MagicNumber respond,
                                    QTcpSocket *psocketForAnswers)
{

    QByteArray regResponseBlock;

    QDataStream out (&regResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(REGISTRATION)
        << quint8(respond);

    out.device()->seek(0);
    out << quint16 (regResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(regResponseBlock);

}




void Server::authProcessingResponses(MagicNumber respond,
                                     QTcpSocket *psocketForAnswers)
{

QByteArray authResponseBlock;

    QDataStream out (&authResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(AUTHORIZATION)
        << quint8(respond);

    out.device()->seek(0);
    out << quint16 (authResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(authResponseBlock);

}
