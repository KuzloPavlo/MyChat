#pragma once
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QTextBrowser>
#include <QSpacerItem>
#include <QString>


MainWindow::MainWindow(QWidget *parent, Client *pSERVER) :
    QMainWindow(parent),
    ui(new Ui::MainWindow), m_pSERVER (pSERVER),addParticipantDialog (new AddParticipantDialog( this))
{
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
    ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //--------------------------------------------------------------+
    // section for experiments                                      |
    //--------------------------------------------------------------+
    ui->tableParticipiantsChat->setCellWidget(0,0, new FormParticipant(ui->tableParticipiantsChat));
    //    ui->tableParticipiantsChat->setCellWidget(0,1, new FormParticipant(ui->tableParticipiantsChat));
    //    ui->tableParticipiantsChat->setCellWidget(0,2, new FormParticipant(ui->tableParticipiantsChat));
    //    ui->tableParticipiantsChat->setCellWidget(1,0, new FormParticipant(ui->tableParticipiantsChat));
    //    ui->tableParticipiantsChat->setCellWidget(1,1, new FormParticipant(ui->tableParticipiantsChat));
    //    ui->tableParticipiantsChat->setCellWidget(1,2, new FormParticipant(ui->tableParticipiantsChat));

    ui->tableParticipiantsChat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableParticipiantsChat->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int ID = 77;
    QString adm = "PAVEL";
    QString chtname = "Chat Name 77";
    QString us1 = "name1";
    QString us2 = "name2";
    QString us3 = "name3";
    QVector <QString> part;

    part.push_back(us1);
    part.push_back(us2);
    part.push_back(us3);
    part.push_back(adm);


    // ui->ChatListWidget->setCellWidget(0,0 ,new FormChat(ID,chtname,adm, part, ui->ChatListWidget));

    for(int i = 0; i < 20; i++)
    {
        FormChat *newchat =  new FormChat(ID,chtname,adm, part, ui->ChatListWidget);
    }
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
                SIGNAL (signalFoundFriend(QString)),
                this,
                SLOT (slotFoundFriend(QString)));


    connect(
                m_pSERVER,
                SIGNAL(signalNewFriend()),
                this,
                SLOT(slotNewFriend()));

    connect(
                m_pSERVER,
                SIGNAL(signalIncomingMessage(const QString &,
                                             const QString &,
                                             const QString &)),
                this,
                SLOT(slotIncomingMessage(const QString &,
                                         const QString &,
                                         const QString &))
                );


    connect(
                m_pSERVER,
                SIGNAL(signalEarlierReceivedMessage(const QString &,const QString &,const QString &)),
                this,
                SLOT(slotEarlierReceivedMessage(const QString &,const QString &,const QString &))
                );

    connect(
                m_pSERVER,
                SIGNAL(signalEarlierSendMessage(const QString &,const QString &,const QString &)),
                this,
                SLOT(slotEarlierSendMessage(const QString &,const QString &,const QString &))
                );

    connect(
                this,
                SIGNAL(signalShowListFriends()),
                m_pSERVER,
                SLOT(slotShowListFriends())
                );

    connect(
                m_pSERVER,
                SIGNAL(signalAddFriendToList(QString)),
                this,
                SLOT(slotAddFriendToList(QString))
                );

    connect(
                this,
                SIGNAL(signalShowListChats()),
                m_pSERVER,
                SLOT(slotShowListChats())
                );

    connect(
                m_pSERVER,
                SIGNAL(signalAddChatToList(int)),
                this,
                SLOT(slotAddChatToList(int))
                );

    connect(
                this,
                SIGNAL(signalShowFriend(QString)),
                m_pSERVER,
                SLOT(slotShowFriend(QString))
                );


    connect(
                m_pSERVER,
                SIGNAL(signalShowFriend(QString, QString, QString)),
                this,
                SLOT(slotShowFriend(QString, QString, QString))
                );

    connect(
                this,
                SIGNAL(signalShowPotentialFriend(QString)),
                m_pSERVER,
                SLOT(slotShowPotentialFriend(QString))
                );

    connect(
                m_pSERVER,
                SIGNAL(signalShowPotentialFriend(QString,QString,QString)),
                this,
                SLOT(slotShowPotentialFriend(QString,QString,QString))
                );

    connect(
                addParticipantDialog,
                SIGNAL(signalFindParticipants(const QString &)),
                m_pSERVER,
                SLOT(slotFindParticipants(const QString &))
                );

    connect(
                m_pSERVER,
                SIGNAL(signalShowFriend(const QString &)),
                addParticipantDialog,
                SLOT(slotFindParticipant(const QString &))
                );

    connect(
                addParticipantDialog,
                SIGNAL(signalCreateNewCaht(QVector<QString>)),
                m_pSERVER,
                SLOT(slotCrateNewGroupChat(QVector<QString>))

                );

    connect(
                m_pSERVER,
                SIGNAL(signalNewGroupChat()),
                this,
                SLOT( slotNewGroupChat())
                );



















    connect(
                m_pSERVER,
                SIGNAL(f(const QString &)),
                this,
                SLOT(slotclientdebug(const QString &))
                );



}

