#pragma once

#include <QWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QSize>
#include "message.h"

namespace Ui {
class OutgoingMessage;
}

class OutgoingMessage : public QWidget
{
    Q_OBJECT

public:
     OutgoingMessage(QWidget *parent = 0, Message *outgoingMessage = 0);
    ~OutgoingMessage();

private:
    Ui::OutgoingMessage *ui;
    void setMessage(const Message &message);

public slots:
    void slotResize(QTextEdit *textBrowser);
};
