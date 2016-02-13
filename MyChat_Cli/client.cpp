#include "Client.h"
#include "correspondence.h"

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
        this->setFriends(&in);
        break;

    case MessageTypes::getCorrespondence:
        this->setCorrespondence(&in);
        break;

    case MessageTypes::message:
        this->receiveMessage(&in);
        break;

    case MessageTypes::groupMessage:
        this->receiveGroupMessage(&in);
        break;

    case MessageTypes::createChat:
        this->processCreateGroupChatResponse(&in);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}



//void Client::slotSetUser(const QString &pname,      // Возможно етот слот и НЕНУЖЕН
//                         const QString &psurname,
//                         const QString &plogin,
//                         const QString &ppassword,
//                         const QString &pipAddress)
//{
//    User user(pname,psurname,plogin,ppassword,pipAddress);
//    this->m_user = user;
//}



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

    QList<Correspondence>::iterator i = m_Correspondence.begin();
    while(i != m_Correspondence.end())
    {
        if((*i).findParticipants(sender,recipient))
        {
            (*i).addNewMessage(outgoingMessage);
            break;
        }
        i++;
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



void Client::sendMessage(const QString &sender, const int &IDNumber, const QString &messageText, const QDateTime &dataTime)
{
    Message outgoingMessage;
    outgoingMessage.mSender = sender;
    outgoingMessage.mRecipient = "";
    outgoingMessage.mMessageText = messageText;
    outgoingMessage.mDataTime = dataTime;

    QList<Correspondence>::iterator i = m_Correspondence.begin();
    while(i != m_Correspondence.end())
    {
        if((*i).getIDNumber() == IDNumber)
        {
            (*i).addNewMessage(outgoingMessage);
            break;
        }
        i++;
    }

    QByteArray block;

    QDataStream out (&block,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::groupMessage )
        << quint8(IDNumber)
        << sender
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
    getFriends();
}



void Client::processFindFriendResponse(QDataStream *in)
{
    quint8 npotentialFriends;
    QVector<User>  potentialFriends;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> npotentialFriends;

    for (int i = 0; i < static_cast<int>(npotentialFriends); i++)
    {
        QString potentialFriendName;
        QString potentialFriendSurname;
        QString potentialFriendLogin;
        QString emptyString = "";

        *in >> potentialFriendName
                >> potentialFriendSurname
                >> potentialFriendLogin;

        User tempFrined(
                    potentialFriendName,
                    potentialFriendSurname,
                    potentialFriendLogin,
                    emptyString,
                    emptyString);

        potentialFriends.push_back(tempFrined);
    }

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

    m_friends.push_back(tempFriend);

    User *newFriend;

    QList<User>::iterator i = m_friends.begin();

    while(i != m_friends.end())
    {
        if(friendLogin == (*i).getLogin())
        {
            newFriend =& (*i);
            break;
        }
        i++;
    }

    Correspondence newCorrespondence(newFriend,&m_user); //create local correspondence
    m_Correspondence.push_back(newCorrespondence);

    emit this->signalNewFriend();
}



void Client::getFriends()
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



void Client::getCorrespondence()
{
    QByteArray block;

    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::getCorrespondence)
        << m_user.getLogin();

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}



void Client::setFriends(QDataStream *in)
{
    quint8 nfriends;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> nfriends;

    for(int i = 0; i < static_cast<int>(nfriends); i++)
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
    getCorrespondence();
}



