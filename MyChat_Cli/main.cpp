#include "mainwindow.h"
#include <QApplication>
#include "serv_connect.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Serv_Connect  connect ;
    MainWindow WINDOW(0, &connect);

    WINDOW.show();

   return app.exec();
}
