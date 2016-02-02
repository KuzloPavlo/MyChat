#include "Client.h"

Client::Client(QObject *parent) : QObject(parent), m_nnextBlockSize(0)
{
    m_psocket = new QTcpSocket(this);
    m_psocket->connectToHost ("127.0.0.1", 3030);

    if (m_psocket->waitForConnected(3000))
    {
        qDebug() << "Connected!";
    }

    else
    {
        qDebug() << "Not connected!";
    }

    connect(m_psocket, SIGNAL(readyRead()), this, SLOT(slotReadServer()));
    m_nnextBlockSize = 0;

    QDataStream temp (&m_block,QIODevice::WriteOnly);  //
    m_out =& temp;                                      //
    m_out->setVersion(QDataStream::Qt_5_5);             //
    *m_out << quint16(0);                              //
}

void Client::sendToServer(QDataStream *out, QByteArray *block)
{

    //    m_out->setVersion(QDataStream::Qt_5_5);
    //        m_out->device()->seek(0);
    //        *m_out << quint16 (m_block.size() - sizeof(quint16));
    //        m_psocket->write(m_block);
    //        m_block.clear();
    //        *m_out <<quint16(0);


    // out->setVersion(QDataStream::Qt_5_5);

    out->device()->seek (0);
    *out << quint16 (block->size() - sizeof(quint16));
    m_psocket->write(*block);
}


void Client::slotReadServer()
{
    quint8 requestType;

    QDataStream in (m_psocket);
    in.setVersion(QDataStream::Qt_5_5);

    if (m_nnextBlockSize == 0)
    {
        if (m_psocket->bytesAvailable() < sizeof(quint16))
            return;
        in >> m_nnextBlockSize;
    }

    if (m_psocket->bytesAvailable() < m_nnextBlockSize)
        return;

    in >> requestType;

    switch (static_cast<MessageTypes>(requestType))
    {

    case MessageTypes::registration:
        this->processRegistrationResponse(&in);
        break;

    case MessageTypes::authorization:
        this->processAuthorizationResponse(&in);
        break;

    case MessageTypes::searchFriend:
        this->processFindFriendResponse(&in);
        break;

    case MessageTypes::addFriend:
        this->processAddFriendResponse(&in);
        break;

    case MessageTypes::getFriends:
        this->setFriendsAndCorrespondence(&in);
        break;

    case MessageTypes::message:
        this->receiveMessage(&in);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}



void Client::slotSetUser(const QString &pname,      // Возможно етот слот и НЕНУЖЕН
                         const QString &psurname,
                         const QString &plogin,
                         const QString &ppassword,
                         const QString &pipAddress)
{
    User user(pname,psurname,plogin,ppassword,pipAddress);
    this->m_user = user;
}



void Client::addDataUser(
        const QString &pname,
        const QString &psurname,
        const QString &plogin,
        const QString &ppassword,
        const QString &pipAddress)
{
    User temp(pname,psurname, plogin, ppassword, pipAddress);
    m_user = temp;
}



User Client::getUser()
{
    User temp = m_user;
    return temp;
}



void Client::registerUser(const QString &name, const QString &surname, const QString &login, const QString &password)
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::registration)
        << name
        << surname
        << login
        << password;

    sendToServer(&out, &block );

    //    out.device()->seek (0);
    //    out << quint16 (block.size() - sizeof(quint16));
    //    m_psocket->write(block);
}



void Client::authorizationUser (const QString &login, const QString &password)
{
    QByteArray block;

    QDataStream out (&block,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::authorization)
        << login
        << password;

    out.device()->seek (0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}




void Client::findFriend(const QString &tokenFriend)
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::searchFriend)
        << tokenFriend;

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}




void Client::addFriend (const QString &loginFriend)
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (MessageTypes::addFriend)
        << m_user.getLogin()
        << loginFriend;

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);

}




void Client::removeFriend(const QString &loginFriend)
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (MessageTypes::removeFriend)
        << m_user.getLogin()
        << loginFriend;

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}


void Client::sendMessage(
        const QString &sender,
        const QString &recipient,
        const QString &messageText,
        const QDateTime &dataTime)
{

    Message outgoingMessage;
    outgoingMessage.mSender = sender;
    outgoingMessage.mRecipient = recipient;
    outgoingMessage.mMessageText = messageText;
    outgoingMessage.mDataTime = dataTime;

    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(m_Correspondence[i].findParticipants(sender,recipient))
        {
            m_Correspondence[i].addNewMessage(outgoingMessage);
            break;
        }
    }

    QByteArray block;

    QDataStream out (&block,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::message)
        << sender
        << recipient
        << messageText
        << dataTime;

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}


