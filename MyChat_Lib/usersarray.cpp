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



QVector<User> UsersArray::findFriend (const QString &tokenFriend)  //
{

    QVector<User> potentialFriends;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].getName().indexOf(tokenFriend) != -1 ||
                m_users[i].getSurname().indexOf(tokenFriend) != -1 ||
                m_users[i].getLogin().indexOf(tokenFriend) != -1 )
        {
            // User tempUser = ;            // вот єто
            potentialFriends.push_back(m_users[i]);//tempUser);  // поробуй сразу вставить
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
            //puser->addFriend(pfriend);
            //pfriend->addFriend(puser);

            Correspondence correspondence;
            m_Correspondence.push_back(correspondence);

            Interlocutor newfriend;
            newfriend.m_correspondence =& m_Correspondence.back();

            newfriend.m_user = pfriend;
            puser->addFriend(newfriend);

            newfriend.m_user = puser;
            pfriend->addFriend(newfriend);

            return ReturnValues::addedFriend;
        }
    }
    return ReturnValues::returnNull;
}





QVector<User> UsersArray::getUserFriends(QDataStream *pUserInfo)
{
    QString userLogin;
    QVector<User> friends;

    pUserInfo->setVersion(QDataStream::Qt_5_5);
    *pUserInfo >> userLogin;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].getLogin())
        {
            friends = m_users[i].getFriends();
            break;
        }

    }
    return   friends;
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


}


QString UsersArray::getUserIPAddress(const QString &userLogin)
{

    return "asdj";
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






