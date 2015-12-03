#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent, Serv_Connect *pSERVER) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{


    QPalette pall;
   // pall.setColor (this->backgroundRole (), QColor(100, 100, 100, 255));
    pall.setBrush (this->backgroundRole (), QBrush(QPixmap ("C:/MyChat/MyChat/pall.jpg")));
    this->setPalette (pall);

   // this->setStyleSheet ("color: rgb(50, 0, 70)");


    ui->setupUi(this);

    SERVER = pSERVER;


   this->setStyleSheet ("color: rgb(255, 120, 0)");

  // this->setWindowFlags ( Qt::FramelessWindowHint);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_WelOkBut_clicked()
{
    ui->WelcomePage->setVisible (false);
    ui->LoginPage->setVisible (true);
}


void MainWindow::on_LogRegistrationBut_clicked()
{
    ui->LoginPage->setVisible (false);
    ui->RegistrationPage->setVisible (true);
}

void MainWindow::on_RegBackBut_clicked()
{
    ui->RegistrationPage->setVisible (false);
    ui->LoginPage->setVisible (true);


}

void MainWindow::on_Close_clicked()
{
  close ();
}

void MainWindow::on_Roll_up_clicked()
{


//    this->hide ();
}

void MainWindow::on_RegRegistrationBut_clicked()
{
     if (false) {
        // если не вся информация введенна придумать что сделать
        //
        //
    }

     QByteArray RegBlock;

     QDataStream out (&RegBlock, QIODevice::WriteOnly);
     out.setVersion (QDataStream::Qt_5_5);
     out << quint16 (0)
         << quint8 ('R')
         << ui->RegNameEdit->text ()
         << ui->RegSurnameEdit->text ()
         << ui->RegLoginEdit->text ()
         << ui->RegPasswordEdit->text ();

     out.device ()->seek (0);
     out <<quint16 (RegBlock.size ()- sizeof (quint16));

   //  SERVER->socket->write (RegBlock);//

      qDebug () << ui->RegNameEdit->text ();
      qDebug () << ui->RegSurnameEdit->text ();
      qDebug () << ui->RegLoginEdit->text ();
      qDebug () << ui->RegPasswordEdit->text ();

     SERVER->Registration (&RegBlock);
}
