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
    emit f("Client::slotReadServer()1");
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
    emit f("Client::slotReadServer()2");
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

    case MessageTypes::createChat:
        emit f("Client::slotReadServer()case MessageTypes::createChat:1");
        this->processCreateGroupChatResponse(&in);
        emit f("Client::slotReadServer()case MessageTypes::createChat:2");
        break;


    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
    emit f("Client::slotReadServer()3");
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
    qDebug()<< "1setAuthorizedUser1";
    in->setVersion (QDataStream::Qt_5_5);

    QString userName;
    QString userSurname;
    QString userLogin;
    QString userPassword = "";
    QString userIPAddress;
    qDebug()<< "1setAuthorizedUser1";
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
    qDebug()<< "1setAuthorizedUser1";
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
    qDebug()  << "1";
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

    qDebug()  << "1";
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
    qDebug()  << "1";
    Correspondence newCorrespondence(newFriend,&m_user); //create local correspondence

    m_Correspondence.push_back(newCorrespondence);
    qDebug()  << "1";
    emit this->signalNewFriend();
    qDebug()  << "1";
}


void Client::getFriends()
{
    QByteArray block;
    qDebug()<< "1getFriends1";
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    qDebug()<< "1getFriends1";
    out << quint16(0)
        << quint8(MessageTypes::getFriends)
        << m_user.getLogin();
    qDebug()<< "1getFriends1";
    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
    qDebug()<< "1getFriends2";
}


