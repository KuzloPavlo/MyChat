#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "arrayofusers.h"
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
    ArrayOfUsers m_users;
    QTcpServer *m_pserver;
    quint16 m_nnextBlockSize;

    void regProcessingResponses(ReturnValues respond,
                                QTcpSocket *psocketForAnswers);

    void authProcessingResponses(ReturnValues respond,
                                 QTcpSocket *psocketForAnswers);

    void searchFriend(QVector<User> potentialFriends,
                       QTcpSocket *psocketForAnswers);

    void addFriendProcessingResponses(ReturnValues respond,
                                      QTcpSocket *psocketForAnswers);

    void getUserFriends(QVector<User> friends,
                        QTcpSocket *psocketForAnswers);

    void removingFriend(ReturnValues respond,
                        QTcpSocket *psocketForAnswers);

};

#endif // SERVER_H
