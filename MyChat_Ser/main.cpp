#include <QCoreApplication>
#include "server.h"
#include "user.h"
#include "usersarray.h"
#include <QString>
#include <QDebug>

#include <qapplication.h>
#include <QApplication>
#include <QWidget>
#include <QDialog>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Server server;

    return a.exec();
}
