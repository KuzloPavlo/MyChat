#include "incomingmessage.h"
#include "ui_incomingmessage.h"

IncomingMessage::IncomingMessage(QWidget *parent, Message *incomingMessage):
    QWidget(parent),
    ui(new Ui::IncomingMessage)
{
    ui->setupUi(this);
    setMessage(*incomingMessage);
    emit slotResize(ui->text);
}

IncomingMessage::~IncomingMessage()
{
    delete ui;
}

void IncomingMessage::setMessage(const Message &message)
{
    this->ui->user->setText(message.mSender);
    this->ui->text->setText(message.mMessageText);
    this->ui->time->setText(message.mDataTime.time().toString());
}

void IncomingMessage::slotResize(QTextEdit *textBrowser)
{
    textBrowser->document()->adjustSize();
    QSize size = textBrowser->document()->size().toSize() + QSize(0,0);
    this->setMaximumHeight(size.height());
    this->setMinimumHeight(size.height());
}
