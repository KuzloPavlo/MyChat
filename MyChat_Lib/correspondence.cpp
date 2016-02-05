#include "correspondence.h"

#include "user.h"

Correspondence::Correspondence()
{
qDebug()<< "1Correspondence()1";
}

Correspondence::Correspondence(User *sender, User *recipient)
{
    m_participants.push_back(sender);
    m_participants.push_back(recipient);
    m_IDNumber = 0; // it is tet-a-tet chat
}


void Correspondence::addNewMessage(const Message &message)
{
    m_Messages.push_back(message);

    // Тут необхідно дописати сортування масиву по даті
    //при добавлені нового повідомлення

    qDebug() << "From correspondenc Class" << message.mMessageText;
}


QVector<Message> Correspondence::getCorrespondence()
{
    return m_Messages;
}

void Correspondence::setParticipants(User *participant1,User *participant2)
{
    m_participants.push_back(participant1);
    m_participants.push_back(participant2);
}

void Correspondence::addParticipant(User *participant)
{
    m_participants.push_back(participant);
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


int Correspondence::getIDNumber()
{
    return m_IDNumber;
}

void Correspondence::setIDNumber(int IDNumber)
{
    m_IDNumber = IDNumber;
}

QVector<QString> Correspondence::getParticipants()
{
    QVector<QString> Participants;
    for(int i = 0; i < m_participants.size(); i++)
    {
        Participants.push_back(m_participants[i]->getLogin());
    }
    return Participants;
}


Message Correspondence::getLastMessage()
{
    return m_Messages[m_Messages.size()-1];
}