//-------------------------------------
// function for debug
//---------------------------------

void MainWindow::f(const QString &str)
{
    ui->forWindDebug->addItem(str);
}

void MainWindow::slotclientdebug(const QString &str)
{
    ui->forClientDebug->addItem(str);
}

//-----------------------------------

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

    ui->MainStackedWidgetInfo->setCurrentIndex(0);

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



void MainWindow::slotResizeTableWidgetRows(QTableWidget *tableWidget)
{

}



void MainWindow::addNewMessage(QTableWidget *tableWidget, QWidget *message)
{
    emit tableWidget->insertRow(tableWidget->rowCount());
    tableWidget->setCellWidget(tableWidget->rowCount()-1, 0, message);
}



void MainWindow::slotFoundFriend(QString login)
{
    //this->m_potentialFriends = potentialFriends;

    //    for (int i = 0; i < potentialFriends.size(); i++)
    //    {
    ui->MainListWidget->addItem(login);
    //}
}



void MainWindow::slotNewFriend()
{
    ui->MainStackedWidgetInfo->setCurrentIndex(4);
    ui->newGroupChatLabel->setVisible(false);
    ui->newFriendLabel->setVisible(true);
}


void MainWindow::slotNewGroupChat()
{
    ui->MainStackedWidgetInfo->setCurrentIndex(4);
    ui->newGroupChatLabel->setVisible(true);
    ui->newFriendLabel->setVisible(false);
}

void MainWindow::slotIncomingMessage(const QString &sender,
                                     const QString &message,
                                     const QString &time)
{
    if (ui->FriendLoginLabel->text() == sender)
    {
        addNewMessage(ui->tableWidget, new IncomingMessage(sender,message,time,ui->tableWidget));
    }
}


void MainWindow::slotEarlierReceivedMessage(const QString &sender, const QString &message, const QString &time)
{
    if (ui->FriendLoginLabel->text() == sender)
    {
        addNewMessage(ui->tableWidget, new IncomingMessage(sender,message,time,ui->tableWidget));
    }
    qDebug()<< "perepisKA";
}


void MainWindow::slotEarlierSendMessage(const QString &recipient, const QString &message, const QString &time)
{
    if (ui->FriendLoginLabel->text() == recipient)
    {
        addNewMessage(ui->tableWidget, new OutgoingMessage (recipient,message,time,ui->tableWidget));
    }
    qDebug()<< "perepisKA";
}


void MainWindow::on_MainConnBut_clicked()
{
    ui->ConntactsListWidget->clear();

    emit signalShowListFriends();

    //    for (int i = 0; i < m_friends.size(); i++)
    //    {
    //        ui->ConntactsListWidget->addItem(m_friends[i].getLogin());
    //    }

    ui->MainStackedWidgetConntact->setCurrentIndex(0);
    ui->MainStackedWidgetInfo->setCurrentIndex(3);
    emit f("MainWindow::on_MainConnBut_clicked()");
}



