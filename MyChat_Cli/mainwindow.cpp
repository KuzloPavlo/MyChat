#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QPalette pall;
   // pall.setColor (this->backgroundRole (), QColor(100, 100, 100, 255));
    pall.setBrush (this->backgroundRole (), QBrush(QPixmap ("C:/MyChat/MyChat/pall.jpg")));
    this->setPalette (pall);





   // this->setStyleSheet ("color: rgb(50, 0, 70)");


    ui->setupUi(this);

this->setStyleSheet ("color: rgb(255, 120, 0)");
//    this->








   // this->setWindowFlags (Qt::Window | Qt::WindowMinimizeButtonHint  | Qt::Tool);
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
