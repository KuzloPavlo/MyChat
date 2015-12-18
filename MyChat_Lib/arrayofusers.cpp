#include "arrayofusers.h"



ReturnValues ArrayOfUsers::addUser(
        QString *pname,
        QString *psurname,
        QString *plogin,
        QString *ppassword,
        QString *pipAddress)
{

        for (int i = 0; i < m_users.size(); i++)
        {
            if (*plogin == m_users[i].showLogin())

                return login_busy;
        }

        User newUser(pname,psurname,plogin,ppassword,pipAddress);
        m_users.push_back(newUser);

        return registered;

}



ReturnValues ArrayOfUsers::authorizeUser(QString *plogin,
                                         QString *ppassword)
{
    if (m_users.size())
    {
        for (int i = 0; i < m_users.size(); i++)
        {
            if (*plogin == m_users[i].showLogin() &&
                    *ppassword == m_users[i].showPassword())
            {
                return authorized;
            }

            if (*plogin == m_users[i].showLogin() &&
                    *ppassword != m_users[i].showPassword())
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


User ArrayOfUsers::getUser(QString *pUserLogin)
{
    User user;
    for (int i = 0; i < m_users.size(); i++)
    {
        if (*pUserLogin == m_users[i].showLogin())
        {
            user =  m_users[i];
        }

    }
    // QString empty = "";        // ??????
    //user.setPassword(&empty);  // remove password
    return user;
}




QVector<User> ArrayOfUsers::seatrchFriend (QString *pdataFriend)  //
{

    QVector<User> potentialFriends;

    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].showName().indexOf(*pdataFriend) != -1 ||
                m_users[i].showSurname().indexOf(*pdataFriend) != -1 ||
                m_users[i].showLogin().indexOf(*pdataFriend) != -1 )
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