void MainWindow::on_MainChatsBut_clicked()
{
    ui->ChatListWidget->clear();

    emit signalShowListChats();

    ui->MainStackedWidgetConntact->setCurrentIndex(1);
    ui->MainStackedWidgetInfo->setCurrentIndex(5);
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



    //    for (int i = 0; i < m_friends.size(); i++)
    //    {
    //        if (currentText == m_friends[i].getLogin())
    //        {
    //            emit on_ConntactsListWidget_currentTextChanged(currentText);
    //            return;
    //        }
    //    }

    if (currentText == ui->UserLoginLabel->text())
    {
        emit on_MainUserBut_clicked();
        return;
    }

    emit signalShowPotentialFriend(currentText);

    //    for(int i = 0; i < m_potentialFriends.size(); i++)
    //    {
    //        if (currentText == m_potentialFriends[i].getLogin())
    //        {
    //            ui->SearchFriendNameLabel->setText(m_potentialFriends[i].getName());
    //            ui->SearchFriendSurnameLabel->setText(m_potentialFriends[i].getSurname());
    //            ui->SearchFriendLoginLabel->setText(m_potentialFriends[i].getLogin());
    //        }
    //    }
    //    ui->MainStackedWidgetInfo->setCurrentIndex(2);
}




void MainWindow::on_MainAddFrinedBut_clicked()
{
    m_pSERVER->addFriend(ui->SearchFriendLoginLabel->text());

    emit slotShowFriend(
                ui->SearchFriendNameLabel->text(),
                ui->SearchFriendSurnameLabel->text(),
                ui->SearchFriendLoginLabel->text());
}



void MainWindow::on_MainUserBut_clicked()
{
    ui->MainStackedWidgetInfo->setCurrentIndex(0);
    ui->tableWidget->setRowCount(0);
}




void MainWindow::on_ConntactsListWidget_currentTextChanged(const QString &currentText)
{
    //    for (int i = 0; i < m_friends.size(); i++)
    //    {
    //        if (currentText == m_friends[i].getLogin())
    //        {
    //            ui->FriendNameLabel->setText(m_friends[i].getName());
    //            ui->FriendSurnameLabel->setText(m_friends[i].getSurname());
    //            ui->FriendLoginLabel->setText(m_friends[i].getLogin());
    //            return;
    //        }
    //    }
    //    ui->DeleteConBut->setVisible(true);  // WHOT THIS??
    //    ui->MainStackedWidgetInfo->setCurrentIndex(1);

    ui->tableWidget->setRowCount(0);
    emit signalShowFriend(currentText);




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
    if (!ui->messageEdit->toPlainText().isEmpty() && !ui->FriendLoginLabel->text().isEmpty())
    {
        QDateTime dataTimeMessage = QDateTime::currentDateTime();

        m_pSERVER->sendMessage(
                    ui->UserLoginLabel->text(),
                    ui->FriendLoginLabel->text(),
                    ui->messageEdit->toPlainText(),
                    dataTimeMessage);

        addNewMessage(
                    ui->tableWidget,
                    new OutgoingMessage(
                        ui->UserLoginLabel->text(),
                        ui->messageEdit->toPlainText(),
                        dataTimeMessage.time().toString(),
                        ui->tableWidget));

        ui->messageEdit->clear();
    }
}


void MainWindow::slotAddFriendToList(QString login)
{
    ui->ConntactsListWidget->addItem(login);
}


void MainWindow::slotAddChatToList(const int &IDNumber)
{
    // ui->ChatTableWidget->addItem(QString::number(IDNumber));
}


void MainWindow::slotShowFriend(QString name, QString surname, QString login)
{
    ui->FriendNameLabel->setText(name);
    ui->FriendSurnameLabel->setText(surname);
    ui->FriendLoginLabel->setText(login);
    ui->MainStackedWidgetInfo->setCurrentIndex(1);

    f("slotShowFriend many");
}


void MainWindow::slotShowPotentialFriend(QString name, QString surname, QString login)
{
    ui->SearchFriendNameLabel->setText(name);
    ui->SearchFriendSurnameLabel->setText(surname);
    ui->SearchFriendLoginLabel->setText(login);
    ui->MainStackedWidgetInfo->setCurrentIndex(2);
}

void MainWindow::on_CreateCahtBut_clicked()
{
    addParticipantDialog->setFlagCreatingNewChat();
    addParticipantDialog->show();
    f("on_CreateCahtBut_clicked");
}


void MainWindow::on_ChatListWidget_itemClicked(QListWidgetItem *item)
{
    f("MainWindow::on_ChatListWidget_itemClicked(QListWidgetItem *item)");


    FormChat *currChat = dynamic_cast<FormChat*>(ui->ChatListWidget->itemWidget(item));
 f("MainWindow::on_ChatListWidget_itemClicked(QListWidgetItem *item)");
    f(currChat->m_admin);
    f(currChat->m_ChatName);

}
