#include "servermessage.h"
#include "ui_formmessage.h"

ServerMessage::ServerMessage(
        const QString &sender,
        const QString &message,
        const QString &time,
        QWidget *parent ) : FormMessage (sender, message, time, parent)
{

    this->ui->empty->setMinimumWidth(40);
    this->ui->empty->setMaximumWidth(40);
    this->ui->user->setMinimumWidth(60);
    this->ui->user->setMaximumWidth(60);

}

