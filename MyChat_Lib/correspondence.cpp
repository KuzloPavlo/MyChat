#include "correspondence.h"

Correspondence::Correspondence()
{

}

Correspondence::Correspondence(User *sender, User *recipient)
{
    m_participants.push_back(sender);
    m_participants.push_back(recipient);
}


void Correspondence::addNewMessage(const Message &message)
{
    m_Messages.push_back(message);

    // Тут необхідно дописати сортування масиву по даті
    //при добавлені нового повідомлення

    qDebug() << "from" << message.mMessageText;
}


QVector<Message> Correspondence::getCorrespondence()
{
    return m_Messages;
}



bool Correspondence::findParticipants(const QString &sender, const QString &recipient)
{
    if (sender == m_participants[0]->getLogin() || sender == m_participants[1]->getLogin())
    {
        if (recipient == m_participants[0]->getLogin() || recipient == m_participants[1]->getLogin())
        {
            return true;
        }
    }
    return false;
}



Message& Correspondence::getLastMessage()
{
    return m_Messages.back();
}
