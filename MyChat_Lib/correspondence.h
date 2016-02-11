#pragma once
#include <QVector>
#include "message.h"
#include <QString>

class User;               // forward declaration

class Correspondence
{
public:
    Correspondence();
    Correspondence(User *sender, User *recipient);
    Correspondence(User *admin, QVector<User*> participants, const int &IDNumber);
    void addNewMessage(const Message &message);
    Message getLastMessage();
    QVector<Message> getCorrespondence();
    void setParticipants(User *participant1,User *participant2);
    void addParticipant(User *participant);
    void addParticipant(const QString &notFriend);
    bool findParticipants(const QString &sender, const QString &recipient);
    bool findIDNumber(const int &IDNumber);
    int getIDNumber();
    void setIDNumber(int IDNumber);
    QVector<QString> getParticipants();
    QVector<QString> getDataParticipants();
    QVector<QString> getDataAdmin();
    QVector<QString> getNotFriends();
    User* getAdmin();
    QString getChatName();
private:
    QVector<Message> m_Messages;
    QVector<User*> m_participants;
    QVector<QString> m_notFriends;
    QString m_ChatName;
    int m_IDNumber;
    User *m_admin;
};
