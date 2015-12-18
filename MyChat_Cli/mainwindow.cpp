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

    ui->MainCloseSearchButt->setVisible(false);
    ui->MainSearchBut->setVisible(false);

    ui->MainSearchFriendPage->setVisible(false);
    ui->MainInfoLabel->setVisible(false);
    ui->MainAddFrinedBut->setVisible(false);


    connect(
                m_pSERVER,
                SIGNAL (signalRegRegistered(QString*,QString*,QString*,QString*,QString*)),
                this,
                SLOT (slotRegRegistered(QString*,QString*,QString*,QString*,QString*))
                );

    connect(
                m_pSERVER,
                SIGNAL (signalRegLoginBusy()),
                this,
                SLOT (slotRegLoginBusy()));

    connect(
                m_pSERVER,
                SIGNAL (signalAuthAuthorized(QString*,QString*,QString*,QString*,QString*)),
                this,
                SLOT (slotAuthAuthorized(QString*,QString*,QString*,QString*,QString*)));

    connect(
                m_pSERVER,
                SIGNAL (signalAuthWrongLogin ()),
                this,
                SLOT (slotAuthWrongLogin()));

    connect(
                m_pSERVER,
                SIGNAL (signalAuthWrongPassword()),
                this,
                SLOT (slotAuthWrongPassword()));

    connect(
                m_pSERVER,
                SIGNAL (signalAuthIsEmty()),
                this,
                SLOT (slotAuthIsEmty()));

    connect(
                m_pSERVER,
                SIGNAL (signalSearchFriendResponsNotFound()),
                this,
                SLOT (slotSearchFriendResponsNotFound()));

    connect(
                m_pSERVER,
                SIGNAL (signalSearchFriendResponsFound(QVector<User>)),
                this,
                SLOT (slotSearchFriendResponsFound(QVector<User>)));

    connect(
                m_pSERVER,
                SIGNAL (signalSearchFriendResponsFound(QVector<User>)),
                m_pSERVER,
                SLOT (slotSearchFriendResponsFound(QVector<User>)));
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

    ui->RegEnterNameLabel->setVisible(false);                    // What's the difference,
    ui->RegEnterSurameLabel->setVisible(false);                  // check four times the visibility
    ui->RegEnterLoginLabel->setVisible(false);                   // or made invisible!!!
    ui->RegEnterPasswordLabel->setVisible(false);                // !I think it is better to make the invisible

    if (!ui->RegNameEdit->text().isEmpty() &&             // if all the fields are full
            !ui->RegSurnameEdit->text().isEmpty() &&      //
            !ui->RegLoginEdit->text().isEmpty() &&        //
            !ui->RegPasswordEdit->text().isEmpty())       //
    {
        m_pSERVER->registration (
                    &ui->RegNameEdit->text(),
                    &ui->RegSurnameEdit->text(),
                    &ui->RegLoginEdit->text(),
                    &ui->RegPasswordEdit->text());

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

    // Добавить обработку отсутствия соединение с сервером
}




