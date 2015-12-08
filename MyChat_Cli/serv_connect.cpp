#include "serv_connect.h"
#include <QString>
#include <QDataStream>

Serv_Connect::Serv_Connect(QObject *parent) : QObject(parent),nextBlockSize(0)
{
    socket = new QTcpSocket(this);
    socket->connectToHost ("127.0.0.1", 3030);

    if (socket->waitForConnected (3000))
    {
        qDebug () << "Connected!";
    }

    else
    {
        qDebug () << "Not connected!";
    }

    connect (socket, SIGNAL (readyRead ()), this, SLOT (slotReadServer ()));
    nextBlockSize = 0;
}

void Serv_Connect::slotReadServer ()
{
    quint8 requestType;
    QDataStream in(socket);
    in.setVersion (QDataStream::Qt_5_5);

    if (nextBlockSize == 0)
    {
        if (socket->bytesAvailable ()< sizeof(quint16))
            return;
        in>>nextBlockSize;
    }

    if (socket->bytesAvailable ()< nextBlockSize)
        return;

    in>>requestType;
    qDebug() << (char)requestType;  // здесь печатаю
    qDebug()<< "server_connect.cpp stroka 43";

    switch ((char)requestType)
    {
    case 'R': this->RegServerRespons (&in);
        break;
    default:
        break;
    }

    requestType =0;
    nextBlockSize = 0;
}

void Serv_Connect::Registration (QString *name,QString *surname, QString *login, QString *password)
{
    QByteArray RegBlock;

    QDataStream out (&RegBlock, QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);
    out << quint16 (0)
        << quint8 ('R')
        << *name
        << *surname
        << *login
        << *password;

    out.device ()->seek (0);
    out <<quint16 (RegBlock.size ()- sizeof (quint16));
    socket->write(RegBlock);
}

void Serv_Connect::Authorization (QString *login, QString *password)
{
    QByteArray AuthBlock;

    QDataStream out (&AuthBlock,QIODevice::WriteOnly);
    out.setVersion (QDataStream::Qt_5_5);
    out << quint16 (0)
        << quint8 ('A')
        << *login
        << *password;

    out.device ()->seek (0);
    out <<quint16 (AuthBlock.size ()-sizeof (quint16));
    socket->write(AuthBlock);
}

//---------------------------------------------
// ServerRespons
//--------------------------------------------
void Serv_Connect::RegServerRespons(QDataStream *RegInfo)
{
    quint8 registered;
    RegInfo->setVersion (QDataStream::Qt_5_5);
    *RegInfo>> registered;
    qDebug() << registered;
    qDebug() << "serv_connect.cpp 102";

    if ('N' == (char)registered )
    {
        // не зарегистрировано
        quint8 why;
        *RegInfo>> why;
        if ('L' == (char)why) {
            // такой логин уже имеется
        }
        else {
            // для другой причины
        }
    }

    if ('Y'==(char)registered)
    {
        QString login_ServerRespons;
        QString password_ServerRespons;
        *RegInfo >> login_ServerRespons
                >> password_ServerRespons;

    }
}

//--------------------------------------------------------

void Serv_Connect::setPtoWindow (MainWindow *pWINDOW )
{
    WINDOW = pWINDOW;                   // ХЗХЗХЗХЗХЗХЗХЗХЗ
}
