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

    ui->RemoveFriendBut->setVisible(false);
    ui->RemoveLabel->setVisible(false);
    ui->NotRmoveFriendBut->setVisible(false);


    connect(
                m_pSERVER,
                SIGNAL (signalRegistered(const QString& ,const QString&)),
                this,
                SLOT (slotRegistered(const QString&, const QString&))
                );

    connect(
                m_pSERVER,
                SIGNAL (signalLoginBusy()),
                this,
                SLOT (slotLoginBusy()));

    connect(
                m_pSERVER,
                SIGNAL (signalAuthorized(const QString&, const QString&, const QString&)),
                this,
                SLOT (slotAuthorized(const QString&, const QString&, const QString&)));

    connect(
                m_pSERVER,
                SIGNAL (signalWrongLogin ()),
                this,
                SLOT (slotWrongLogin()));

    connect(
                m_pSERVER,
                SIGNAL (signalWrongPassword()),
                this,
                SLOT (slotWrongPassword()));

    connect(
                m_pSERVER,
                SIGNAL (signalIsEmty()),
                this,
                SLOT (slotIsEmty()));



    connect(
                m_pSERVER,
                SIGNAL (signalFoundFriend(QVector<User>)),
                this,
                SLOT (slotFoundFriend(QVector<User>)));


    connect(
                m_pSERVER,
                SIGNAL(signalNewFriend(const User&)),
                this,
                SLOT(slotNewFriend(const User&)));

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
    if (!ui->RegNameEdit->text().isEmpty() &&             // if all the fields are full
            !ui->RegSurnameEdit->text().isEmpty() &&      //
            !ui->RegLoginEdit->text().isEmpty() &&        //
            !ui->RegPasswordEdit->text().isEmpty())       //
    {
        m_pSERVER->registerUser (
                    ui->RegNameEdit->text(),
                    ui->RegSurnameEdit->text(),
                    ui->RegLoginEdit->text(),
                    ui->RegPasswordEdit->text());
    }

    ui->RegEnterNameLabel->setVisible(ui->RegNameEdit->text().isEmpty());

    ui->RegEnterSurameLabel->setVisible(ui->RegSurnameEdit->text().isEmpty());

    ui->RegEnterLoginLabel->setVisible(ui->RegLoginEdit->text().isEmpty());

    ui->RegEnterPasswordLabel->setVisible(ui->RegPasswordEdit->text().isEmpty());

    // Добавить обработку отсутствия соединение с сервером
}




void MainWindow::on_LogLoginBut_clicked()
{
    if (!ui->LogLoginEdit->text().isEmpty() && !ui->LogPasswordEdit->text().isEmpty())
    {
        m_pSERVER->authorizationUser(ui->LogLoginEdit->text(),
                                     ui->LogPasswordEdit->text());
    }

    ui->LogEnterLoginLabel->setVisible(ui->LogLoginEdit->text().isEmpty());

    ui->LogEnterPasswordLabel->setVisible(ui->LogPasswordEdit->text().isEmpty());

    // Добавить обработку отсутствия соединение с сервером
}




void MainWindow::slotRegistered(const QString &login, const QString &password)
{
    ui->RegLoginBusyEdit->setVisible(false);    // if showed
    ui->RegistrationPage->setVisible (false);
    ui->WelcomePage->setVisible (true);

    ui->WelLoginEdit->setText(login);         // copy Data user
    ui->WelPasswordEdit->setText(password);   // copy Data user

    ui->LogLoginEdit->setText(login);         // copy Data user
    ui->LogPasswordEdit->setText(password);   // copy Data user
}




void MainWindow::slotLoginBusy()
{
    ui->RegLoginBusyEdit->setVisible(true);
}



void MainWindow::slotAuthorized(const QString &name,
                                const QString &surname,
                                const QString &login)
{
    ui->LoginPage->setVisible(false);
    ui->MainPage->setVisible(true);

    ui->UserNameLabel->setText(name);
    ui->UserSurnameLabel->setText(surname);
    ui->UserLoginLabel->setText(login);
}


void MainWindow::slotWrongLogin()
{
    ui->LogWrongLoginLabel->setVisible(true);
}


void MainWindow::slotWrongPassword()
{
    ui->LogWrongPasswordLabel->setVisible(true);
}




