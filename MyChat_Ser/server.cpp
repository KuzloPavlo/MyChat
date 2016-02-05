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
    connect(pSocket, SIGNAL(disconnected()), this, SLOT(slotDisconnectClient()));

    m_nnextBlockSize = 0;
}


void Server::slotDisconnectClient()
{
    QTcpSocket *pclientSocket = (QTcpSocket*) sender();

    m_users.disconnectUser(pclientSocket);
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

    case MessageTypes::registration:
        registerUser(&in, &out);
        break;

    case MessageTypes::authorization:
        authorizationUser(&in, &out, pclientSocket);
        break;

    case MessageTypes::searchFriend:
        findFriend(&in, &out);
        break;

    case MessageTypes::addFriend:
        addFriend(&in, &out);
        break;

    case MessageTypes::removeFriend:
        removeFriend(&in, &out);
        break;

    case MessageTypes::getFriends:
        getFriends(&in, &out);
        break;

    case MessageTypes::getCorrespondence:
        getCorrespondence(&in, &out);
        break;

    case MessageTypes::message:
        receiveMessage(&in, &out);
        break;

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

    *out << quint8(MessageTypes::registration)
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



void Server::authorizationUser(QDataStream *in, QDataStream *out, QTcpSocket *pClientSocket)
{
    QString login;
    QString password;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> login >> password;

    ReturnValues respond = m_users.authorizeUser(login, password, pClientSocket);

    *out << quint8(MessageTypes::authorization)
         << quint8(respond);

    if (respond == ReturnValues::authorized)
    {
        User user = m_users.getUser(login);

        *out << user.getName()
             << user.getSurname()
             << user.getLogin()
             << user.getIPAddress();

        qDebug() << "Authorized User:";
        qDebug() << "Login:    " << user.getLogin();
    }
}



void Server::findFriend(QDataStream *in, QDataStream *out)
{
    QString tokenFriend;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> tokenFriend;

    //----------------------
    // qDebug() << tokenFriend;
    //---------------------

    QVector<User> potentialFriends = m_users.findFriend(tokenFriend);

    *out << quint8 (MessageTypes::searchFriend)
         << quint8 (potentialFriends.size());

    for (int t = 0; t < potentialFriends.size(); t++)
    {
        *out << potentialFriends[t].getName()
             << potentialFriends[t].getSurname()
             << potentialFriends[t].getLogin();

        qDebug() << "Server";
        qDebug() << potentialFriends[t].getLogin();
    }
}



void Server::addFriend(QDataStream *in, QDataStream *out)
{
    QString userLogin;
    QString friendLogin;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> userLogin >> friendLogin;

    ReturnValues respond = m_users.addFriend(userLogin,friendLogin);

    *out << quint8 (MessageTypes::addFriend)
         << quint8 (respond);

    if (respond == ReturnValues::addedFriend)
    {
        User friendUser = m_users.getUser(friendLogin);

        *out << friendUser.getName()
             << friendUser.getSurname()
             << friendUser.getLogin()
             << friendUser.getIPAddress();

        QTcpSocket *pfriendSocket = NULL;
        pfriendSocket = m_users.getUserTcpSocket(friendLogin);

        if(pfriendSocket)
        {
            QByteArray block;
            QDataStream tofriend (&block, QIODevice::WriteOnly);

            tofriend.setVersion(QDataStream::Qt_5_5);
            tofriend << quint16(0)
                     << quint8 (MessageTypes::addFriend)
                     << quint8 (respond);

            User user = m_users.getUser(userLogin);

            tofriend << user.getName()
                     << user.getSurname()
                     << user.getLogin()
                     << user.getIPAddress();

            if (block.size())
            {
                tofriend.device()->seek(0);
                tofriend << quint16 (block.size() - sizeof(quint16));
                pfriendSocket->write(block);
            }
        }
        qDebug() << userLogin << " & " << friendLogin;
        qDebug() << " now friends." << endl << endl;
    }
}





void Server::removeFriend(QDataStream *in, QDataStream *out)
{
    QString userLogin;
    QString friendLogin;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> userLogin >> friendLogin;

    ReturnValues respond = m_users.removeFriend(userLogin,friendLogin);

    *out << quint8 (MessageTypes::removeFriend)
         << quint8 (respond);

    if (respond == ReturnValues::removedFriend)
    {
        qDebug() << userLogin << " & " << friendLogin;
        qDebug() << " now NOT friends" << endl << endl;

    }
}





void Server::getFriends(QDataStream *in, QDataStream *out)
{
    QString login;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> login;

    QVector<User> friends =  m_users.getUserFriends(login);

    *out << quint8 (MessageTypes::getFriends)
         << quint8 (friends.size());

    for(int i =0; i < friends.size(); i++)
    {
        *out << friends[i].getName()
             << friends[i].getSurname()
             << friends[i].getLogin();
    }

}


void Server::getCorrespondence(QDataStream *in, QDataStream *out)
{qDebug()<< "1getCorrespondence1";
    QString login;

    in->setVersion(QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);
qDebug()<< "1getCorrespondence1";
    *in >> login;
qDebug()<< "1getCorrespondence11";
    QVector<Correspondence> correspondence = m_users.getUserCorrespondence(login);
qDebug()<< "1getCorrespondence1";
    *out << quint8 (MessageTypes::getCorrespondence)
         << quint8(correspondence.size());
qDebug()<< "1getCorrespondence1";
    for(int j = 0; j < correspondence.size(); j++)
    {
    qDebug()<< "1getCorrespondence5";
        *out << quint8 (correspondence[j].getIDNumber());
        qDebug()<< "1getCorrespondence6";
        QVector<QString> participants = correspondence[j].getParticipants();
        qDebug()<< "1getCorrespondence7";
        *out << quint8 (participants.size());
qDebug()<< "1getCorrespondence8";
        for(int i = 0; i < participants.size(); i++)
        {
        qDebug()<< "1getCorrespondence9";
            *out << participants[i];
            qDebug()<< "1getCorrespondence10";
        }
qDebug()<< "1getCorrespondence1";
        QVector<Message> messages = correspondence[j].getCorrespondence();
        *out << quint8(messages.size());

        for(int k = 0; k < messages.size(); k++)
        {
            *out << messages[k].mSender
                 << messages[k].mRecipient
                 << messages[k].mMessageText
                 << messages[k].mDataTime;
        }
    }qDebug()<< "1getCorrespondence2";
}



void Server::receiveMessage(QDataStream *in, QDataStream *out)
{
    Message newmessage;

    in->setVersion (QDataStream::Qt_5_5);
    out->setVersion(QDataStream::Qt_5_5);

    *in >> newmessage.mSender
            >> newmessage.mRecipient
            >> newmessage.mMessageText
            >> newmessage.mDataTime;

    m_users.receiveMessage(newmessage);

    QTcpSocket *pRecipientSocket = NULL;
    pRecipientSocket = m_users.getUserTcpSocket(newmessage.mRecipient);


    if(pRecipientSocket)
    {

        QByteArray block;
        QDataStream toRecipient (&block, QIODevice::WriteOnly);
        toRecipient.setVersion(QDataStream::Qt_5_5);
        toRecipient << quint16(0);

        toRecipient << quint8(MessageTypes::message)
                    << newmessage.mSender
                    << newmessage.mRecipient
                    << newmessage.mMessageText
                    << newmessage.mDataTime;

        toRecipient.device()->seek(0);
        toRecipient << quint16 (block.size() - sizeof(quint16));
        pRecipientSocket->write(block);
    }

    //    *out << quint8(MessageTypes::message) // ЗАЧЕМ????????????????????
    //         << newmessage.mSender
    //         << newmessage.mRecipient
    //         << newmessage.mMessageText
    //         << newmessage.mDataTime;
}
