#include "mainwindow.h"
#include <QApplication>
#include "serv_connect.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow WINDOW;

    WINDOW.show();




    //---------------------------------------+
    //  Test connect with library            |
    //---------------------------------------+
    User us;
    us.Test ();
    Users uss;
    uss.Test ();
    Community comm;
    comm.Test ();
    Friends fr;
    fr.Test ();
    ParticipantsChat pr;
    pr.Test ();
    //---------------------------------------+
    //  Test connect with library            |
    //---------------------------------------+

    Serv_Connect connect;

    connect.Connect ();

    return app.exec();
}
