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
    void addNewMessage(const Message &message);
    Message getLastMessage();
    QVector<Message> getCorrespondence();
    void setParticipants(User *participant1,User *participant2);
    void addParticipant(User *participant);
    bool findParticipants(const QString &sender, const QString &recipient);
    int getIDNumber();
    void setIDNumber(int IDNumber);
    QVector<QString> getParticipants();
private:
    QVector<Message> m_Messages;
    QVector<User*> m_participants;
    int m_IDNumber;
};
