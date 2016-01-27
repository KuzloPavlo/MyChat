#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QTextBrowser>
#include <QSpacerItem>
#include <QString>

MainWindow::MainWindow(QWidget *parent, Client *pSERVER) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_pSERVER (pSERVER)
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //--------------------------------------------------------------+
    // section for experiments                                      |
    //--------------------------------------------------------------+

    Message mess;

    mess.mDataTime = QDateTime::currentDateTime();
    mess.mMessageText = "hhdfgjajffghahfg"
                        "ahgjhahfghajfdg;hafdgh"
                        "ahfgghjahdfjgshfdjgh hfgjhs dfghsdfggsfhf gsdfhfg sf"
                        "shdgfk shgfjkhsjfhg;sh"
                        "rtyeoyey5oypeoyperoty"
                        "etpyeprtyieroytioetyoie er yyt et yty"
                        "typoieryt ieriy eroity erty "
                        "etr yeproiy terpiy erpoyt eryieri ypoer y eroyoper yreity "
                        "ptryi eriyt erytier yti eriypieoryio eryie ry e ryeoyt eriy eryi tery[i eryeir yeyery iyier iyt"
                        "tpryi eryti eryeriytp[oeriytopery ipoeryeporyieryi ep ye ryopertyie y"
                        "fg jsffgh s";
    mess.mSender = "PAVLO";


    emit slotAddNewMessage(ui->tableWidget, new IncomingMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));
    emit slotAddNewMessage(ui->tableWidget, new FormMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));
    emit slotAddNewMessage(ui->tableWidget, new OutgoingMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));
    emit slotAddNewMessage(ui->tableWidget, new IncomingMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));
    emit slotAddNewMessage(ui->tableWidget, new FormMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));
    emit slotAddNewMessage(ui->tableWidget, new OutgoingMessage(mess.mSender, mess.mMessageText, mess.mDataTime.time().toString(),ui->tableWidget));

    //--------------------------------------------------------------+
    // section for experiments                                      |
    //--------------------------------------------------------------+


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

    ui->MainPotentialFriendPage->setVisible(false);

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

    connect(
                m_pSERVER,
                SIGNAL(signalIncomingMessage(const Message&)),
                this,
                SLOT(slotIncomingMessage(const Message&))
                );

}




MainWindow::~MainWindow()
{
    delete ui;
}




void MainWindow::on_WelOkBut_clicked()
{
    emit ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_LogRegistrationBut_clicked()
{
    emit ui->stackedWidget->setCurrentIndex(1);
}




void MainWindow::on_RegBackBut_clicked()
{
    emit ui->stackedWidget->setCurrentIndex(0);
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

    ui->stackedWidget->setCurrentIndex(2);

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
    ui->stackedWidget->setCurrentIndex(3);

    ui->MainStackedWidgetLeft->setCurrentIndex(0);
    ui->MainStackedWidgetConntact->setCurrentIndex(0);

    ui->UserNameLabel->setText(name);
    ui->UserSurnameLabel->setText(surname);
    ui->UserLoginLabel->setText(login);

    ui->MainStackedWidgetInfo->setCurrentIndex(0);


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



void MainWindow::slotResizeTableWidgetRows(QTableWidget *tableWidget)
{

}



void MainWindow::slotAddNewMessage(QTableWidget *tableWidget, QWidget *message)
{
    emit tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setCellWidget(tableWidget->rowCount()-1, 0, message);
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

    User temp = newFriend;

    emit on_ConntactsListWidget_currentTextChanged(temp.getLogin());
}



void MainWindow::slotIncomingMessage(const Message &incomingMessage)
{
    if (ui->FriendLoginLabel->text() == incomingMessage.mSender)
    {
        Message temp = incomingMessage;
        //emit slotAddNewMessage(ui->tableWidget, new IncomingMessage(ui->tableWidget,&temp));
    }
}



void MainWindow::on_MainConnBut_clicked()
{
    ui->ConntactsListWidget->clear();

    for (int i = 0; i < m_friends.size(); i++)
    {
        ui->ConntactsListWidget->addItem(m_friends[i].getLogin());
    }

    ui->MainStackedWidgetConntact->setCurrentIndex(0);
}



void MainWindow::on_MainChatsBut_clicked()
{
    ui->MainStackedWidgetConntact->setCurrentIndex(1);
}



void MainWindow::on_MainCloseSearchButt_clicked()
{
    ui->MainSearchEdit->clear();
    ui->MainListWidget->clear();
    ui->MainSearchBut->setVisible(false);
    ui->MainStackedWidgetLeft->setCurrentIndex(0);
    ui->MainCloseSearchButt->setVisible(false);
}




void MainWindow::on_MainSearchEdit_textChanged(const QString &arg1)
{
    ui->MainCloseSearchButt->setVisible(true);
    ui->MainStackedWidgetLeft->setCurrentIndex(1);
    ui->MainSearchBut->setVisible(!arg1.isEmpty());
}



void MainWindow::on_MainSearchBut_clicked()
{
    ui->MainListWidget->clear();
    m_pSERVER->findFriend(ui->MainSearchEdit->text());
}




void MainWindow::on_MainListWidget_currentTextChanged(const QString &currentText)
{
    for (int i = 0; i < m_friends.size(); i++)
    {
        if (currentText == m_friends[i].getLogin())
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

    for(int i = 0; i < m_potentialFriends.size(); i++)
    {
        if (currentText == m_potentialFriends[i].getLogin())
        {
            ui->SearchFriendNameLabel->setText(m_potentialFriends[i].getName());
            ui->SearchFriendSurnameLabel->setText(m_potentialFriends[i].getSurname());
            ui->SearchFriendLoginLabel->setText(m_potentialFriends[i].getLogin());
        }
    }
    ui->MainStackedWidgetInfo->setCurrentIndex(2);
}




void MainWindow::on_MainAddFrinedBut_clicked()
{
    m_pSERVER->addFriend(ui->SearchFriendLoginLabel->text());
}



void MainWindow::on_MainUserBut_clicked()
{
    ui->MainStackedWidgetInfo->setCurrentIndex(0);
}




void MainWindow::on_ConntactsListWidget_currentTextChanged(const QString &currentText)
{
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
    ui->DeleteConBut->setVisible(true);  // WHOT THIS??
    ui->MainStackedWidgetInfo->setCurrentIndex(1);

    // Тут потрібно дописати підгрузку та відображення попередньої переписки
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
}

void MainWindow::on_SendMessageBut_clicked()
{

    if (!ui->messageEdit->toPlainText().isEmpty())
    {
        Message newMessage;
        newMessage.mSender = ui->UserLoginLabel->text();
        newMessage.mRecipient = ui->FriendLoginLabel->text();
        newMessage.mMessageText =   ui->messageEdit->toPlainText();
        newMessage.mDataTime = QDateTime::currentDateTime();

        //        emit slotAddNewMessage(
        //                    ui->tableWidget,
        //                    //new OutgoingMessage(ui->tableWidget, &newMessage));

        m_pSERVER->sendMessage(
                    newMessage.mSender,
                    newMessage.mRecipient,
                    newMessage.mMessageText,
                    newMessage.mDataTime
                    );

        ui->messageEdit->clear();
    }
}