void Client::setCorrespondence(QDataStream *in)
{
    quint8 ncorrespondence;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> ncorrespondence;

    for(int j = 0; j < static_cast<int> (ncorrespondence); j++)
    {
        quint8 IDNumber;
        *in >> IDNumber;

        quint8 nparticipants;
        *in >> nparticipants;

        Correspondence messages;

        for(int i = 0; i < static_cast<int> (nparticipants); i++)
        {
            QString participantLogin;
            *in >> participantLogin;

            if(participantLogin == m_user.getLogin())
            {
                messages.addParticipant(&m_user);
            }

            else
            {
                QList<User>::iterator t = m_friends.begin();
                while(t != m_friends.end())
                {
                    if(participantLogin == (*t).getLogin())
                    {
                        messages.addParticipant(&(*t));
                    }
                    t++;
                }
            }
        }

        quint8 nmessages;
        *in >> nmessages;

        for(int k = 0; k < static_cast<int>(nmessages); k++)
        {
            QString sender,recipient,messageText;
            QDateTime dataTime;

            *in >> sender
                    >> recipient
                    >> messageText
                    >> dataTime;

            Message tempMessage;

            tempMessage.mSender = sender;
            tempMessage.mRecipient = recipient;
            tempMessage.mMessageText = messageText;
            tempMessage.mDataTime = dataTime;

            messages.addNewMessage(tempMessage);
        }
        m_Correspondence.push_back(messages);
    }
}



void Client::receiveMessage(QDataStream *in)
{
    in->setVersion(QDataStream::Qt_5_5);

    Message incomingMessage;

    *in >> incomingMessage.mSender
            >> incomingMessage.mRecipient
            >> incomingMessage.mMessageText
            >> incomingMessage.mDataTime;

    emit signalIncomingMessage(
                incomingMessage.mSender,
                incomingMessage.mMessageText,
                incomingMessage.mDataTime.time().toString());

    QList<Correspondence>::iterator i = m_Correspondence.begin();

    while(i != m_Correspondence.end())
    {
        if((*i).findParticipants(incomingMessage.mSender,incomingMessage.mRecipient))
        {
            (*i).addNewMessage(incomingMessage);
            break;
        }
        i++;
    }
}



void Client::receiveGroupMessage(QDataStream *in)
{
    quint8 IDNumber;
    Message incomingMessage;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> IDNumber
            >> incomingMessage.mSender
            >> incomingMessage.mMessageText
            >> incomingMessage.mDataTime;

    incomingMessage.mRecipient = m_user.getLogin();

    emit signalGroupIncomingMessage(
                static_cast<int>(IDNumber),
                incomingMessage.mSender,
                incomingMessage.mMessageText,
                incomingMessage.mDataTime.time().toString());

    QList<Correspondence>::iterator i = m_Correspondence.begin();

    while(i != m_Correspondence.end())
    {
        if((*i).getIDNumber() == static_cast<int>(IDNumber))
        {
            (*i).addNewMessage(incomingMessage);
            break;
        }
        i++;
    }
}



void Client::slotShowListFriends()
{
    QList<User>::iterator i = m_friends.begin();

    while(i != m_friends.end())
    {
        emit signalAddFriendToList((*i ).getLogin());
        i++;
    }
}


void Client::slotShowListChats()
{
    QList<Correspondence>::iterator i = m_Correspondence.begin();

    while(i != m_Correspondence.end())
    {
        if((*i).getIDNumber() != 0)
        {
            emit signalAddChatToList(
                        (*i).getIDNumber(),
                        (*i).getChatName(),
                        (*i).getParticipants());
        }
        i++;
    }
}



void Client::slotFindParticipants(const QString &tokenParticipant)
{
    QList<User>::iterator i = m_friends.begin();
    while(i != m_friends.end())
    {
        if((*i).getName().indexOf(tokenParticipant) != -1 ||
                (*i).getSurname().indexOf(tokenParticipant) != -1 ||
                (*i).getLogin().indexOf(tokenParticipant) != -1)
        {
            emit signalShowFriend((*i).getLogin());
        }
        i++;
    }
}