void Client::processRegistrationResponse(QDataStream *in)
{
    quint8 response;
    in->setVersion (QDataStream::Qt_5_5);
    *in >> response;

    switch (static_cast<ReturnValues>(response))
    {

    case ReturnValues::registered:
    {
        QString userLogin;
        QString userPassword;

        *in >> userLogin >> userPassword;

        emit signalRegistered(userLogin, userPassword);
    }
        break;

    case ReturnValues::loginBusy:
        emit signalLoginBusy();
        break;

    default:
        break;
    }
}




void Client::processAuthorizationResponse(QDataStream *in)
{
    quint8 response;

    in->setVersion (QDataStream::Qt_5_5);
    *in >> response;

    switch (static_cast<ReturnValues>(response))
    {

    case ReturnValues::authorized:
        setAuthorizedUser(in);
        break;

    case ReturnValues::wrongLogin:
        emit signalWrongLogin();
        break;

    case ReturnValues::wrongPassword:
        emit signalWrongPassword();
        break;

    case ReturnValues::isEmpty:
        emit signalIsEmty();
        break;

    default:
        break;
    }

}




void Client::setAuthorizedUser(QDataStream *in)
{
    in->setVersion (QDataStream::Qt_5_5);

    QString userName;
    QString userSurname;
    QString userLogin;
    QString userPassword = "";
    QString userIPAddress;

    *in >> userName
            >> userSurname
            >> userLogin
            >> userIPAddress;

    User tempUser(userName,
                  userSurname,
                  userLogin,
                  userPassword,
                  userIPAddress);

    this->m_user = tempUser;

    emit signalAuthorized(userName, userSurname, userLogin);
    getFriendsAndCorrespondence();
}




void Client::processFindFriendResponse(QDataStream *in)
{
    quint8 npotentialFriends;
    QVector<User>  potentialFriends;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> npotentialFriends;

    qDebug() << "nashel";

    for (int i = 0; i < static_cast<int>(npotentialFriends); i++)
    {
        QString potentialFriendName;
        QString potentialFriendSurname;
        QString potentialFriendLogin;
        QString emptyString = "";

        *in >> potentialFriendName
                >> potentialFriendSurname
                >> potentialFriendLogin;

        qDebug() << potentialFriendName;
        qDebug() << potentialFriendSurname;
        qDebug() << potentialFriendLogin;

        User tempFrined(
                    potentialFriendName,
                    potentialFriendSurname,
                    potentialFriendLogin,
                    emptyString,
                    emptyString);

        potentialFriends.push_back(tempFrined);
    }
    // emit signalFoundFriend(potentialFriends);

    m_potentialFriends = potentialFriends;

    for(int i = 0; i < m_potentialFriends.size(); i++)
    {
        emit signalFoundFriend(m_potentialFriends[i].getLogin());
    }
}



void Client::processAddFriendResponse(QDataStream *in){

    quint8 response;

    in->setVersion (QDataStream::Qt_5_5);
    *in >> response;

    switch (static_cast<ReturnValues>(response))
    {

    case ReturnValues::addedFriend:
        setNewFriend(in);
        break;

    default:
        break;
    }
}



void Client::setNewFriend(QDataStream *in)
{
    in->setVersion (QDataStream::Qt_5_5);

    QString friendName;
    QString friendSurname;
    QString friendLogin;
    QString friendPassword = "";
    QString friendIPAddress;

    *in >> friendName
            >> friendSurname
            >> friendLogin
            >> friendIPAddress;

    User tempFriend (friendName,
                     friendSurname,
                     friendLogin,
                     friendPassword,
                     friendIPAddress);

    //  emit this->signalNewFriend(tempFriend);
    m_friends.push_back(tempFriend);

    User *newFriend;
    for (int i = 0; i < m_friends.size(); i++)
    {
        if(friendLogin == m_friends[i].getLogin())
        {
            newFriend =& m_friends[i];
            break;
        }
    }

    Correspondence newCorrespondence(newFriend,&m_user); //create local correspondence

    m_Correspondence.push_back(newCorrespondence);

}


void Client::getFriendsAndCorrespondence()
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::getFriends)
        << m_user.getLogin();

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}


