#ifndef FORMPARTICIPANT_H
#define FORMPARTICIPANT_H

#include <QWidget>

namespace Ui {
class FormParticipant;
}

class FormParticipant : public QWidget
{
    Q_OBJECT

public:
    explicit FormParticipant(QWidget *parent = 0);
    ~FormParticipant();

private:
    Ui::FormParticipant *ui;
};

#endif // FORMPARTICIPANT_H
