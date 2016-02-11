#pragma once

#include <QWidget>
#include <QString>
#include <QListWidget>

namespace Ui {
class FormChat;
}

class FormChat : public QWidget
{
    Q_OBJECT

public:
    explicit FormChat(
            const int &IDNumer,
            const QString &chatName,
            QVector<QString> participants,
            QListWidget *listWidget,
            QWidget *parent = 0);
    ~FormChat();

    int getIDNumber();

private:
    Ui::FormChat *ui;
    int m_IDNumber;
    QString m_ChatName;
    QListWidget *m_listWidget;
};
