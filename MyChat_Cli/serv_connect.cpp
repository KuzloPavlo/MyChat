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

    qDebug() << static_cast<MagicNumber> (requestType);  // здесь печатаю
    qDebug() << "server_connect.cpp stroka 43";

    switch (static_cast<MagicNumber>(requestType))
    {
    case REGISTRATION:
        this->regServerRespons(&in);
        break;

    case AUTHORIZATION:
        this->authServerRespons(&in);
        break;

    default:
        break;
    }

    requestType = 0;
    m_nnextBlockSize = 0;
}




void Serv_Connect::registration(QString *pname, QString *psurname, QString *plogin, QString *ppassword)
{
    QByteArray regBlock;

    QDataStream out (&regBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_5);
    out << quint16 (0)
        << quint8 (REGISTRATION)
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
        << quint8 (AUTHORIZATION)
        << *plogin
        << *ppassword;

    out.device()->seek (0);
    out << quint16 (authBlock.size() - sizeof(quint16));
    m_psocket->write(authBlock);
}




void Serv_Connect::regServerRespons(QDataStream *pregInfo)
{
    quint8 response;
    pregInfo->setVersion (QDataStream::Qt_5_5);
    *pregInfo >> response;
    qDebug() << static_cast<MagicNumber>(response);
    qDebug() << "serv_connect.cpp 112";

    switch (static_cast<MagicNumber>(response))
    {

    case REGISTERED:
        emit signalRegServerResponseRegistered();
        break;

    case LOGIN_BUSY:
        emit signalRegServerResponseLoginBusy();
        break;

    default:
        break;
    }
}




void Serv_Connect::authServerRespons(QDataStream *pauthInfo)
{
    quint8 response;
    pauthInfo->setVersion (QDataStream::Qt_5_5);
    *pauthInfo >> response;
    qDebug() << static_cast<MagicNumber>(response);
    qDebug() << "serv_connect.cpp 140";

    switch (static_cast<MagicNumber>(response))
    {

    case AUTHORIZED:
        emit signalAuthServerResponseAuthorized();
        break;

    case WRONG_LOGIN:
        emit signalAuthServerResponseWrongLogin();
        break;

    case WRONG_PASSWORD:
        emit signalAuthServerResponseWrongPassword();
        break;

    case IS_EMPTY:
        emit signalAuthServerResponseIsEmty();
        break;

    default:
        break;
    }

}
