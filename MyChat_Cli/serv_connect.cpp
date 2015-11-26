#include "serv_connect.h"
#include <QString>

Serv_Connect::Serv_Connect(QObject *parent) : QObject(parent)
{

}


void Serv_Connect::Connect (){

  //  QString IPadress = "127.0.0.1";
    socket= new QTcpSocket(this);

    socket->connectToHost ("127.0.0.1", 3030);

    if (socket->waitForConnected (3000)){


        qDebug () << "Connected!";
        QByteArray gbt ;
        gbt = socket->read(10);

        qDebug () << gbt;
        socket->close ();
    }

    else {

        qDebug () << "Not connected!";
    }


}
