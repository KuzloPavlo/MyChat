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
     void Connect ();
signals:

public slots:

private:

     QTcpSocket *socket;
};

#endif // SERV_CONNECT_H
