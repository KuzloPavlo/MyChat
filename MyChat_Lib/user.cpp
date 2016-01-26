#include "user.h"


User::User()
{

}




User::User( const QString &pname,
            const QString &psurname,
            const QString &plogin,
            const QString &ppassword,
            const QString &pipAddress)
    : m_name(pname),
      m_surname(psurname),
      m_login(plogin),
      m_password(ppassword),
      m_ipAddress(pipAddress) {}



void User::addFriend(const Interlocutor &pfriend)
{
    m_interlocutors.push_back(pfriend);
}



QVector<User> User::getFriends()
{

    QVector<User> friends;

    for (int i = 0; i < m_friends.size(); i++)
    {
        User temp = *m_friends[i];

        friends.push_back(temp);
    }

    return friends;
}




void User::removeFriend(const QString &friendLogin)
{
    QVector<User*>::iterator p = m_friends.begin();

    while ((*p)->getLogin() != friendLogin)
    {
        p++;
    }
    m_friends.erase(p);
}




QString User::getName()
{
    return this->m_name;
}

QString User::getSurname()
{
    return this->m_surname;
}

QString User::getLogin()
{
    return this->m_login;
}

QString User::getPassword()
{
    return this->m_password;
}

QString User::getIPAddress()
{
    return this->m_ipAddress;
}


QTcpSocket* User::getTcpSocket()
{
    return m_pUserSocket;
}


void User::setName(QString *pname)
{
    this->m_name =* pname;

}

void User::setSurname(QString *psurname)
{

    this->m_surname = *psurname;
}


void User::setLogin(QString *plogin)
{

    this->m_login = *plogin;
}

void User::setPassword(QString *ppassword)
{
    this->m_password = *ppassword;
}

void User::setIPAddress(QString *pipAddress)
{
    this->m_ipAddress = *pipAddress;
}

void User::setTcpSocket(QTcpSocket *pClientSocket)
{
    this->m_pUserSocket = pClientSocket;
}
