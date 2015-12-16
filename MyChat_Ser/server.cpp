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

    qDebug() << static_cast<ReturnValues> (requestType);  // здесь печатаю
    qDebug() << "Server server.cpp stroka 53";

    switch (static_cast<MessageTypes>(requestType))
    {

    case registration:
        regProcessingResponses(m_users.addUser(&in), pclientSocket);
        break;

    case authorization:
        authProcessingResponses(m_users.authorizeUser(&in), pclientSocket);
        break;

    case add_friend:
        addFriendProcessingResponses(m_users.addFriend(&in), pclientSocket);
        break;

    case get_friends:
        getUserFriends(m_users.getUserFriends(&in), pclientSocket);
        break;

    case remove_friend:
        removingFriend(m_users.removingFriend(&in), pclientSocket);
        break;

    case search_friend:
        searchFriend(m_users.seatrchFriend(&in), pclientSocket);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}




void Server::regProcessingResponses(ReturnValues respond,
                                    QTcpSocket *psocketForAnswers)
{

    QByteArray regResponseBlock;

    QDataStream out (&regResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(registration)
        << quint8(respond);

    out.device()->seek(0);
    out << quint16 (regResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(regResponseBlock);

}





void Server::authProcessingResponses(ReturnValues respond,
                                     QTcpSocket *psocketForAnswers)
{

    QByteArray authResponseBlock;

    QDataStream out (&authResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(authorization)
        << quint8(respond);

    out.device()->seek(0);
    out << quint16 (authResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(authResponseBlock);

}





void Server::searchFriend(QVector<User> potentialFriends,
                          QTcpSocket *psocketForAnswers)
{
    QByteArray potentialFriendsBlock;

    QDataStream out (&potentialFriendsBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (search_friend);

    for (int i = 0; i < potentialFriends.size(); i++)
    {
        out << QString (potentialFriends[i].showName())
            << QString (potentialFriends[i].showSurname())
            << QString (potentialFriends[i].showLogin())
            << QString (potentialFriends[i].showIPAddress());
    }

    out.device()->seek(0);
    out << quint16 (potentialFriendsBlock.size() - sizeof(quint16));

    psocketForAnswers->write(potentialFriendsBlock);

}




void Server::addFriendProcessingResponses(ReturnValues respond,
                                          QTcpSocket *psocketForAnswers)
{
    QByteArray addFriendResponseBlock;

    QDataStream out (&addFriendResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (add_friend)
        << quint8 (respond);

    out.device()->seek(0);
    out << quint16(addFriendResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(addFriendResponseBlock);

}





void Server::getUserFriends(QVector<User> friends,
                            QTcpSocket *psocketForAnswers)
{
    QByteArray getFriendsBlock;

    QDataStream out (&getFriendsBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (get_friends);

    for (int i = 0; i < friends.size(); i++)
    {
        out << QString (friends[i].showName())
            << QString (friends[i].showSurname())
            << QString (friends[i].showLogin())
            << QString (friends[i].showIPAddress());
    }

    out.device()->seek(0);
    out << quint16 (getFriendsBlock.size() - sizeof(quint16));
    psocketForAnswers->write(getFriendsBlock);

}




void Server::removingFriend(ReturnValues respond,
                            QTcpSocket *psocketForAnswers)
{
    QByteArray removeFriendBlock;

    QDataStream out (&removeFriendBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(remove_friend)
        << quint8 (respond);

    out.device()->seek(0);
    out << quint16 (removeFriendBlock.size() - sizeof(quint16));
    psocketForAnswers->write(removeFriendBlock);

}
