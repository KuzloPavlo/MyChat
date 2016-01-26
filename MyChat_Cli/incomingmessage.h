#pragma once

#include <QWidget>
#include "message.h"
#include <QTextEdit>

namespace Ui {
class IncomingMessage;
}

class IncomingMessage : public QWidget
{
    Q_OBJECT

public:
    explicit IncomingMessage(QWidget *parent = 0, Message *incomingMessage = 0);
    ~IncomingMessage();

private:
    Ui::IncomingMessage *ui;
    void setMessage(const Message &message);
public slots:
    void slotResize(QTextEdit *textBrowser);
};
