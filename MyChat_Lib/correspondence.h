#pragma once
#include <QVector>
#include "message.h"
#include <user.h>
#include <QString>

class User;               // forward declaration

class Correspondence
{
public:
    Correspondence();
    Correspondence(User *sender, User *recipient);
    void addNewMessage(const Message &message);
    Message& getLastMessage();
    QVector<Message> getCorrespondence();
    bool findParticipants(const QString &sender, const QString &recipient);
private:
    QVector<Message> m_Messages;
    QVector<User*> m_participants;
};
