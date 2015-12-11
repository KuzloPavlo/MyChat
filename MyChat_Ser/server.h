#pragma once
#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QString>

#include "arrayofusers.h"
#include "MagicNumber.h"

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

    void regProcessingResponses(MagicNumber respond,
                                QTcpSocket *psocketForAnswers);

    void authProcessingResponses(MagicNumber respond,
                                 QTcpSocket *psocketForAnswers);



};

#endif // SERVER_H
