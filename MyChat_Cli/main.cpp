#include "mainwindow.h"
#include <QApplication>
#include "Client.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Client  connect ;
    MainWindow WINDOW(0, &connect);

    WINDOW.show();

   return app.exec();
}
