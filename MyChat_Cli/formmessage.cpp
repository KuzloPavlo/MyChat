#include "formmessage.h"
#include "ui_formmessage.h"

FormMessage::FormMessage(
        const QString &sender,
        const QString &message,
        const QString &time,
        QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormMessage)
{
    ui->setupUi(this);
    setMessage(sender, message, time);
    emit slotResize(ui->text);
}

FormMessage::~FormMessage()
{
    delete ui;
}


void FormMessage::setMessage(
        const QString &sender,
        const QString &message,
        const QString &time)
{
    this->ui->user->setText(sender);
    this->ui->text->setText(message);
    this->ui->time->setText(time);
}


void FormMessage::slotResize(QTextEdit *textBrowser)
{
    textBrowser->document()->adjustSize();
    QSize size = textBrowser->document()->size().toSize() + QSize(0,0);

    if (size.height() > this->minimumHeight())
    {
        this->setMaximumHeight(size.height());
        this->setMinimumHeight(size.height());
    }
    else
    {
        setMaximumHeight(this->minimumHeight());
        setMinimumHeight(this->minimumHeight());
    }
}
