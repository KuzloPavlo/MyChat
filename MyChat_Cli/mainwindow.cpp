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

    ui->tableParticipiantsChat->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableParticipiantsChat->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    m_currentFriend = "";
    m_сurrentTetATetChat = true;
    m_currentGroupChat = -1;

    //--------------------------------------------------------------+
    // section for experiments                                      |
    //--------------------------------------------------------------+
    ui->tableParticipiantsChat->setCellWidget(0,0, new FormParticipant("Pavlo","Kuzlo", "KPV", ui->tableParticipiantsChat));

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

    //    for(int i = 0; i < 20; i++)
    //    {
    //        emit slotAddChatToList(ID,chtname,part);
    //        // FormChat *newchat =  new FormChat(ID,chtname,adm, part, ui->ChatListWidget);
    //    }
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
                SIGNAL(signalGroupIncomingMessage(int,QString,QString,QString)),
                this,
                SLOT(slotGroupIncomingMessage(int,QString,QString,QString))
                );


    connect(
                m_pSERVER,
                SIGNAL(signalEarlierReceivedMessage(const int&,const QString &,const QString &,const QString &)),
                this,
                SLOT(slotEarlierReceivedMessage(const int&,const QString &,const QString &,const QString &))
                );

    connect(
                m_pSERVER,
                SIGNAL(signalEarlierSendMessage(const int&,const QString &,const QString &,const QString &)),
                this,
                SLOT(slotEarlierSendMessage(const int&,const QString &,const QString &,const QString &))
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
                SIGNAL(signalAddChatToList(const int &,
                                           const QString &,
                                           QVector<QString> )),
                this,
                SLOT(slotAddChatToList(const int &,
                                       const QString &,
                                       QVector<QString> ))
                );

    connect(
                this,
                SIGNAL(signalShowChat(const int &)),
                m_pSERVER,
                SLOT(slotShowChat(const int &))
                );

    connect(
                m_pSERVER,
                SIGNAL(signalShowChat(const int &,
                                      const QString &,
                                      QVector<QString>,
                                      QVector<QString>,
                                      QVector<QString>)),
                this,
                SLOT(slotShowChat(const int &,
                                  const QString &,
                                  QVector<QString>,
                                  QVector<QString>,
                                  QVector<QString>))
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

//void

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
    if (sender == m_currentFriend && m_сurrentTetATetChat)
    {
        addNewMessage(ui->tableWidget, new IncomingMessage(sender,message,time,ui->tableWidget));
    }
}


void MainWindow::slotGroupIncomingMessage(const int &IDnumber, const QString &sender, const QString &message, const QString &time)
{
    if(IDnumber == m_currentGroupChat && !m_сurrentTetATetChat)
    {
        addNewMessage(ui->tableWidget, new IncomingMessage(sender,message,time,ui->tableWidget));
    }
}


void MainWindow::slotEarlierReceivedMessage(const int &IDNumber,const QString &sender, const QString &message, const QString &time)
{
    if ((m_currentFriend == sender && m_сurrentTetATetChat) ||
            (m_currentGroupChat == IDNumber && !m_сurrentTetATetChat))
    {
        addNewMessage(ui->tableWidget, new IncomingMessage(sender,message,time,ui->tableWidget));
    }

}


void MainWindow::slotEarlierSendMessage(const int &IDNumber,const QString &recipient, const QString &message, const QString &time)
{
    if ((m_currentFriend == recipient && m_сurrentTetATetChat) ||
            (m_currentGroupChat == IDNumber && !m_сurrentTetATetChat))
    {
        addNewMessage(ui->tableWidget, new OutgoingMessage (ui->UserLoginLabel->text(),message,time,ui->tableWidget));
    }

}


