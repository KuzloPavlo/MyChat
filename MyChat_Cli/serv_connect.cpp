#include "serv_connect.h"
#include <QString>

Serv_Connect::Serv_Connect(QObject *parent) : QObject(parent),nextBlockSize(0)
{
  //connect (socket , SIGNAL (connected ()), this , SLOT (connectedServ ()));
  //connect (socket , SIGNAL (disconnect ()))
}

void Serv_Connect::ConnectToServer (){

    socket = new QTcpSocket(this);

    socket->connectToHost ("127.0.0.1", 3030);

    if (socket->waitForConnected (3000)){


        emit connectedServ ();

     //   qDebug () << "Connected!";
        //QByteArray gbt ;
        //gbt = socket->read(10);

        //qDebug () << gbt;
        //socket->close ();
    }

    else {

        qDebug () << "Not connected!";
    }


    nextBlockSize = 0;
}

//-----------------------------------------------------------------------------

void Serv_Connect::Registration (QByteArray *RegBlok) {

    socket->write(*RegBlok);

  qDebug () << "Registration!";

}


void Serv_Connect::connectedServ () {

        qDebug () << "Connected taki!";

}
