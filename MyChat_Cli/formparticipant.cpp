#include "formparticipant.h"
#include "ui_formparticipant.h"

FormParticipant::FormParticipant(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormParticipant)
{
    ui->setupUi(this);
    ui->deleteParticipant->setVisible(false);
    ui->Online->setVisible(false);
}

FormParticipant::~FormParticipant()
{
    delete ui;
}