void Client::slotShowFriend(const QString &login)
{
    QList<User>::iterator i = m_friends.begin();
    while(i != m_friends.end())
    {
        if (login == (*i).getLogin())
        {
            emit signalShowFriend((*i).getName(),(*i).getSurname(),(*i).getLogin());
            break;
        }
        i++;
    }

    QVector<Message> correspondence;

    QList<Correspondence>::iterator j = m_Correspondence.begin();
    while(j != m_Correspondence.end())
    {
        if((*j).findParticipants(login, m_user.getLogin()))
        {
            correspondence = (*j).getCorrespondence();
            break;
        }
        j++;
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



void Client::slotShowChat(const int &IDNumber)
{
    f("slotShowChat");
    //    int chatIDNumber;
    //    QString nameChat;
    //    QVector<QString> admin;
    //    QVector<QString> friends;
    //    QVector<QString> notFriends;

    QList<Correspondence>::iterator i = m_Correspondence.begin();
    while(i != m_Correspondence.end())
    {
        if(IDNumber == (*i).getIDNumber())
        {
            //            chatIDNumber = m_Correspondence[i].getIDNumber();

            //            nameChat = m_Correspondence[i].getChatName();

            //            admin = m_Correspondence[i].getDataAdmin();

            //            friends = m_Correspondence[i].getDataParticipants();

            //            notFriends = m_Correspondence[i].getNotFriends();

            emit signalShowChat(
                        (*i).getIDNumber(),
                        (*i).getChatName(),
                        (*i).getDataAdmin(),
                        (*i).getDataParticipants(),
                        (*i).getNotFriends()
                        );
            break;
        }
        i++;
    }

    // emit signalShowChat(chatIDNumber,nameChat,admin,friends,notFriends);
}



void Client::slotShowPotentialFriend(const QString &login)
{
    QList<User>::iterator i = m_friends.begin();
    while(i != m_friends.end())
    {
        if (login == (*i).getLogin())
        {
            emit signalShowFriend(
                        (*i).getName(),
                        (*i).getSurname(),
                        (*i).getLogin());
            return;
        }
        i++;
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



void Client::slotCrateNewGroupChat(QVector<QString> participants)
{

    QByteArray block;
    QDataStream out (&block, QIODevice::WriteOnly);

    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::createChat)
        << m_user.getLogin()
        << quint8(participants.size());

    for(int i = 0; i < participants.size(); i++)
    {
        out << participants[i];
    }

    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}



void Client::processCreateGroupChatResponse(QDataStream *in)
{
    quint8 response;

    in->setVersion (QDataStream::Qt_5_5);
    *in >> response;

    switch(static_cast<ReturnValues>(response))
    {
    case ReturnValues::createdChat:
        setNewGroupChat(in);
        break;

    default:
        break;
    }
}


void Client::setNewGroupChat(QDataStream *in)
{
    quint8 IDNumber;
    quint8 nparticipant;
    QString adminLogin;
    QVector<QString> participantsLogins;
    User *admin;
    QVector<User*> participants;
    QVector<QString> notFriends;

    in->setVersion (QDataStream::Qt_5_5);

    *in >> IDNumber
            >> adminLogin
            >> nparticipant;

    for (int i = 0; i < static_cast<int>(nparticipant); i++)
    {
        QString participant;
        *in >> participant;
        participantsLogins.push_back(participant);
    }

    for(int j = 0; j < participantsLogins.size(); j++)
    {
        QList<User>::iterator h = m_friends.begin();
        while(h != m_friends.end())
        {
            if(participantsLogins[j] == (*h).getLogin())
            {
                participants.push_back(&(*h));
                break;
            }
            h++;
        }
    }


    if(participantsLogins.size() != participants.size())
    {
        for(int k = 0; k < participantsLogins.size(); k++)
        {
            bool flag = false;

            for(int n = 0; n < participants.size(); n++)
            {
                if(participants[n]->getLogin() == participantsLogins[k])
                {
                    flag = true;
                    break;
                }
            }

            if(!flag)
            {
                notFriends.push_back(participantsLogins[k]);
            }
        }
    }

    if(adminLogin == m_user.getLogin())
    {
        admin =& m_user;
    }
    else
    {
        QList<User>::iterator o = m_friends.begin();
        while(o != m_friends.end())
        {
            if(adminLogin == (*o).getLogin())
            {
                admin =&(*o);
                break;
            }
            o++;
        }
    }

    Correspondence groupCorrespondence(admin,participants,IDNumber);

    for(int y = 0; y < notFriends.size(); y++)
    {
        groupCorrespondence.addParticipant(notFriends[y]);
    }

    m_Correspondence.push_back(groupCorrespondence);

    emit signalNewGroupChat();
}
