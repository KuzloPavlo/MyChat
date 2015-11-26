#include "mainwindow.h"
#include <QApplication>
#include "serv_connect.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

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

    return a.exec();
}
