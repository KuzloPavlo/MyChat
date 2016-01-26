#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QString>
#include "user.h"
#include "messagetypes.h"
#include "returnvalues.h"
#include "message.h"

class Serv_Connect : public QObject
{
    Q_OBJECT
public:
    explicit Serv_Connect(QObject *parent = 0);

    void registerUser(const QString &name,
                      const QString &surname,
                      const QString &login,
                      const QString &password);

    void authorizationUser(const QString &login, const QString &password);

    void findFriend(const QString &tokenFriend);

    void addFriend (const QString &loginFriend);

    void removeFriend(const QString &loginFriend);

    void addDataUser(
            const QString &pname,
            const QString &psurname,
            const QString &plogin,
            const QString &ppassword,
            const QString &pipAddress);

    User getUser();

    void sendMessage(
            const QString &sender,
            const QString &recipient,
            const QString &messageText,
            const QDateTime &dateTime);



public:

    //  QVector<User> m_potentialFriends;          // ПИТАЙ!!!!!
    QByteArray m_block; //
    QDataStream *m_out; //


signals:
    void signalRegistered(const QString &login, const QString &password);

    void signalLoginBusy();

    void signalAuthorized(
            const QString &name,
            const QString &surname,
            const QString &login);

    void signalWrongLogin();
    void signalWrongPassword();
    void signalIsEmty();
    void signalFoundFriend(QVector<User> potentialFriends);
    void signalNewFriend(const User &newFriend);
    void signalIncomingMessage(const Message &incomingMessage);

private:
    QTcpSocket *m_psocket;
    quint16 m_nnextBlockSize;
    User m_user;
    QVector<User>m_friends;
    QVector<Correspondence> m_Correspondence;

    //  QVector<User>m_friends;



    void sendToServer(QDataStream *out, QByteArray *block);
    //  void sendToServer();
    void processRegistrationResponse(QDataStream *in);
    void processAuthorizationResponse(QDataStream *in);
    void setAuthorizedUser(QDataStream *in);

    void processFindFriendResponse(QDataStream *in);
    void processAddFriendResponse(QDataStream *in);
    void setNewFriend(QDataStream *in);

    void receiveMessage(QDataStream *in);

private slots:
    void slotReadServer();
    void slotSetUser(const QString &pname,
                     const QString &psurname,
                     const QString &plogin,
                     const QString &ppassword,
                     const QString &pipAddress);

    // void slotSearchFriendResponsFound(QVector<User> potentialFriends);

};
