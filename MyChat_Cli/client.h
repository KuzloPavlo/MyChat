#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QDataStream>
#include <QString>
#include <QList>
#include "user.h"
#include "messagetypes.h"
#include "returnvalues.h"
#include "message.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

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
            const QDateTime &dataTime);

    void sendMessage(
            const QString &sender,
            const int & IDNumber,
            const QString &messageText,
            const QDateTime &dataTime);

public:

    QByteArray m_block;
    QDataStream *m_out;


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
    void signalFoundFriend(const QString &login);
    void signalNewFriend();
    void signalNewGroupChat();
    void signalIncomingMessage(
            const QString &sender,
            const QString &message,
            const QString &time);

    void signalGroupIncomingMessage(
            const int &IDnumber,
            const QString &sender,
            const QString &message,
            const QString &time);

    void signalEarlierReceivedMessage(
            const int &IDNumber,
            const QString &sender,
            const QString &message,
            const QString &time
            );

    void signalEarlierSendMessage(
            const int &IDNumber,
            const QString &sender,
            const QString &message,
            const QString &time);

    void signalAddFriendToList(const QString &login);

    void signalAddChatToList(const int &IDNumer,
                             const QString &chatName,
                             QVector<QString> participants);

    void signalShowFriend(const QString &name,
                          const QString &surname,
                          const QString &login);

    void signalShowFriend(const QString &login);

    void signalShowChat(
            const int &IDNumber,
            const QString &chatName,
            QVector<QString> admin,
            QVector<QString> friends,
            QVector<QString> notFriends);

    void signalShowPotentialFriend(const QString &name,
                                   const QString &surname,
                                   const QString &login);

    void f(const QString &str);

private:
    QTcpSocket *m_psocket;
    quint16 m_nnextBlockSize;
    User m_user;
    QVector<User> m_potentialFriends;
    QList<User> m_friends;
    QList<Correspondence> m_Correspondence;



    void sendToServer(QDataStream *out, QByteArray *block);
    //  void sendToServer();
    void processRegistrationResponse(QDataStream *in);
    void processAuthorizationResponse(QDataStream *in);
    void setAuthorizedUser(QDataStream *in);

    void processFindFriendResponse(QDataStream *in);
    void processAddFriendResponse(QDataStream *in);
    void processCreateGroupChatResponse(QDataStream *in);
    void setNewFriend(QDataStream *in);
    void setNewGroupChat(QDataStream *in);
    void getFriends();
    void getCorrespondence();
    void setFriends(QDataStream *in);
    void setCorrespondence(QDataStream *in);
    //void showCorrespondence(const QString &sender, const QString &recipient);

    void receiveMessage(QDataStream *in);

    void receiveGroupMessage(QDataStream *in);



private slots:
    void slotReadServer();
    //    void slotSetUser(const QString &pname,
    //                     const QString &psurname,
    //                     const QString &plogin,
    //                     const QString &ppassword,
    //                     const QString &pipAddress);

    void slotShowListFriends();

    void slotShowListChats();

    void slotFindParticipants(const QString &tokenParticipant);

    void slotShowFriend(const QString &login);

    void slotShowChat(const int &IDNumber);

    void slotShowPotentialFriend(const QString &login);

    void slotCrateNewGroupChat(QVector<QString> participants);

    // void slotSearchFriendResponsFound(QVector<User> potentialFriends);

};