void MainWindow::slotIsEmty()
{

}




void MainWindow::slotFoundFriend(QVector<User> potentialFriends)
{
    this->m_potentialFriends = potentialFriends;

    for (int i = 0; i < potentialFriends.size(); i++)
    {
        ui->MainListWidget->addItem(potentialFriends[i].getLogin());
    }
}





void MainWindow::slotNewFriend(const User &newFriend)
{
    m_friends.push_back(newFriend);

    ui->MainSearchFriendPage->setVisible(false);
}




void MainWindow::on_MainConnBut_clicked()
{
    ui->MainChatsPage->setVisible(false);
    ui->MainSearchFriendPage->setVisible(false);
    ui->MainUserInfo->setVisible(false);
  //  ui->MainFriendInfo->setVisible(false);
    ui->MainConnPage->setVisible(true);

    ui->ConntactsListWidget->clear();

    for (int i = 0; i < m_friends.size(); i++)
    {
        ui->ConntactsListWidget->addItem(m_friends[i].getLogin());
    }
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
}



void MainWindow::on_MainSearchBut_clicked()
{
    m_pSERVER->findFriend(ui->MainSearchEdit->text());
    ui->MainListWidget->clear();
}




void MainWindow::on_MainListWidget_currentTextChanged(const QString &currentText)
{
    for (int i = 0; i < m_friends.size(); i++)
    {
        if (currentText ==  m_friends[i].getLogin())
        {
            emit on_ConntactsListWidget_currentTextChanged(currentText);
            return;
        }
    }

    if (currentText == ui->UserLoginLabel->text())
    {
        emit on_MainUserBut_clicked();
        return;
    }

  //  ui->MainFriendInfo->setVisible(false);
    ui->MainUserInfo->setVisible(false);
    ui->MainSearchFriendPage->setVisible(true);

    for(int i = 0; i < m_potentialFriends.size(); i++)
    {
        if (currentText == m_potentialFriends[i].getLogin())
        {
            ui->SearchFriendNameLabel->setText(m_potentialFriends[i].getName());
            ui->SearchFriendSurnameLabel->setText(m_potentialFriends[i].getSurname());
            ui->SearchFriendLoginLabel->setText(m_potentialFriends[i].getLogin());
        }
    }
}




void MainWindow::on_MainAddFrinedBut_clicked()
{
    m_pSERVER->addFriend(ui->SearchFriendLoginLabel->text());
}



void MainWindow::on_MainUserBut_clicked()
{
    ui->MainSearchFriendPage->setVisible(false);
    ui->MainFriendInfo->setVisible(false);
    ui->MainUserInfo->setVisible(true);
}




void MainWindow::on_ConntactsListWidget_currentTextChanged(const QString &currentText)
{
    ui->MainUserInfo->setVisible(false);
    ui->MainSearchFriendPage->setVisible(false);
    ui->MainFriendInfo->setVisible(true);
    ui->DeleteConBut->setVisible(true);

    for (int i = 0; i < m_friends.size(); i++)
    {
        if (currentText == m_friends[i].getLogin())
        {
            ui->FriendNameLabel->setText(m_friends[i].getName());
            ui->FriendSurnameLabel->setText(m_friends[i].getSurname());
            ui->FriendLoginLabel->setText(m_friends[i].getLogin());
            return;
        }
    }
}


void MainWindow::on_DeleteConBut_clicked()
{
    ui->RemoveFriendBut->setVisible(true);
    ui->RemoveLabel->setVisible(true);
    ui->NotRmoveFriendBut->setVisible(true);

    ui->DeleteConBut->setVisible(false);
}

void MainWindow::on_NotRmoveFriendBut_clicked()
{
    ui->RemoveFriendBut->setVisible(false);
    ui->RemoveLabel->setVisible(false);
    ui->NotRmoveFriendBut->setVisible(false);

    ui->DeleteConBut->setVisible(true);
}

void MainWindow::on_RemoveFriendBut_clicked()
{
   m_pSERVER->removeFriend(ui->FriendLoginLabel->text());

    ui->RemoveFriendBut->setVisible(false);
    ui->RemoveLabel->setVisible(false);
    ui->NotRmoveFriendBut->setVisible(false);

    ui->DeleteConBut->setVisible(true);

    ui->MainFriendInfo->setVisible(false);
}
