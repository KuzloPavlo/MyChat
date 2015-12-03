#ifndef SERV_CONNECT_H
#define SERV_CONNECT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Serv_Connect : public QObject
{
    Q_OBJECT
public:
    explicit Serv_Connect(QObject *parent = 0);
    void ConnectToServer ();
    void Registration(QByteArray *RegBlok);
    // QTcpSocket *socket;

private:

     QTcpSocket *socket;
     quint16 nextBlockSize;

     void closeConnection();

private slots:

     void connectedServ ();

};

#endif // SERV_CONNECT_H
