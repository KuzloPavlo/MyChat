#include "usersarray.h"



ReturnValues UsersArray::addUser(
        const QString &name,
        const QString &surname,
        const QString &login,
        const QString &password,
        const QString &ipAddress)
{

    for (int i = 0; i < m_users.size(); i++)
    {
        if (login == m_users[i].getLogin())

            return ReturnValues::loginBusy;
    }

    User newUser(name,surname,login,password,ipAddress);
    m_users.push_back(newUser);

    return registered;
}



ReturnValues UsersArray::authorizeUser(const QString &login, const QString &password, QTcpSocket*pClientSocket)
{
    if (m_users.size())
    {
        for (int i = 0; i < m_users.size(); i++)
        {
            if (login == m_users[i].getLogin() &&
                    password == m_users[i].getPassword())
            {
                m_users[i].setTcpSocket(pClientSocket);
                return ReturnValues::authorized;
            }

            if (login == m_users[i].getLogin() &&
                    password != m_users[i].getPassword())
            {
                return ReturnValues::wrongPassword;
            }
        }

        return ReturnValues::wrongLogin;
    }

    else
    {
        return ReturnValues::isEmpty;
    }

    return ReturnValues::returnNull;
}


User UsersArray::getUser(const QString &login)
{
    User user;
    for (int i = 0; i < m_users.size(); i++)
    {
        if (login == m_users[i].getLogin())
        {
            user =  m_users[i];
        }

    }
    // QString empty = "";        // ??????
    //user.setPassword(&empty);  // remove password
    return user;
}


QTcpSocket* UsersArray::getUserTcpSocket(const QString &userLogin)
{
    QTcpSocket *userTcpSocket;
    for(int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            userTcpSocket = m_users[i].getTcpSocket();
            break;
        }
    }
    return userTcpSocket;
}


void UsersArray::setNullUserTcpSocket(const QString &userLogin)
{
    for(int i = 0; i < m_users.size(); i++)
    {
        if(userLogin == m_users[i].getLogin())
        {
            // QTcpSocket *emptySocket = NULL; // сравни
            m_users[i].setTcpSocket(NULL);
            break;
        }
    }
}


void UsersArray::disconnectUser(QTcpSocket *userTcpSocket)
{

    for(int i = 0; i < m_users.size(); i++)
    {
        if(userTcpSocket == m_users[i].getTcpSocket())
        {
            m_users[i].setTcpSocket(NULL);
            qDebug()<< "DISCONNECTED " << m_users[i].getLogin();
            break;
        }
    }
}


QVector<User> UsersArray::findFriend (const QString &tokenFriend)
{

    QVector<User> potentialFriends;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getName().indexOf(tokenFriend) != -1 ||
                m_users[i].getSurname().indexOf(tokenFriend) != -1 ||
                m_users[i].getLogin().indexOf(tokenFriend) != -1 )
        {
            potentialFriends.push_back(m_users[i]);
        }
    }
    return potentialFriends;
}




ReturnValues UsersArray::addFriend(const QString &userLogin,
                                   const QString &friendLogin)
{
    User *puser = NULL;
    User *pfriend = NULL;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            puser =& m_users[i];
        }

        if (friendLogin == m_users[i].getLogin())
        {
            pfriend =& m_users[i];
        }

        if (puser && pfriend)
        {
            Correspondence correspondence(puser, pfriend); //create correspondence
            m_Correspondence.push_back(correspondence);

            for (int i = 0; i < m_Correspondence.size(); i++)
            {
                if(m_Correspondence[i].findParticipants(userLogin, friendLogin))
                {
                    puser->addFriend(pfriend, &m_Correspondence[i]);
                    pfriend->addFriend(puser, &m_Correspondence[i]);
                    return ReturnValues::addedFriend;
                }
            }
        }
    }
    return ReturnValues::returnNull;
}


