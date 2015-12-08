#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent, Serv_Connect *pSERVER) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), SERVER (pSERVER)
{
    QPalette pall;
   // pall.setColor (this->backgroundRole (), QColor(100, 100, 100, 255));
    pall.setBrush (this->backgroundRole (), QBrush(QPixmap ("C:/MyChat/MyChat/pall.jpg")));
    this->setPalette (pall);

    ui->setupUi(this);

  //  SERVER = pSERVER;

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
//    свернуть
}

void MainWindow::on_RegRegistrationBut_clicked()
{
     if (false)
     {
        // если не вся информация введенна - придумать что сделать
     }

     SERVER->Registration (&ui->RegNameEdit->text(),
                           &ui->RegSurnameEdit->text(),
                           &ui->RegLoginEdit->text(),
                           &ui->RegPasswordEdit->text ());
}

void MainWindow::on_LogLoginBut_clicked()
{
    if (false)
    {
       // если не вся информация введенна - придумать что сделать
    }



    SERVER->Authorization (&ui->LogLoginEdit->text(),
                           &ui->LogPasswordEdit->text());
}

//---------------------------------------------
// ServerRespons
//--------------------------------------------

void MainWindow::RegServerResponsYes ( QString *login, QString *password) // переделай показ страниц при помощи указателей на узел стека
{
    ui->RegistrationPage->setVisible (false);
    ui->WelcomePage ->setVisible (true);
    ui->WelLoginEdit->setText (*login);
    ui->WelPasswordEdit->setText (*password);

    qDebug() << *login;
    qDebug() << *password;
}

void MainWindow::RegServerResponsNo (char *ch) // сделай здесь все красиво!!!!!!!!!!!!!!!!!!!!!!
{
    switch (*ch) {
    case 'L': qDebug()<< "Login zanjat";

        break;
    default: qDebug()<< "Ne zaregistrirovano po drugoi prichine";
        break;
    }
}
//--------------------------------------------
