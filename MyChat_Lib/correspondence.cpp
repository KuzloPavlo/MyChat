#include "correspondence.h"

void Correspondence::addNewMessage(const Message &message)
{
    m_Messages.push_back(message);

    // Тут необхідно дописати сортування масиву по даті
    //при добавлені нового повідомлення
}

QVector<Message> Correspondence::getCorrespondence()
{
    return m_Messages;
}

Message& Correspondence::getLastMessage()
{
    return m_Messages.back();
}
