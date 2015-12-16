#include "arrayofusers.h"

ReturnValues ArrayOfUsers::addUser(QDataStream *pNewUserInfo)
{
    qDebug() << "LIB users.cpp 5";
    QString name ;
    QString surname;
    QString login;
    QString password;
    QString ipAddress = "127.0.0.1";  // Нужно реализовввать получение IP адреса.

    pNewUserInfo->setVersion (QDataStream::Qt_5_5);
    *pNewUserInfo >> name
            >> surname
            >> login
            >> password;

    qDebug() << name;
    qDebug() << surname;
    qDebug() << login;
    qDebug() << password;
    qDebug() << "LIB users.cpp s 14-18";

    if (m_users.size())
    {
        for (int i = 0; i < m_users.size(); i++)
        {
            if (login == m_users[i].showLogin())

                return login_busy;
        }

        User newUser(&name,&surname,&login,&password,&ipAddress);
        m_users.push_back (newUser);
        signalRegistered (m_users[m_users.size ()-1].showLogin(),
                m_users[m_users.size ()-1].showPassword());

        return registered;
    }

    if (!m_users.size ())
    {
        User newUser(&name,&surname,&login,&password,&ipAddress);
        m_users.push_back (newUser);
        signalRegistered (m_users[m_users.size ()-1].showLogin(),
                m_users[m_users.size ()-1].showPassword());

        return registered;
    }

    return  return_null;
}



ReturnValues ArrayOfUsers::authorizeUser(QDataStream *pAuthoInfo)
{
    QString login;
    QString password;

    pAuthoInfo->setVersion(QDataStream::Qt_5_5);
    *pAuthoInfo >> login
            >> password;

    if (m_users.size())
    {
        for (int i = 0; i < m_users.size(); i++)
        {
            if (login == m_users[i].showLogin() &&
                    password == m_users[i].showPassword())
            {
                return authorized;
            }

            if (login == m_users[i].showLogin() &&
                    password != m_users[i].showPassword())
            {
                return wrong_password;
            }
        }

        return wrong_login;
    }

    else
    {
        return is_empty;
    }

    return return_null;
}




QVector<User> ArrayOfUsers::seatrchFriend (QDataStream *pFriendInfo)
{
    QString dataUser;
    QVector<User> potentialFriends;

    pFriendInfo->setVersion(QDataStream::Qt_5_5);
    *pFriendInfo >> dataUser;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].showName().indexOf(dataUser) != -1 ||
                m_users[i].showSurname().indexOf(dataUser) != -1 ||
                m_users[i].showLogin().indexOf(dataUser) != -1 )
        {
            User tempUser = m_users[i];
            potentialFriends.push_back(tempUser);
        }
    }

    return potentialFriends;
}




ReturnValues ArrayOfUsers::addFriend(QDataStream *pNewFriendInfo)
{
    QString userLogin;
    QString friendLogin;
    User *puser = NULL;
    User *pfriend = NULL;

    pNewFriendInfo->setVersion(QDataStream::Qt_5_5);
    *pNewFriendInfo >> userLogin
            >> friendLogin;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].showLogin())
        {
            puser =& m_users[i];
        }

        if (friendLogin == m_users[i].showLogin())
        {
            pfriend =& m_users[i];
        }

        if (puser && pfriend)
        {
            puser->addFriend(pfriend);
            pfriend->addFriend(puser);

            return added_friend;
        }
    }
    return return_null;
}




QVector<User> ArrayOfUsers::getUserFriends(QDataStream *pUserInfo)
{
    QString userLogin;
    QVector<User> friends;

    pUserInfo->setVersion(QDataStream::Qt_5_5);
    *pUserInfo >> userLogin;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].showLogin())
        {
            friends = m_users[i].getFriends();
            break;
        }

    }
    return   friends;
}




ReturnValues ArrayOfUsers::removingFriend(QDataStream *pRemoveFriendInfo)
{
    QString userLogin;
    QString friendLogin;

    pRemoveFriendInfo->setVersion(QDataStream::Qt_5_5);
    *pRemoveFriendInfo >> userLogin
            >> friendLogin;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (userLogin == m_users[i].showLogin())
        {
            m_users[i].removingFriend(&friendLogin);
            break;
        }
    }

    return removed_friend;
}





int ArrayOfUsers::showUsersLogin(QDataStream *pAuthoInfo)
{
    for(int i = 0; i < m_users.size(); i++)
        m_users[i].showLogin();

    QString login;
    QString password;

    pAuthoInfo->setVersion (QDataStream::Qt_5_5);
    *pAuthoInfo>> login >> password;

    qDebug() << login;
    qDebug() << password;

    for (int i = 0; i < m_users.size(); i++)
    {
        qDebug() << m_users[i].showLogin();
    }

    return 0;
}




void ArrayOfUsers::signalRegistered(QString login, QString password)
{

}




void  ArrayOfUsers::signalLoginBusu()
{

}
