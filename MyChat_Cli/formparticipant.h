#pragma once
#include <formfriend.h>

class FormParticipant : public FormFriend
{

    Q_OBJECT

public:
    FormParticipant(
            const QString &name,
            const QString &surname,
            const QString &login,
            QWidget *parent = 0);

    FormParticipant(const QString &login,
                    QWidget *parent = 0);
};
