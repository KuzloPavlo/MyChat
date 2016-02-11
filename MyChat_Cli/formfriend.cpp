#include "formfriend.h"
#include "ui_formfriend.h"

FormFriend::FormFriend(
        const QString &name,
        const QString &surname,
        const QString &login,QWidget *parent) : m_login(login),
    QWidget(parent),
    ui(new Ui::FormFriend)
{
    ui->setupUi(this);
    ui->deleteParticipant->setVisible(false);
    ui->Online->setVisible(false);
    ui->Login->setText(name + " " + surname);
}

FormFriend::~FormFriend()
{
    delete ui;
}
