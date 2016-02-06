#include "serverdebug.h"
#include "ui_serverdebug.h"

ServerDebug::ServerDebug() :

    ui(new Ui::ServerDebug)
{
    ui->setupUi(this);
}

ServerDebug::~ServerDebug()
{
    delete ui;
}


void ServerDebug::slotdebug(const QString &str)
{
    ui->listWidget->addItem(str);
}
