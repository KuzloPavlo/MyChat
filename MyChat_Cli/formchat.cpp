#include "formchat.h"
#include "ui_formchat.h"

FormChat::FormChat(
        const int &IDNumer,
        const QString &chatName,
        const QString &admin,
        QVector<QString> participants,
        QListWidget *listWidget,
        QWidget *parent) :

    m_IDNumber(IDNumer),
    m_ChatName(chatName),
    m_admin(admin),
    m_participants(participants),
    m_listWidget(listWidget),
    QWidget(listWidget),
    ui(new Ui::FormChat)
{
    ui->setupUi(this);
    ui->ChatNamelabel->setText(m_ChatName);

    QString participantsLogin = "";

    for (int i = 0; i < m_participants.size(); i++)
    {
        QString participant = " " + m_participants[i] + ",";

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
