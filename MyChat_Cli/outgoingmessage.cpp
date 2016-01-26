#include "outgoingmessage.h"
#include "ui_outgoingmessage.h"

OutgoingMessage::OutgoingMessage(QWidget *parent, Message *outgoingMessage) :
    QWidget(parent),
    ui(new Ui::OutgoingMessage)
{
    ui->setupUi(this);
    setMessage(*outgoingMessage);
    emit slotResize(ui->text);
}

OutgoingMessage::~OutgoingMessage()
{
    delete ui;
}

void OutgoingMessage::setMessage(const Message &message)
{
    this->ui->user->setText(message.mSender);
    this->ui->text->setText(message.mMessageText);
    this->ui->time->setText(message.mDataTime.time().toString());
}

void OutgoingMessage::slotResize(QTextEdit *textBrowser)
{
    textBrowser->document()->adjustSize();
    QSize size = textBrowser->document()->size().toSize() + QSize(0,0);
    this->setMaximumHeight(size.height());
    this->setMinimumHeight(size.height());
}
