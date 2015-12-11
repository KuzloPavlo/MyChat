#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>

MainWindow::MainWindow(QWidget *parent, Serv_Connect *pSERVER) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_pSERVER (pSERVER)
{
    QPalette pall;
    // pall.setColor (this->backgroundRole (), QColor(100, 100, 100, 255));
    pall.setBrush (this->backgroundRole (), QBrush(QPixmap ("C:/MyChat/MyChat/pall.jpg")));
    this->setPalette (pall);

    ui->setupUi(this);
    //  m_pSERVER = pSERVER;
    this->setStyleSheet ("color: rgb(255, 120, 0)");
    // this->setWindowFlags ( Qt::FramelessWindowHint);


    ui->RegLoginBusyEdit->setVisible(false);
    ui->RegEnterNameLabel->setVisible(false);
    ui->RegEnterSurameLabel->setVisible(false);
    ui->RegEnterLoginLabel->setVisible(false);
    ui->RegEnterPasswordLabel->setVisible(false);

    ui->LogEnterLoginLabel->setVisible(false);
    ui->LogEnterPasswordLabel->setVisible(false);
    ui->LogWrongLoginLabel->setVisible(false);
    ui->LogWrongPasswordLabel->setVisible(false);


    connect(m_pSERVER, SIGNAL (signalRegServerResponseRegistered()), this,
            SLOT (slotRegServerResponseRegistered()));
    connect(m_pSERVER,SIGNAL (signalRegServerResponseLoginBusy()), this,
            SLOT (slotRegServerResponseLoginBusy()));

    connect(m_pSERVER, SIGNAL (signalAuthServerResponseAuthorized()), this,
            SLOT (slotAuthServerResponseAuthorized()));
    connect(m_pSERVER, SIGNAL (signalAuthServerResponseWrongLogin ()), this,
            SLOT (slotAuthServerResponseWrongLogin()));
    connect(m_pSERVER, SIGNAL (signalAuthServerResponseWrongPassword()), this,
            SLOT (slotAuthServerResponseWrongPassword()));
    connect(m_pSERVER, SIGNAL (signalAuthServerResponseIsEmty()), this,
            SLOT (slotAuthServerResponseIsEmty()));
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
    ui->LoginPage->setVisible(false);
    ui->RegistrationPage->setVisible(true);
    //ui->RegLoginBusyEdit->setVisible(false);
}




void MainWindow::on_RegBackBut_clicked()
{
    ui->RegistrationPage->setVisible(false);
    ui->LoginPage->setVisible(true);
}




void MainWindow::on_Close_clicked()
{
    close();
}




void MainWindow::on_Roll_up_clicked()
{
    //    свернуть
}




void MainWindow::on_RegRegistrationBut_clicked()
{
    if (!ui->RegNameEdit->text().isEmpty() &&           // if all the fields are full
            !ui->RegSurnameEdit->text().isEmpty() &&    //
            !ui->RegLoginEdit->text().isEmpty() &&      //
            !ui->RegPasswordEdit->text().isEmpty())      //
    {
        m_pSERVER->registration (&ui->RegNameEdit->text(),
                                 &ui->RegSurnameEdit->text(),
                                 &ui->RegLoginEdit->text(),
                                 &ui->RegPasswordEdit->text ());

        ui->WelLoginEdit->setText(ui->RegLoginEdit->text());
        ui->WelPasswordEdit->setText(ui->RegPasswordEdit->text());

        ui->LogLoginEdit->setText(ui->RegLoginEdit->text());
        ui->LogPasswordEdit->setText(ui->RegPasswordEdit->text());
    }

    if (ui->RegNameEdit->text().isEmpty())
    {
        ui->RegEnterNameLabel->setVisible(true);
    }


    if (ui->RegSurnameEdit->text().isEmpty())
    {

        ui->RegEnterSurameLabel->setVisible(true);
    }

    if (ui->RegLoginEdit->text().isEmpty())
    {

        ui->RegEnterLoginLabel->setVisible(true);
    }

    if (ui->RegPasswordEdit->text().isEmpty())
    {
        ui->RegEnterPasswordLabel->setVisible(true);
    }
}




void MainWindow::on_LogLoginBut_clicked()
{

    if (!ui->LogLoginEdit->text().isEmpty() && !ui->LogPasswordEdit->text().isEmpty())
    {
        m_pSERVER->authorization (&ui->LogLoginEdit->text(),
                                  &ui->LogPasswordEdit->text());
    }

    if (ui->LogLoginEdit->text().isEmpty())
    {
        ui->LogEnterLoginLabel->setVisible(true);
    }

    if (ui->LogPasswordEdit->text().isEmpty())
    {
        ui->LogEnterPasswordLabel->setVisible(true);
    }

}




void MainWindow::slotRegServerResponseRegistered()
{
    ui->RegistrationPage->setVisible (false);
    ui->WelcomePage->setVisible (true);
    ui->RegLoginBusyEdit->setVisible(false);
}




void MainWindow::slotRegServerResponseLoginBusy()
{
    // ui->RegistrationPage->setVisible(true);
    ui->RegLoginBusyEdit->setVisible(true);
}



void MainWindow::slotAuthServerResponseAuthorized()
{
    ui->LoginPage->setVisible(false);
    ui->MainPage->setVisible(true);

}


void MainWindow::slotAuthServerResponseWrongLogin()
{
    ui->LogWrongLoginLabel->setVisible(true);
}


void MainWindow::slotAuthServerResponseWrongPassword()
{
    ui->LogWrongPasswordLabel->setVisible(true);
}

void MainWindow::slotAuthServerResponseIsEmty()

{


}
