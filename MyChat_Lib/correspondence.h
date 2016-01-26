#pragma once
#include <QVector>
#include "message.h"

class Correspondence
{
public:
    void addNewMessage(const Message &message);
    Message& getLastMessage();
    QVector<Message> getCorrespondence();
private:
    QVector<Message> m_Messages;
};
