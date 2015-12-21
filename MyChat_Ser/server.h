#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "usersarray.h"
#include "returnvalues.h"
#include "messagetypes.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
signals:
public slots:
    void slotNewConnection ();
    void slotReadClient();
private:
    UsersArray m_users;
    QTcpServer *m_pserver;
    quint16 m_nnextBlockSize;



    void registerUser(QDataStream *in, QDataStream *out);

    void authorizationUser(QDataStream *in, QDataStream *out);

    void findFriend(QDataStream *in, QDataStream *out);


//    void searchFriend(QVector<User> potentialFriends,
//                      QTcpSocket *psocketForAnswers);

//void addFriend(Qstring* userLogin, QString* friendLogin);  // продолжай

    void addFriendProcessingResponses(ReturnValues respond,
                                      QTcpSocket *psocketForAnswers);

    void getUserFriends(QVector<User> friends,
                        QTcpSocket *psocketForAnswers);

    void removingFriend(ReturnValues respond,
                        QTcpSocket *psocketForAnswers);

};

#endif // SERVER_H
