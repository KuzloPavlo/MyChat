#include "formchat.h"
#include "ui_formchat.h"

FormChat::FormChat(
        const int &IDNumer,
        const QString &chatName,
        QVector<QString> participants,
        QListWidget *listWidget,
        QWidget *parent) :

    m_IDNumber(IDNumer),
    m_ChatName(chatName),
    m_listWidget(listWidget),
    QWidget(listWidget),
    ui(new Ui::FormChat)
{
    ui->setupUi(this);
    ui->ChatNamelabel->setText(m_ChatName);

    QString participantsLogin = "";

    for (int i = 0; i < participants.size() && i < 3 ; i++)
    {
        QString participant = " " + participants[i] + ",";

        participantsLogin += participant;
    }

    ui->Userslabel->setText(participantsLogin);

    QListWidgetItem *item = new QListWidgetItem (m_listWidget);

    m_listWidget->setItemWidget(item, this);
}

FormChat::~FormChat()
{
    delete ui;
}


int FormChat::getIDNumber()
{
    return m_IDNumber;
}
