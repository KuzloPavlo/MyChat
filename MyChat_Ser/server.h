#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);

signals:
public slots:

    void SlotnewConnection ();
    void slotReadClient();

private:
    QTcpServer *server;
    quint16 nextBlockSize;

};

#endif // SERVER_H