ReturnValues UsersArray::addGroupChat(const QString &admiLogin, QVector<QString> participantslogins, const int &IDNumber)/*,Correspondence *groupCaht)*/
{
    qDebug() << "UsersArray::addGroupChat1";
    User *admin;
    QVector<User*> participants;
    for(int i = 0; i < m_users.size(); i++)
    {qDebug() << "UsersArray::addGroupChat11";
        if(admiLogin == m_users[i].getLogin())
        {qDebug() << "UsersArray::addGroupChat2";
            admin =& m_users[i];
            continue;
        }

        for(int j = 0; j < participantslogins.size(); j++)
        {qDebug() << "UsersArray::addGroupChat3";
            if(participantslogins[j] ==  m_users[i].getLogin())
            {qDebug() << "UsersArray::addGroupChat4";
                participants.push_back(&m_users[i]);
                break;
            }
        }
    }
    qDebug() << "UsersArray::addGroupChat5";
    Correspondence correspondence(admin, participants,IDNumber);
    m_Correspondence.push_back(correspondence);
    qDebug() << "UsersArray::addGroupChat51";
    for(int t = 0; t < m_Correspondence.size(); t++)
    {qDebug() << "UsersArray::addGroupChat52";
        if(m_Correspondence[t].findIDNumber(IDNumber))
        {
            // groupCaht =& m_Correspondence[t];
            // qDebug() << groupCaht->getIDNumber();
            qDebug() << "UsersArray::addGroupChat6";
            admin->addGroupCorrespondence(&m_Correspondence[t]);
            qDebug() << "UsersArray::addGroupChat7";
            for(int h = 0; h < participants.size(); h++)
            {qDebug() << "UsersArray::addGroupChat8";
                participants[h]->addGroupCorrespondence(&m_Correspondence[t]);
                qDebug() << "UsersArray::addGroupChat9";
            }
            break;
        }
    }
    qDebug() << "UsersArray::addGroupChat10";
    return createdChat;
}


Correspondence* UsersArray::getGroupChat(const int &IDNumber)
{
    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(m_Correspondence[i].findIDNumber(IDNumber))
        {
            return &m_Correspondence[i];
        }
    }
    return NULL;
}

QVector<User> UsersArray::getUserFriends(const QString &userLogin)
{
    QVector<User> friends;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            friends = m_users[i].getFriends();
            break;
        }
    }
    return friends;
}


QVector<Correspondence> UsersArray::getUserCorrespondence(const QString &userLogin)
{
    qDebug()<< "1UsersArray::getUserCorrespondence1";
    QVector<Correspondence> correspondence;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            qDebug()<< "1UsersArray::getUserCorrespondence2";
            correspondence = m_users[i].getCorrespondence();
            qDebug()<< "1UsersArray::getUserCorrespondence3";
            break;
        }
    }
    qDebug()<< "1UsersArray::getUserCorrespondence2";
    return correspondence;

}


ReturnValues UsersArray::removeFriend(const QString &userLogin, const QString &friendLogin)
{
    User *puser = NULL;
    User *pfriend = NULL;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            puser =& m_users[i];
        }

        if (friendLogin == m_users[i].getLogin())
        {
            pfriend =& m_users[i];
        }

        if (puser && pfriend)
        {
            puser->removeFriend(friendLogin);
            pfriend->removeFriend(userLogin);
            return ReturnValues::removedFriend;
        }
    }
    return ReturnValues::returnNull;
}



void UsersArray::receiveMessage(const Message &newmessage)
{
    for(int i = 0; i < m_Correspondence.size(); i++)
    {
        if(m_Correspondence[i].findParticipants(newmessage.mSender, newmessage.mRecipient))
        {
            m_Correspondence[i].addNewMessage(newmessage);
            break;
        }
    }
}



int UsersArray::showUsersLogin(QDataStream *pAuthoInfo)
{
    for(int i = 0; i < m_users.size(); i++)
        m_users[i].getLogin();

    QString login;
    QString password;

    pAuthoInfo->setVersion (QDataStream::Qt_5_5);
    *pAuthoInfo>> login >> password;

    qDebug() << login;
    qDebug() << password;

    for (int i = 0; i < m_users.size(); i++)
    {
        qDebug() << m_users[i].getLogin();
    }

    return 0;
}






