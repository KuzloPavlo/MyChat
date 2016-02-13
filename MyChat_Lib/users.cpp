#include "users.h"



ReturnValues Users::addUser(
        const QString &name,
        const QString &surname,
        const QString &login,
        const QString &password,
        const QString &ipAddress)
{
    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if (login == (*it).getLogin())
        {
            return ReturnValues::loginBusy;
        }
        it++;
    }

    User newUser(name,surname,login,password,ipAddress);
    m_users.push_back(newUser);

    return registered;
}

ReturnValues Users::authorizeUser(const QString &login, const QString &password, QTcpSocket*pClientSocket)
{
    QList<User>::iterator it = m_users.begin();
    while (it != m_users.end())
    {
        if (login == (*it).getLogin() &&
                password == (*it).getPassword())
        {
            (*it).setTcpSocket(pClientSocket);
            return ReturnValues::authorized;
        }

        if (login == (*it).getLogin() &&
                password != (*it).getPassword())
        {
            return ReturnValues::wrongPassword;
        }

        it++;
    }
    return ReturnValues::wrongLogin;
}



User Users::getUser(const QString &login)
{
    User user;
    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if (login == (*it).getLogin())
        {
            user =  (*it);
        }
        it++;
    }
    return user;
}


QTcpSocket* Users::getUserTcpSocket(const QString &userLogin)
{
    QTcpSocket *userTcpSocket;
    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if (userLogin ==(*it).getLogin())
        {
            userTcpSocket = (*it).getTcpSocket();
            break;
        }
        it++;
    }
    return userTcpSocket;
}


void Users::setNullUserTcpSocket(const QString &userLogin)
{
    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if(userLogin == (*it).getLogin())
        {
            // QTcpSocket *emptySocket = NULL; // сравни
            (*it).setTcpSocket(NULL);
            break;
        }
        it++;
    }
}


void Users::disconnectUser(QTcpSocket *userTcpSocket)
{
    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if(userTcpSocket == (*it).getTcpSocket())
        {
            (*it).setTcpSocket(NULL);
            qDebug()<< "DISCONNECTED " << (*it).getLogin();
            break;
        }
        it++;
    }
}


QVector<User> Users::findFriend (const QString &tokenFriend)
{

    QVector<User> potentialFriends;

    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if ((*it).getName().indexOf(tokenFriend) != -1 ||
                (*it).getSurname().indexOf(tokenFriend) != -1 ||
                (*it).getLogin().indexOf(tokenFriend) != -1 )
        {
            potentialFriends.push_back(*it);
        }
        it++;
    }
    return potentialFriends;
}




ReturnValues Users::addFriend(const QString &userLogin,
                              const QString &friendLogin)
{
    User *puser = NULL;
    User *pfriend = NULL;

    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if (userLogin == (*it).getLogin())
        {
            puser =& (*it);
        }

        if (friendLogin == (*it).getLogin())
        {
            pfriend =& (*it);
        }

        if (puser && pfriend)
        {
            Correspondence correspondence(puser, pfriend); //create correspondence
            m_Correspondence.push_back(correspondence);

            QList<Correspondence>::iterator j = m_Correspondence.begin();

            while(j != m_Correspondence.end())
            {
                if((*j).findParticipants(userLogin, friendLogin))
                {
                    puser->addFriend(pfriend, &(*j));
                    pfriend->addFriend(puser, &(*j));
                    return ReturnValues::addedFriend;
                }
                j++;
            }
        }
        it++;
    }
    return ReturnValues::returnNull;
}


