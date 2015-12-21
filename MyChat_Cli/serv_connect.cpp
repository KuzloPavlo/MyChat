#include "serv_connect.h"
#include <QString>
#include <QDataStream>



Serv_Connect::Serv_Connect(QObject *parent) : QObject(parent), m_nnextBlockSize(0)
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
}




void Serv_Connect::slotReadServer()
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

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}



void Serv_Connect::slotSetUser(const QString &pname,      // Возможно етот слот и НЕНУЖЕН
                               const QString &psurname,
                               const QString &plogin,
                               const QString &ppassword,
                               const QString &pipAddress)
{
    User user(pname,psurname,plogin,ppassword,pipAddress);
    this->m_user = user;
}







void Serv_Connect::addDataUser(
        const QString &pname,
        const QString &psurname,
        const QString &plogin,
        const QString &ppassword,
        const QString &pipAddress)
{
    User temp(pname,psurname, plogin, ppassword, pipAddress);
    m_user = temp;
}



User Serv_Connect::getUser()
{
    User temp = m_user;

    return temp;
}



void Serv_Connect::registerUser(const QString &name, const QString &surname, const QString &login, const QString &password)
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

    out.device()->seek (0);
    out << quint16 (block.size() - sizeof(quint16));
    m_psocket->write(block);
}




void Serv_Connect::authorizationUser (const QString &login, const QString &password)
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




void Serv_Connect::findFriend(const QString &tokenFriend)//searchFriend(QString *pdataFriend)  // надо конст ссілку
{

    // qDebug() << "Serv_connect, searchFriend" << *pdataFriend;

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




void Serv_Connect::addFriend (QString *pLoginFriend)
{
    QByteArray addFriendBlock;

    QDataStream out (&addFriendBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (MessageTypes::addFriend)
        << m_user.getLogin()
        << *pLoginFriend;

    out.device()->seek(0);
    out << quint16 (addFriendBlock.size() - sizeof(quint16));
    m_psocket->write(addFriendBlock);

}




void Serv_Connect::processRegistrationResponse(QDataStream *in)
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




void Serv_Connect::processAuthorizationResponse(QDataStream *in)
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




void Serv_Connect::setAuthorizedUser(QDataStream *in)
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




void Serv_Connect::processFindFriendResponse(QDataStream *in)
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
            QString potentialFriendIPAddress;
            QString emptyString = "";

            *in >> potentialFriendName
                    >> potentialFriendSurname
                    >> potentialFriendLogin
                    >> potentialFriendIPAddress;

            User tempFrined(
                        potentialFriendName,
                        potentialFriendSurname,
                        potentialFriendLogin,
                        emptyString,
                        potentialFriendIPAddress);

            potentialFriends.push_back(tempFrined);

        }
        emit signalFoundFriend(potentialFriends);
}
