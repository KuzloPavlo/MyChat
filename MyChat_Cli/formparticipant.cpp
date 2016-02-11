#include "formparticipant.h"
#include "ui_formfriend.h"

FormParticipant::FormParticipant(
        const QString &name,
        const QString &surname,
        const QString &login,
        QWidget *parent) : FormFriend(name,surname,login,parent)
{
    ui->deleteParticipant->setVisible(true);
}

FormParticipant::FormParticipant(const QString &login,
                                 QWidget *parent) : FormFriend(login,login,login,parent)
{
    ui->Login->setText(login);
}