ReturnValues Users::addGroupChat(const QString &admiLogin, QVector<QString> participantslogins, const int &IDNumber)/*,Correspondence *groupCaht)*/
{
    User *admin;
    QVector<User*> participants;

    QList<User>::iterator it = m_users.begin();

    while (it != m_users.end())
    {
        if(admiLogin == (*it).getLogin())
        {
            admin =& (*it);
            it++;
            continue;
        }

        for(int j = 0; j < participantslogins.size(); j++)
        {
            if(participantslogins[j] ==  (*it).getLogin())
            {
                participants.push_back(&(*it));
                break;
            }
        }
        it++;
    }

    Correspondence correspondence(admin, participants,IDNumber);
    m_Correspondence.push_back(correspondence);

    QList<Correspondence>::iterator j = m_Correspondence.begin();

    while(j != m_Correspondence.end())
    {
        if((*j).findIDNumber(IDNumber))
        {

            admin->addGroupCorrespondence(&(*j));

            for(int h = 0; h < participants.size(); h++)
            {
                participants[h]->addGroupCorrespondence(&(*j));

            }
            break;
        }
        j++;
    }
    return createdChat;
}


Correspondence* Users::getGroupChat(const int &IDNumber)
{
    QList<Correspondence>::iterator j = m_Correspondence.begin();

    while(j != m_Correspondence.end())
    {
        if((*j).findIDNumber(IDNumber))
        {
            return &(*j);
        }
        j++;
    }
    return NULL;
}

QVector<User> Users::getUserFriends(const QString &userLogin)
{
    QVector<User> friends;

    QList<User>::iterator it = m_users.begin();
    while (it != m_users.end())
    {
        if (userLogin == (*it).getLogin())
        {
            friends = (*it).getFriends();
            break;
        }
        it++;
    }
    return friends;
}


QVector<Correspondence> Users::getUserCorrespondence(const QString &userLogin)
{
    QVector<Correspondence> correspondence;

    QList<User>::iterator it = m_users.begin();
    while (it != m_users.end())
    {
        if (userLogin ==  (*it).getLogin())
        {
            correspondence =  (*it).getCorrespondence();
            break;
        }
        it++;
    }
    return correspondence;
}


ReturnValues Users::removeFriend(const QString &userLogin, const QString &friendLogin)
{
    User *puser = NULL;
    User *pfriend = NULL;

    QList<User>::iterator it = m_users.begin();
    while (it != m_users.end())
    {
        if (userLogin == (*it).getLogin())
        {
            puser =& (*it);
        }

        if (friendLogin == (*it).getLogin())
        {
            pfriend =& (*it);
        }

        if (puser && pfriend)
        {
            puser->removeFriend(friendLogin);
            pfriend->removeFriend(userLogin);
            return ReturnValues::removedFriend;
        }
        it++;
    }
    return ReturnValues::returnNull;
}



void Users::receiveMessage(const Message &newmessage)
{
    QList<Correspondence>::iterator j = m_Correspondence.begin();

    while(j != m_Correspondence.end())
    {
        if((*j).findParticipants(newmessage.mSender, newmessage.mRecipient))
        {
            (*j).addNewMessage(newmessage);
            break;
        }
        j++;
    }
}



QVector<QTcpSocket*> Users::reciveGroupMessage(const int &IDNumber, const Message &newmessage)
{
    QVector<QTcpSocket*> participantsTcpSockets;
    QVector<QString> participants;
    QList<Correspondence>::iterator j = m_Correspondence.begin();

    while(j != m_Correspondence.end())
    {
        if((*j).getIDNumber() == IDNumber)
        {
            (*j).addNewMessage(newmessage);
            participants = (*j).getParticipants();
            break;
        }
        j++;
    }

    for(int i = 0; i < participants.size(); i++)
    {
        if(participants[i] != newmessage.mSender)
        {
            participantsTcpSockets.push_back(this->getUserTcpSocket(participants[i]));
        }
    }

    return participantsTcpSockets;
}


//int Users::showUsersLogin(QDataStream *pAuthoInfo)
//{
//    for(int i = 0; i < m_users.size(); i++)
//        m_users[i].getLogin();

//    QString login;
//    QString password;

//    pAuthoInfo->setVersion (QDataStream::Qt_5_5);
//    *pAuthoInfo>> login >> password;

//    qDebug() << login;
//    qDebug() << password;

//    for (int i = 0; i < m_users.size(); i++)
//    {
//        qDebug() << m_users[i].getLogin();
//    }

//    return 0;
//}