void MainWindow::on_MainConnBut_clicked()
{
    ui->ConntactsListWidget->clear();

    emit signalShowListFriends();

    ui->MainStackedWidgetConntact->setCurrentIndex(0);
    ui->MainStackedWidgetInfo->setCurrentIndex(3);
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
    m_currentFriend = currentText;
    m_сurrentTetATetChat = true;
    m_currentGroupChat = 0;
    ui->tableWidget->setRowCount(0);
    emit signalShowFriend(currentText);
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
    f("on_SendMessageBut_clicked()1");
    f(&m_сurrentTetATetChat);
    f(m_currentGroupChat);
    f(m_currentFriend);

    QDateTime dataTimeMessage = QDateTime::currentDateTime();

    if (!ui->messageEdit->toPlainText().isEmpty())
    {
        if(m_сurrentTetATetChat && m_currentFriend != "")
        {
            m_pSERVER->sendMessage(
                        ui->UserLoginLabel->text(),
                        m_currentFriend,
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

        if(!m_сurrentTetATetChat && m_currentGroupChat > 0)
        {
            m_pSERVER->sendMessage(
                        ui->UserLoginLabel->text(),
                        m_currentGroupChat,
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
}


void MainWindow::slotAddFriendToList(QString login)
{
    ui->ConntactsListWidget->addItem(login);
}


void MainWindow::slotAddChatToList(const int &IDNumer,
                                   const QString &chatName,
                                   QVector<QString> participants)
{
    f("MainWindow::slotAddChatToList1");
    FormChat *newChat  = new FormChat(IDNumer,chatName,participants,ui->ChatListWidget);
    f("MainWindow::slotAddChatToList2");
}


void MainWindow::slotShowFriend(QString name, QString surname, QString login)
{
    ui->FriendNameLabel->setText(name);
    ui->FriendSurnameLabel->setText(surname);
    ui->FriendLoginLabel->setText(login);
    ui->MainStackedWidgetInfo->setCurrentIndex(1);

    f("slotShowFriend many");
}


void MainWindow::slotShowChat(
        const int &IDNumber,const QString &chatName,
        QVector<QString> admin, QVector<QString> friends, QVector<QString> notFriends)
{
    f("slotShowChat");
    if(!m_сurrentTetATetChat && IDNumber == m_currentGroupChat)
    {
        int rowCount = 1;
        int nColumn = 0;

        ui->tableParticipiantsChat->clearContents();
        ui->tableParticipiantsChat->setRowCount(rowCount);

        ui->ChatNameLabel->setText(chatName);

        ui->AdminLabel->setText(admin[0] + " " + admin[1]);

        for(int i = 0; i < friends.size(); i += 3)
        {
            FormParticipant *tempParticipant = new FormParticipant(friends[i+0],
                    friends[i+1], friends[i+2],ui->tableParticipiantsChat);

            if(nColumn == 3)
            {
                ui->tableParticipiantsChat->insertRow(rowCount);
                rowCount++;
                nColumn = 0;
            }

            ui->tableParticipiantsChat->setCellWidget(rowCount-1,nColumn,tempParticipant);
            nColumn++;
        }

        for(int j = 0; j < notFriends.size(); j++)
        {
            FormParticipant *tempParticipant = new FormParticipant(
                        notFriends[j], ui->tableParticipiantsChat);

            if(nColumn == 3)
            {
                ui->tableParticipiantsChat->insertRow(rowCount);
                rowCount++;
                nColumn = 0;
            }

            ui->tableParticipiantsChat->setCellWidget(rowCount-1, nColumn,tempParticipant);
            nColumn++;
        }
        ui->MainStackedWidgetInfo->setCurrentIndex(6);
    }
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
}



void MainWindow::on_ChatListWidget_itemClicked(QListWidgetItem *item)
{ f("MainWindow::on_ChatListWidget_itemClicked1");
    FormChat *currChat = dynamic_cast<FormChat*> (ui->ChatListWidget->itemWidget(item));
    m_currentGroupChat = currChat->getIDNumber();
    m_сurrentTetATetChat = false;
    ui->tableWidget->setRowCount(0);
    emit signalShowChat(currChat->getIDNumber());
    f("MainWindow::on_ChatListWidget_itemClicked2");
}
