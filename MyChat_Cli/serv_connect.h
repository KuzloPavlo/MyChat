#pragma once
#ifndef SERV_CONNECT_H
#define SERV_CONNECT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include "mainwindow.h"

class MainWindow;

class Serv_Connect : public QObject
{
    Q_OBJECT
public:
    explicit Serv_Connect(QObject *parent = 0);

    void setPtoWindow (MainWindow *pWINDOW=0);

    void Registration(QString *name,
                      QString *surname,
                      QString *login,
                      QString *password);

    void Authorization(QString *login,
                      QString *password);

private:
     QTcpSocket *socket;
     quint16 nextBlockSize;
     MainWindow *WINDOW;

     void RegServerRespons(QDataStream *RegInfo);
     //void AuthServerRespons;
private slots:
      void slotReadServer();
};

#endif // SERV_CONNECT_H
