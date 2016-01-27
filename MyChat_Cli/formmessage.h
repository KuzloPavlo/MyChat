#pragma once

#include <QWidget>
#include <QTextBrowser>
#include <QTextEdit>
#include <QSize>
#include "message.h"


namespace Ui {
class FormMessage;
}

class FormMessage : public QWidget
{
    Q_OBJECT

public:
    explicit FormMessage(
            const QString &sender,
            const QString &message,
            const QString &time,
            QWidget *parent = 0);

    ~FormMessage();

protected:
    Ui::FormMessage *ui;
    void setMessage(
            const QString &sender,
            const QString &message,
            const QString &time);

public slots:
    void slotResize(QTextEdit *textBrowser);
};
