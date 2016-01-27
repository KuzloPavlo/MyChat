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
        const QDateTime &dateTime)
{
    QByteArray block;

    QDataStream out (&block,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::message)
        << sender
        << recipient
        << messageText
        << dateTime;

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
}




void Client::processFindFriendResponse(QDataStream *in)
{
    quint8 npotentialFriends;
    QVector<User>  potentialFriends;

    in->setVersion(QDataStream::Qt_5_5);

    *in >> npotentialFriends;

    for (int i = 0; i <static_cast<int>(npotentialFriends); i++)
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
    emit signalFoundFriend(potentialFriends);
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

    emit this->signalNewFriend(tempFriend);
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

    emit signalIncomingMessage(incomingMessage);
}