void Client::setFriendsAndCorrespondence(QDataStream *in)
{
    int nfriends;
    // int ncorrespondence;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> nfriends;

    for(int i = 0; i < nfriends; i++)
    {
        QString friendName;
        QString friendSurname;
        QString friendLogin;
        QString emptyString = "";

        *in >> friendName
                >> friendSurname
                >> friendLogin;

        User tempFriend(
                    friendName,
                    friendSurname,
                    friendLogin,
                    emptyString,
                    emptyString
                    );
        m_friends.push_back(tempFriend);
    }

    // *in >> ncorrespondence;

    //    for(int j = 0; j < ncorrespondence; j++)
    //    {
    //        Correspondence messages;
    //        int nmessages;

    //        *in >> nmessages;

    //        for(int k = 0; k < nmessages; k++)
    //        {
    //            Message tempMessage;

    //            *in >> tempMessage.mSender
    //                    >> tempMessage.mRecipient
    //                    >> tempMessage.mMessageText
    //                    >> tempMessage.mDataTime;

    //            messages.addNewMessage(tempMessage);
    //        }
    //        m_Correspondence.push_back(messages);
    //    }

    //    for(int h = 0; h < m_Correspondence.size(); h++)
    //    {
    //        Message temp = m_Correspondence[h].getLastMessage();
    //        for(int n = 0; n < m_friends.size(); n++)
    //        {
    //            qDebug() << m_friends[n].getLogin();

    //            if(temp.mRecipient == m_friends[n].getLogin() || temp.mSender == m_friends[n].getLogin())
    //            {
    //                m_Correspondence[h].setParticipants(&m_user, &m_friends[n]);
    //            }
    //        }
    //    }


}

void Client::receiveMessage(QDataStream *in)
{
    in->setVersion(QDataStream::Qt_5_5);

    Message incomingMessage;

    *in >> incomingMessage.mSender
            >> incomingMessage.mRecipient
            >> incomingMessage.mMessageText
            >> incomingMessage.mDataTime;

    qDebug() << incomingMessage.mSender;
    qDebug() << incomingMessage.mRecipient;
    qDebug() << incomingMessage.mMessageText;
    qDebug() << incomingMessage.mDataTime;

    emit signalIncomingMessage(
                incomingMessage.mSender,
                incomingMessage.mMessageText,
                incomingMessage.mDataTime.time().toString());

    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(m_Correspondence[i].findParticipants( incomingMessage.mSender,incomingMessage.mRecipient))
        {
            m_Correspondence[i].addNewMessage(incomingMessage);
            break;
        }
    }
}


void Client::slotShowListFriends()
{
    for(int i = 0; i < m_friends.size(); i++)
    {
        emit signalAddFriendToList(m_friends[i].getLogin());
    }
}


void Client::slotShowFriend(const QString &login)
{
    for (int i = 0; i < m_friends.size(); i++)
    {
        if (login == m_friends[i].getLogin())
        {
            emit signalShowFriend(
                        m_friends[i].getName(),
                        m_friends[i].getSurname(),
                        m_friends[i].getLogin());
            break;
        }
    }



    QVector<Message> correspondence;

    for(int j = 0; j < m_Correspondence.size(); j++)
    {
        if(m_Correspondence[j].findParticipants(login, m_user.getLogin()))
        {
            correspondence = m_Correspondence[j].getCorrespondence();
            for(int k = 0; k < correspondence.size(); k++)
                break;
        }
    }

    for(int n = 0; n < correspondence.size(); n++)
    {
        if(correspondence[n].mSender == login)
        {
            emit signalEarlierReceivedMessage(
                        correspondence[n].mSender,
                        correspondence[n].mMessageText,
                        correspondence[n].mDataTime.time().toString());
        }

        else
        {
            emit signalEarlierSendMessage(
                        correspondence[n].mRecipient,
                        correspondence[n].mMessageText,
                        correspondence[n].mDataTime.time().toString());
        }
    }
}


//void Client::showCorrespondence(const QString &sender, const QString &recipient)
//{
//    QVector<Message> correspondence;

//    for(int j = 0; j < m_Correspondence.size(); j++)
//    {
//        if(m_Correspondence[j].findParticipants(sender, recipient))
//        {
//            qDebug() << "Nashel perepisku";
//            correspondence = m_Correspondence[j].getCorrespondence();
//            break;
//        }
//    }

//}

void Client::slotShowPotentialFriend(const QString &login)
{
    for(int i = 0; i < m_friends.size(); i++)
    {
        if (login == m_friends[i].getLogin())
        {
            emit signalShowFriend(
                        m_friends[i].getName(),
                        m_friends[i].getSurname(),
                        m_friends[i].getLogin());
            return;
        }
    }

    for(int j = 0; j < m_potentialFriends.size(); j++)
    {
        if (login == m_potentialFriends[j].getLogin())
        {
            emit signalShowPotentialFriend(
                        m_potentialFriends[j].getName(),
                        m_potentialFriends[j].getSurname(),
                        m_potentialFriends[j].getLogin());
            return;
        }
    }
}