void MainWindow::on_LogLoginBut_clicked()
{

    ui->LogEnterLoginLabel->setVisible(false);
    ui->LogEnterPasswordLabel->setVisible(false);

    if (!ui->LogLoginEdit->text().isEmpty() && !ui->LogPasswordEdit->text().isEmpty())
    {
        m_pSERVER->authorization(&ui->LogLoginEdit->text(),
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

    // Добавить обработку отсутствия соединение с сервером
}




void MainWindow::slotRegRegistered(QString *pname,
                                   QString *psurname,
                                   QString *plogin,
                                   QString *ppassword,
                                   QString *pipAddress)
{
    ui->RegLoginBusyEdit->setVisible(false);    // if showed
    ui->RegistrationPage->setVisible (false);
    ui->WelcomePage->setVisible (true);

    ui->WelLoginEdit->setText(*plogin);         // copy Data user
    ui->WelPasswordEdit->setText(*ppassword);   // copy Data user

    ui->LogLoginEdit->setText(*plogin);         // copy Data user
    ui->LogPasswordEdit->setText(*ppassword);   // copy Data user
}




void MainWindow::slotRegLoginBusy()
{
    ui->RegLoginBusyEdit->setVisible(true);
}



void MainWindow::slotAuthAuthorized( QString *pname,
                                     QString *psurname,
                                     QString *plogin,
                                     QString *ppassword,
                                     QString *pipAddress)
{

    ui->LoginPage->setVisible(false);
    ui->MainPage->setVisible(true);

    ui->UserNameLabel->setText(*pname);
    ui->UserSurnameLabel->setText(*psurname);
    ui->UserLoginLabel->setText(*plogin);

}


void MainWindow::slotAuthWrongLogin()
{
    ui->LogWrongLoginLabel->setVisible(true);
}


void MainWindow::slotAuthWrongPassword()
{
    ui->LogWrongPasswordLabel->setVisible(true);
}

void MainWindow::slotAuthIsEmty()

{


}


void MainWindow::slotSearchFriendResponsNotFound()

{

    // добавь что ничего не найдено

}



void MainWindow::slotSearchFriendResponsFound(QVector<User> potentialFriends)
{
    //  m_potentialFriends = potentialFriends;  // ВОТ ТАК СДЕЛАЙ!!!
    ui->MainListWidget->clear();

    for (int i = 0; i < potentialFriends.size(); i++)
    {

        ui->MainListWidget->addItem(potentialFriends[i].showLogin());

    }

}


void MainWindow::on_MainConnBut_clicked()
{
    ui->MainChatsPage->setVisible(false);
    ui->MainConnPage->setVisible(true);


}



void MainWindow::on_MainChatsBut_clicked()
{
    ui->MainConnPage->setVisible(false);
    ui->MainChatsPage->setVisible(true);
}



void MainWindow::on_MainCloseSearchButt_clicked()
{
    ui->MainSearchEdit->clear();
    ui->MainListWidget->clear();
    ui->MainInfoLabel->setVisible(false);
    ui->MainAddFrinedBut->setVisible(false);
    ui->MainSearchFriendPage->setVisible(false);
    ui->MainSearchFriendsPage->setVisible(false);
    ui->MainSearchBut->setVisible(false);
    ui->MainSearchBut->setDefault(false);
    ui->MainMainPage->setVisible(true);
    ui->MainCloseSearchButt->setVisible(false);

}



void MainWindow::on_MainSearchEdit_textChanged(const QString &arg1)
{

    ui->MainCloseSearchButt->setVisible(true);
    ui->MainMainPage->setVisible(false);
    ui->MainSearchFriendsPage->setVisible(true);
    ui->MainSearchBut->setVisible(!arg1.isEmpty());
    // ui->MainSearchBut->setDefault(true);    // завязать на Ентер

}



void MainWindow::on_MainSearchBut_clicked()
{/*
    ui->MainPage->setVisible(false);
    ui->LoginPage->setVisible(true);*/

    m_pSERVER->searchFriend(&ui->MainSearchEdit->text());



}




void MainWindow::on_MainListWidget_currentTextChanged(const QString &currentText)
{
    ui->MainUserInfo->setVisible(false);
    ui->MainSearchFriendPage->setVisible(true);
    ui->MainInfoLabel->setVisible(true);
    ui->MainAddFrinedBut->setVisible(true);

    for(int i = 0; i < m_pSERVER->m_potentialFriends.size(); i++)
    {

        if (currentText == m_pSERVER->m_potentialFriends[i].showLogin())
        {
            ui->SearchFriendNameLabel->setText(m_pSERVER->m_potentialFriends[i].showName());
            ui->SearchFriendSurnameLabel->setText(m_pSERVER->m_potentialFriends[i].showSurname());
            ui->SearchFriendLoginLabel->setText(m_pSERVER->m_potentialFriends[i].showLogin());
        }
    }
}




void MainWindow::on_MainAddFrinedBut_clicked()
{
    m_pSERVER->addFriend(&ui->SearchFriendLoginLabel->text());
}



void MainWindow::on_MainUserBut_clicked()
{
    ui->MainSearchFriendPage->setVisible(false);
    ui->MainUserInfo->setVisible(true);
}


void MainWindow::on_ConntactsListWidget_currentTextChanged(const QString &currentText)
{

}
