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
   // QDataStream out ();
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

    switch (static_cast<MessageTypes>(requestType))
    {

    case MessageTypes::registration:         // regProcessingResponses(m_users.addUser(&in), pclientSocket);
        registration(&in,pclientSocket);
        break;

    case MessageTypes::authorization:        //  authProcessingResponses(m_users.authorizeUser(&in), pclientSocket);
        authorization(&in,pclientSocket);
        break;

    case search_friend:                      //searchFriend(m_users.seatrchFriend(&in), pclientSocket);
    searchFriend(&in,pclientSocket);
        break;

    case MessageTypes::add_friend:
        addFriendProcessingResponses(m_users.addFriend(&in), pclientSocket);
        break;

    case MessageTypes::get_friends:
        getUserFriends(m_users.getUserFriends(&in), pclientSocket);

        break;

    case MessageTypes::remove_friend:
        removingFriend(m_users.removingFriend(&in), pclientSocket);
        break;



    default:
        break;


    }

//     out.device()->seek(0);
//    out << quint16 (regResponseBlock.size() - sizeof(quint16));
//    psocketForAnswers->write(regResponseBlock);

    requestType = 0;
    m_nnextBlockSize = 0;
}





void Server::registration(QDataStream *pNewUserInfo,
                          QTcpSocket *psocketForAnswers)
{
    QString name ;
    QString surname;
    QString login;
    QString password;
    QString ipAddress = "127.0.0.1";  // Нужно реализовввать получение IP адреса.

    pNewUserInfo->setVersion (QDataStream::Qt_5_5);
    *pNewUserInfo >> name
            >> surname
            >> login
            >> password;

    ReturnValues respond = m_users.addUser(
                &name,
                &surname,
                &login,
                &password,
                &ipAddress);

    QByteArray regResponseBlock;

    QDataStream out (&regResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::registration)
        << quint8(respond);

    if (respond == ReturnValues::registered)
    {
        User user = m_users.getUser(&login);
        out << user.showName()
            << user.showSurname()
            << user.showLogin()
            << user.showPassword()
            << user.showIPAddress();

        qDebug() << "Registered new User:";
        qDebug() << "Name:     " << user.showName();
        qDebug() << "Surname:  " << user.showSurname();
        qDebug() << "Login:    " << user.showLogin();
        qDebug() << "Password: " << user.showPassword();
        qDebug() << "IPAdress: " << user.showIPAddress() << endl << endl;
    }

    out.device()->seek(0);
    out << quint16 (regResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(regResponseBlock);

}


void Server::authorization(QDataStream *pAuthoInfo,
                           QTcpSocket *psocketForAnswers)
{
    QString login;
    QString password;

    pAuthoInfo->setVersion(QDataStream::Qt_5_5);
    *pAuthoInfo >> login
            >> password;

    ReturnValues respond = m_users.authorizeUser(&login, &password);

    QByteArray authResponseBlock;

    QDataStream out (&authResponseBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::authorization)
        << quint8(respond);

    if (respond == ReturnValues::authorized)
    {
        User user = m_users.getUser(&login);
        out << QString(user.showName())
            << QString(user.showSurname())
            << QString(user.showLogin())
            << QString(user.showPassword())
            << QString(user.showIPAddress());

        // Также необхолимо добавить отправку списка контактов
        // и отправку чатов

        qDebug() << "Authorized User:";
        qDebug() << "Login:    " << user.showLogin();
        qDebug() << "IPAdress: " << user.showIPAddress() << endl << endl;

    }

    out.device()->seek(0);
    out << quint16 (authResponseBlock.size() - sizeof(quint16));
    psocketForAnswers->write(authResponseBlock);

}



void Server::searchFriend(QDataStream *pFriendInfo,
                          QTcpSocket *psocketForAnswers)
{
    QString dataFriend;
    pFriendInfo->setVersion(QDataStream::Qt_5_5);
    *pFriendInfo >> dataFriend;

    QVector<User> potentialFriends = m_users.seatrchFriend(&dataFriend);

    QByteArray potentialFriendsBlock;

    QDataStream out (&potentialFriendsBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::search_friend)
        << quint8 (potentialFriends.size());

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

//        // qDebug() << "Server.cpp searchFriend" << potentialFriends[i].showLogin();
//        out << QString (potentialFriends[i].showName())
//            << QString (potentialFriends[i].showSurname())
//            << QString (potentialFriends[i].showLogin())
//            << QString (potentialFriends[i].showIPAddress());
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
