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
            const QString &admin,
            QVector<QString> participants,
            QListWidget *listWidget,
            QWidget *parent = 0);
    ~FormChat();

private:
    Ui::FormChat *ui;
public:
    int m_IDNumber;
    QString m_ChatName;
    QString m_admin;
    QVector <QString> m_participants;
    QListWidget *m_listWidget;


};
