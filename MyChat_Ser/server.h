#pragma once
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>
#include "users.h"
#include "returnvalues.h"
#include "messagetypes.h"
#include "message.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void f(const QString &str);
signals:


public slots:
    void slotNewConnection ();
    void slotReadClient();
    void slotDisconnectClient();
private:

    Users m_users;
    QTcpServer *m_pserver;
    quint16 m_nnextBlockSize;
    int m_ngroupChats;

    void registerUser(QDataStream *in, QDataStream *out);

    void authorizationUser(QDataStream *in, QDataStream *out, QTcpSocket *pClientSocket);

    void findFriend(QDataStream *in, QDataStream *out);

    void removeFriend(QDataStream *in, QDataStream *out);

    void addFriend(QDataStream *in, QDataStream *out);

    void getFriends(QDataStream *in, QDataStream *out);

    void getCorrespondence(QDataStream *in, QDataStream *out);

    void receiveMessage(QDataStream *in, QDataStream *out);

    void reciveGroupMessage(QDataStream *in, QDataStream *out);

    void sendMessage();

    void createNewGroupChat(QDataStream *in, QDataStream *out);
};
