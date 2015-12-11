#pragma once
#ifndef SERV_CONNECT_H
#define SERV_CONNECT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

#include "magicnumber.h"

class Serv_Connect : public QObject
{
    Q_OBJECT
public:
    explicit Serv_Connect(QObject *parent = 0);

    void registration(QString *pname,
                      QString *psurname,
                      QString *plogin,
                      QString *ppassword);

    void authorization(QString *plogin, QString *ppassword);

signals:
    void signalRegServerResponseRegistered();
    void signalRegServerResponseLoginBusy();

    void signalAuthServerResponseAuthorized();
    void signalAuthServerResponseWrongLogin();
    void signalAuthServerResponseWrongPassword();
    void signalAuthServerResponseIsEmty();

private:
    QTcpSocket *m_psocket;
    quint16 m_nnextBlockSize;

    void regServerRespons(QDataStream *pregInfo);
    void authServerRespons(QDataStream *pauthInfo);

private slots:
    void slotReadServer();
};

#endif // SERV_CONNECT_H
