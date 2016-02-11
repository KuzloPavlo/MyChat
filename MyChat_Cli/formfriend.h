#pragma once
#include <QWidget>

namespace Ui {
class FormFriend;
}

class FormFriend : public QWidget
{
    Q_OBJECT

public:
    explicit FormFriend(
            const QString &name,
            const QString &surname,
            const QString &login,
            QWidget *parent = 0);

    ~FormFriend();

protected:
    Ui::FormFriend *ui;
    bool m_online;
    QString m_login;
};
