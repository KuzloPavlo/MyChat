#pragma once
#include <QDebug>
#include <QVector>
#include <QList>
#include <QDataStream>
#include <QTcpSocket>
#include "user.h"
// efrherthrthertherthertherthe
#include "messagetypes.h"
#include "returnvalues.h"
#include "correspondence.h"
#include "message.h"

class Users
{

public:

    ReturnValues addUser(const QString &name,
                         const QString &surname,
                         const QString &login,
                         const QString &password,
                         const QString &ipAddress);

    ReturnValues authorizeUser(const QString &login, const QString &password, QTcpSocket* pClientSocket);

    QVector<User> findFriend (const QString &tokenFriend);

    User getUser(const QString &login);                  // !!!! Обсуди с Романом

    //  int showUsersLogin(QDataStream *pAuthoInfo);

    ReturnValues addFriend(const QString &userLogin, const QString &friendLogin);

    ReturnValues addGroupChat(const QString &admiLogin, QVector<QString> participantslogins, const int &IDNumber);/*, Correspondence *groupCaht);*/

    Correspondence* getGroupChat(const int &IDNumber);

    ReturnValues removeFriend(const QString &userLogin, const QString &friendLogin);

    QVector<User> getUserFriends(const QString &userLogin);

    QVector<Correspondence> getUserCorrespondence(const QString &userLogin);

    QTcpSocket* getUserTcpSocket(const QString &userLogin);

    void setNullUserTcpSocket(const QString &userLogin);

    void disconnectUser(QTcpSocket *userTcpSocket);

    void receiveMessage(const Message &newmessage);

    QVector<QTcpSocket*> reciveGroupMessage(const int &IDNumber, const Message &newmessage);

signals:
    //    void signalLoginBusu ();
    //    void signalAuthorized ();
    //    void signalLoginWrong ();
    //    void signalPasswordWrong();
private:
    // QVector<User> m_users;
    QList<User> m_users;
    //QVector<Correspondence> m_Correspondence;
    QList<Correspondence> m_Correspondence;

};
