#include <QDataStream>

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

    QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16(0);

    if (m_nnextBlockSize == 0)
    {
        if (pclientSocket->bytesAvailable() < sizeof(quint16))
            return;
        in >> m_nnextBlockSize;
    }

    if (pclientSocket->bytesAvailable() < m_nnextBlockSize)
        return;
    in >> requestType;

    switch (static_cast<MessageTypes>(requestType))
    {

    case MessageTypes::registration:         // regProcessingResponses(m_users.addUser(&in), pclientSocket);
        registerUser(&in, &out);
        break;

    case MessageTypes::authorization:        //  authProcessingResponses(m_users.authorizeUser(&in), pclientSocket);
        authorizationUser(&in, &out);
        break;

    case MessageTypes::searchFriend:                      //searchFriend(m_users.seatrchFriend(&in), pclientSocket);
        findFriend(&in, &out);
        break;

        //    case MessageTypes::addFriend:
        //        addFriendProcessingResponses(m_users.addFriend(&in), pclientSocket);
        //        break;

        //    case MessageTypes::getFriends:
        //        getUserFriends(m_users.getUserFriends(&in), pclientSocket);

        //        break;

        //    case MessageTypes::removeFriend:
        //        removingFriend(m_users.removingFriend(&in), pclientSocket);
        //        break;



    default:
        break;


    }

    if (block.size())
    {
        out.device()->seek(0);
        out << quint16 (block.size() - sizeof(quint16));
        pclientSocket->write(block);
    }
    requestType = 0;
    m_nnextBlockSize = 0;
    block.clear();
}





void Server::registerUser(QDataStream *in, QDataStream *out)
{
    QString name ;
    QString surname;
    QString login;
    QString password;
    QString ipAddress = "127.0.0.1";  // Нужно реализовввать получение IP адреса.

    in->setVersion (QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> name >> surname >> login >> password;

    ReturnValues respond = m_users.addUser(
                name,
                surname,
                login,
                password,
                ipAddress);

    *out // << quint16(0)
         << quint8(MessageTypes::registration)
         << quint8(respond);

    if (respond == ReturnValues::registered)
    {
        User user = m_users.getUser(login);
        *out << user.getLogin()
             << user.getPassword();

        qDebug() << "Registered new User:";
        qDebug() << "Name:     " << user.getName();
        qDebug() << "Surname:  " << user.getSurname();
        qDebug() << "Login:    " << user.getLogin();
        qDebug() << "Password: " << user.getPassword();
        qDebug() << "IPAdress: " << user.getIPAddress() << endl << endl;
    }
}


void Server::authorizationUser(QDataStream *in, QDataStream *out)
{
    QString login;
    QString password;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> login >> password;

    ReturnValues respond = m_users.authorizeUser(login, password);

    *out //<< quint16(0)
         << quint8(MessageTypes::authorization)
         << quint8(respond);

    if (respond == ReturnValues::authorized)
    {
        User user = m_users.getUser(login);

        *out << user.getName()
             << user.getSurname()
             << user.getLogin()   // << user.getPassword()  //
             << user.getIPAddress();

        // Также необхолимо добавить отправку списка контактов  !!!ОТПРАВКУ КОНТАКТОВ И ЧАТОВ ВІПОЛНЯТЬ ОТДЕЛЬНО
        // и отправку чатов

        qDebug() << "Authorized User:";
        qDebug() << "Login:    " << user.getLogin();
        qDebug() << "IPAdress: " << user.getIPAddress() << endl << endl;

    }
}



void Server::findFriend(QDataStream *in, QDataStream *out)
{
    QString tokenFriend;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> tokenFriend;

    QVector<User> potentialFriends = m_users.findFriend(tokenFriend);

    *out //<< quint16 (0)
        << quint8 (MessageTypes::searchFriend)
        << quint8 (potentialFriends.size());

    for (int i = 0; i < potentialFriends.size(); i++)
    {
        *out << QString (potentialFriends[i].getName())
            << QString (potentialFriends[i].getSurname())
            << QString (potentialFriends[i].getLogin())
            << QString (potentialFriends[i].getIPAddress());
    }
}



//void Server::searchFriend(QVector<User> potentialFriends,
//                          QTcpSocket *psocketForAnswers)
//{
//    QByteArray potentialFriendsBlock;

//    QDataStream out (&potentialFriendsBlock, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_5);

//    out << quint16 (0)
//        << quint8 (search_friend)
//        << quint8 (potentialFriends.size());

//    for (int i = 0; i < potentialFriends.size(); i++)
//    {

//        // qDebug() << "Server.cpp searchFriend" << potentialFriends[i].getLogin();
//        out << QString (potentialFriends[i].getName())
//            << QString (potentialFriends[i].getSurname())
//            << QString (potentialFriends[i].getLogin())
//            << QString (potentialFriends[i].getIPAddress());
//    }

//    out.device()->seek(0);
//    out << quint16 (potentialFriendsBlock.size() - sizeof(quint16));
//    psocketForAnswers->write(potentialFriendsBlock);

//}




void Server::addFriendProcessingResponses(ReturnValues respond,
                                          QTcpSocket *psocketForAnswers)
{
    QByteArray addFriendResponseBlock;

    QDataStream out (&addFriendResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (MessageTypes::addFriend)
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
        << quint8 (MessageTypes::getFriends);

    for (int i = 0; i < friends.size(); i++)
    {
        out << QString (friends[i].getName())
            << QString (friends[i].getSurname())
            << QString (friends[i].getLogin())
            << QString (friends[i].getIPAddress());
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
        << quint8(MessageTypes::removeFriend)
        << quint8 (respond);

    out.device()->seek(0);
    out << quint16 (removeFriendBlock.size() - sizeof(quint16));
    psocketForAnswers->write(removeFriendBlock);

}
