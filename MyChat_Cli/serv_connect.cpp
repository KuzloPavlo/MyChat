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

    //    qDebug() << static_cast<MessageTypes> (requestType);  // здесь печатаю
    //    qDebug() << "server_connect.cpp stroka 43";

    switch (static_cast<MessageTypes>(requestType))
    {
    case MessageTypes::registration:
        this->regServerResponding (&in);
        break;

    case MessageTypes::authorization:
        this->authServerResponding(&in);
        break;

    case MessageTypes::search_friend:
        this->searchFriendServerResponding(&in);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}



void Serv_Connect::slotSetUser(QString *pname,      // Возможно етот слот и НЕНУЖЕН
                               QString *psurname,
                               QString *plogin,
                               QString *ppassword,
                               QString *pipAddress)
{
    User user(pname,psurname,plogin,ppassword,pipAddress);
    this->m_user = user;
}




void Serv_Connect::slotSearchFriendResponsFound(QVector<User> potentialFriends)
{
    this->m_potentialFriends = potentialFriends;
}



void Serv_Connect::addDataUser(
        QString *pname,
        QString *psurname,
        QString *plogin,
        QString *ppassword,
        QString *pipAddress)
{
    User temp(pname,psurname, plogin, ppassword, pipAddress);
    m_user = temp;
}



User Serv_Connect::getUser()
{
    User temp = m_user;

    return temp;
}



void Serv_Connect::registration(QString *pname, QString *psurname, QString *plogin, QString *ppassword)
{
    QByteArray regBlock;

    QDataStream out (&regBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16 (0)
        << quint8 (MessageTypes::registration)
        << *pname
        << *psurname
        << *plogin
        << *ppassword;

    out.device()->seek (0);
    out << quint16 (regBlock.size() - sizeof(quint16));
    m_psocket->write(regBlock);
}




void Serv_Connect::authorization (QString *plogin, QString *ppassword)
{
    QByteArray authBlock;

    QDataStream out (&authBlock,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);

    out << quint16 (0)
        << quint8 (MessageTypes::authorization)
        << *plogin
        << *ppassword;

    out.device()->seek (0);
    out << quint16 (authBlock.size() - sizeof(quint16));
    m_psocket->write(authBlock);
}




void Serv_Connect::searchFriend(QString *pdataFriend)  // надо конст ссілку
{

    // qDebug() << "Serv_connect, searchFriend" << *pdataFriend;

    QByteArray searchFriendBlock;

    QDataStream out (&searchFriendBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8(MessageTypes::search_friend)
        << *pdataFriend;

    out.device()->seek(0);
    out << quint16 (searchFriendBlock.size() - sizeof(quint16));
    m_psocket->write(searchFriendBlock);

}




void Serv_Connect::addFriend (QString *pLoginFriend)
{
    QByteArray addFriendBlock;

    QDataStream out (&addFriendBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);

    out << quint16(0)
        << quint8 (MessageTypes::add_friend)
        << m_user.showLogin()
        << *pLoginFriend;

    out.device()->seek(0);
    out << quint16 (addFriendBlock.size() - sizeof(quint16));
    m_psocket->write(addFriendBlock);

}




void Serv_Connect::regServerResponding(QDataStream *pregInfo)
{
    quint8 response;
    pregInfo->setVersion (QDataStream::Qt_5_5);
    *pregInfo >> response;

    switch (static_cast<ReturnValues>(response))
    {

    case registered:
    {

        QString userName;
        QString userSurname;
        QString userLogin;
        QString userPassword;
        QString userIPAddress;

        *pregInfo >> userName
                >> userSurname
                >> userLogin
                >> userPassword
                >> userIPAddress;

        User tempUser(&userName,   // Обсуди с Романом
                      &userSurname,  // Обсуди с Романом
                      &userLogin,
                      &userPassword,
                      &userIPAddress);

        this->m_user = tempUser;   // Обсуди с Романом

        emit signalRegRegistered(
                    &userName,
                    &userSurname,
                    &userLogin,
                    &userPassword,
                    &userIPAddress );
    }
        break;

    case login_busy:
        emit signalRegLoginBusy();
        break;

    default:
        break;
    }
}




void Serv_Connect::authServerResponding(QDataStream *pauthInfo)
{
    quint8 response;
    pauthInfo->setVersion (QDataStream::Qt_5_5);
    *pauthInfo >> response;
    //    qDebug() << static_cast<ReturnValues>(response);
    //    qDebug() << "serv_connect.cpp 140";

    switch (static_cast<ReturnValues>(response))
    {

    case authorized:
    {
        QString userName;
        QString userSurname;
        QString userLogin;
        QString userPassword;
        QString userIPAddress;

        *pauthInfo >> userName
                >> userSurname    // выноси это все в функцию
                >> userLogin
                >> userPassword
                >> userIPAddress;

        User tempUser(&userName,   // Обсуди с Романом
                      &userSurname,  // Обсуди с Романом
                      &userLogin,
                      &userPassword,
                      &userIPAddress);

        this->m_user = tempUser;   // Обсуди с Романом

        emit signalAuthAuthorized(
                    &userName,
                    &userSurname,
                    &userLogin,
                    &userPassword,
                    &userIPAddress);
    }
        break;

    case wrong_login:
        emit signalAuthWrongLogin();
        break;

    case wrong_password:
        emit signalAuthWrongPassword();
        break;

    case is_empty:
        emit signalAuthIsEmty();
        break;

    default:
        break;
    }

}




void Serv_Connect::searchFriendServerResponding(QDataStream *psearchInfo)
{
    quint8 npotentialFriends;
    QVector<User>  potentialFriends;
    psearchInfo->setVersion(QDataStream::Qt_5_5);

    *psearchInfo >> npotentialFriends;

    if (npotentialFriends != 0)
    {
        for (int i = 0; i <static_cast<int>(npotentialFriends); i++)
        {
            QString potentialFriendName;
            QString potentialFriendSurname;
            QString potentialFriendLogin;
            QString potentialFriendIPAddress;
            QString emptyString = "";

            *psearchInfo >> potentialFriendName
                    >> potentialFriendSurname
                    >> potentialFriendLogin
                    >> potentialFriendIPAddress;

            User tempFrined(
                        &potentialFriendName,
                        &potentialFriendSurname,
                        &potentialFriendLogin,
                        &emptyString,
                        &potentialFriendIPAddress);

            //            qDebug() << "Server_connect, searchFriendServerRes"
            //                     << tempFrined.showLogin();

            potentialFriends.push_back(tempFrined);

        }
        emit signalSearchFriendResponsFound(potentialFriends);
        return;
    }

    else
    {
        emit signalSearchFriendResponsNotFound();
    }
}