void Client::getCorrespondence()
{
    QByteArray block;
    qDebug()<< "1getCorrespondence1";
    QDataStream out (&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    qDebug()<< "1getCorrespondence1";
    out << quint16(0)
        << quint8(MessageTypes::getCorrespondence)
        << m_user.getLogin();
    qDebug()<< "1getCorrespondence2";
    out.device()->seek(0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}


void Client::setFriends(QDataStream *in)
{
    quint8 nfriends;
    qDebug()<< "1setFriends1";
    in->setVersion(QDataStream::Qt_5_5);

    *in >> nfriends;
    qDebug()<< "1setFriends1";
    for(int i = 0; i < static_cast<int>(nfriends); i++)
    {
        QString friendName;
        QString friendSurname;
        QString friendLogin;
        QString emptyString = "";

        *in >> friendName
                >> friendSurname
                >> friendLogin;
        qDebug()<< "1setFriends1";
        User tempFriend(
                    friendName,
                    friendSurname,
                    friendLogin,
                    emptyString,
                    emptyString
                    );
        m_friends.push_back(tempFriend);
    }
    qDebug()<< "1setFriends1";
    getCorrespondence();
    qDebug()<< "1setFriends2";
}



void Client::setCorrespondence(QDataStream *in)
{qDebug()<< "1setCorrespondence1";
    quint8 ncorrespondence;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> ncorrespondence;
    qDebug()<< "1setCorrespondence1";
    for(int j = 0; j < static_cast<int> (ncorrespondence); j++)
    {
        quint8 IDNumber;
        *in >> IDNumber;

        quint8 nparticipants;
        *in >> nparticipants;

        Correspondence messages;
        qDebug()<< "1setCorrespondence1";
        for(int i = 0; i < static_cast<int> (nparticipants); i++)
        {
            QString participantLogin;
            *in >> participantLogin;

            if(participantLogin == m_user.getLogin())
            {
                messages.addParticipant(&m_user);
            }

            else
            {qDebug()<< "1setCorrespondence1";
                for(int t = 0; t < m_friends.size(); t++)
                {
                    if(participantLogin == m_friends[t].getLogin())
                    {
                        messages.addParticipant(&m_friends[t]);
                    }
                }
            }
        }
        qDebug()<< "1setCorrespondence1";
        quint8 nmessages;
        *in >> nmessages;

        for(int k = 0; k < static_cast<int>(nmessages); k++)
        {
            QString sender,recipient,messageText;
            QDateTime dataTime;
            qDebug()<< "1setCorrespondence1";
            *in >> sender
                    >> recipient
                    >> messageText
                    >> dataTime;

            Message tempMessage;
            qDebug()<< "1setCorrespondence1";
            tempMessage.mSender = sender;
            tempMessage.mRecipient = recipient;
            tempMessage.mMessageText = messageText;
            tempMessage.mDataTime = dataTime;

            messages.addNewMessage(tempMessage);

            qDebug() << "From Client, setCorr" << messages.getLastMessage().mMessageText;
        }
        m_Correspondence.push_back(messages);
    }
    qDebug()<< "1setCorrespondence2";
    //    for(int h = 0; h < m_Correspondence.size(); h++)
    //    { qDebug()<<"5";
    //        Message temp = m_Correspondence[h].getLastMessage();
    //        qDebug()<<"6";
    //        for(int n = 0; n < m_friends.size(); n++)
    //        {
    //            qDebug() << "Iz naznachenia participiantow" << m_friends[n].getLogin();

    //            if(temp.mRecipient == m_friends[n].getLogin() || temp.mSender == m_friends[n].getLogin())
    //            {
    //                m_Correspondence[h].setParticipants(&m_user, &m_friends[n]);
    //                break;
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


void Client::slotShowListChats()
{
    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(m_Correspondence[i].getIDNumber() != 0)
        {
            emit signalAddChatToList(
                        m_Correspondence[i].getIDNumber(),
                        m_Correspondence[i].getChatName(),
                        m_Correspondence[i].getParticipants());
        }
    }
}


void Client::slotFindParticipants(const QString &tokenParticipant)
{
    emit f("slotFindParticipants1");
    for(int i = 0; i < m_friends.size(); i++)
    {emit f("slotFindParticipants2");
        if(m_friends[i].getName().indexOf(tokenParticipant) != -1 ||
                m_friends[i].getSurname().indexOf(tokenParticipant) != -1 ||
                m_friends[i].getLogin().indexOf(tokenParticipant) != -1)
        {
            emit signalShowFriend(m_friends[i].getLogin());
            emit f("slotFindParticipants3");
        }
    }
    emit f("slotFindParticipants4");
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

    //-----------------------------------

    QVector<Message> correspondence;

    for(int j = 0; j < m_Correspondence.size(); j++)
    {
        if(m_Correspondence[j].findParticipants(login, m_user.getLogin()))
        {
            correspondence = m_Correspondence[j].getCorrespondence();
            //            qDebug() << "Client,slotShowFriend, perepiska megdu " << login <<"i " << m_user.getLogin() << "najdena";
            break;
        }
    }

    for(int n = 0; n < correspondence.size(); n++)
    {
        qDebug() << "Client,slotShowFriend - soobshc: " << correspondence[n].mMessageText;

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



void Client::slotShowChat(const int &IDNumber)
{
    int chatIDNumber;
    QString nameChat;
    QVector<QString> admin;
    QVector<QString> friends;
    QVector<QString> notFriends;

    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(IDNumber == m_Correspondence[i].getIDNumber())
        {
            chatIDNumber = m_Correspondence[i].getIDNumber();

            nameChat = m_Correspondence[i].getChatName();

            admin = m_Correspondence[i].getDataAdmin();

            friends = m_Correspondence[i].getDataParticipants();

            notFriends = m_Correspondence[i].getNotFriends();

            break;
        }
    }

    emit signalShowChat(chatIDNumber,nameChat,admin,friends,notFriends);
}



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


void Client::slotCrateNewGroupChat(QVector<QString> participants)
{
    emit f("Client::slotCrateNewGroupChat1");
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
    emit f("Client::slotCrateNewGroupChat2");
}


void Client::processCreateGroupChatResponse(QDataStream *in)
{ emit f("Client::processCreateGroupChatResponse1");
    quint8 response;

    in->setVersion (QDataStream::Qt_5_5);
    *in >> response;

    switch(static_cast<ReturnValues>(response))
    {
    case ReturnValues::createdChat:
        emit f("Client::processCreateGroupChatResponse2");
        setNewGroupChat(in);
        break;

    default:
        break;
    }
}


void Client::setNewGroupChat(QDataStream *in)
{
    emit f(" Client::setNewGroupChat1");
    quint8 IDNumber;
    quint8 nparticipant;
    QString adminLogin;
    QVector<QString> participantsLogins;
    User *admin;
    QVector<User*> participants;
    QVector<QString> notFriends;

    emit f(" Client::setNewGroupChat2");
    in->setVersion (QDataStream::Qt_5_5);

    *in >> IDNumber
            >> adminLogin
            >> nparticipant;

    for (int i = 0; i < static_cast<int>(nparticipant); i++)
    {emit f(" Client::setNewGroupChat3");
        QString participant;
        *in >> participant;
        participantsLogins.push_back(participant);
    }

    for(int j = 0; j < participantsLogins.size(); j++)
    {
        for(int h = 0; h < m_friends.size(); h++)
        {
            if(participantsLogins[j] == m_friends[h].getLogin())
            {
                participants.push_back(&m_friends[h]);
                emit f(" Client::setNewGroupChat3");
                break;
            }
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
    emit f(" Client::setNewGroupChat4");

    if(adminLogin == m_user.getLogin())
    {
        admin =& m_user;
    }
    else
    {
        for(int o = 0; o < m_friends.size(); o++)
        {
            if(adminLogin == m_friends[o].getLogin())
            {
                admin =& m_friends[o];
                break;
            }
        }
    }
    emit f(" Client::setNewGroupChat5");
    Correspondence groupCorrespondence(admin,participants,IDNumber);

    for(int y = 0; y < notFriends.size(); y++)
    {
        groupCorrespondence.addParticipant(notFriends[y]);
    }

    m_Correspondence.push_back(groupCorrespondence);

    emit signalNewGroupChat();
}
