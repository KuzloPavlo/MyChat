#include "outgoingmessage.h"
#include "ui_formmessage.h"

OutgoingMessage::OutgoingMessage(
        const QString &sender,
        const QString &message,
        const QString &time,
        QWidget *parent ) : FormMessage (sender, message, time, parent)
{
    this->ui->empty->setMinimumWidth(0);
    this->ui->empty->setMaximumWidth(0);
    this->ui->user->setMinimumWidth(100);
    this->ui->user->setMaximumWidth(100);
}

