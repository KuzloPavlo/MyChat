#include "addparticipantdialog.h"
#include "ui_addparticipantdialog.h"

AddParticipantDialog::AddParticipantDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddParticipantDialog)
{
    this->setWindowFlags(Qt::Window | Qt::WindowTitleHint);
    ui->setupUi(this);
    ui->addParticipantBut->setVisible(false);
    ui->Attention->setVisible(false);
}

AddParticipantDialog::~AddParticipantDialog()
{
    delete ui;
}

void AddParticipantDialog::on_findFriendEdit_textChanged(const QString &arg1)
{
    if(!ui->findFriendEdit->text().isEmpty())
    {
        f("on_findFriendEdit_textChanged1");
        ui->listFriends->clear();
        emit signalFindParticipants(arg1);
        f("on_findFriendEdit_textChanged2");
    }
}


void AddParticipantDialog::slotFindParticipant(const QString &login)
{
    f("AddParticipantDialog::slotFindParticipant1");
    ui->listFriends->addItem(login);
    f("AddParticipantDialog::slotFindParticipant2");
}

void AddParticipantDialog::f(const QString &str)
{
    ui->forDebug->addItem(str);
}

void AddParticipantDialog::on_listFriends_currentTextChanged(const QString &currentText)
{
    m_currentItem = currentText;
    ui->addParticipantBut->setVisible(true);
}

void AddParticipantDialog::on_addParticipantBut_clicked()
{
    for(int i = 0; i < m_currentParticipants.size(); i++)
    {
        if(m_currentParticipants[i] == m_currentItem)
        {
            return;
        }
    }
    m_newParticipants.push_back(m_currentItem);
}

void AddParticipantDialog::setFlagCreatingNewChat()
{
    m_flagCreatedNew = true;
}

void AddParticipantDialog::setFlagAddingParticipants()
{
    m_flagCreatedNew = false;
}

//void AddParticipantDialog::isNewChat()
//{
//    return m_flagCreatedNew;
//}

void AddParticipantDialog::on_closeBut_clicked()
{
    if(m_flagCreatedNew)
    {
        if(m_newParticipants.size() == 0)
        {
            ui->Attention->setVisible(true);
            return;
        }
        ui->Attention->setVisible(false);
        CreateNewCaht();
        this->hide();
    }
    else
    {
        AddNewParticipant();
    }

}

void AddParticipantDialog::AddNewParticipant()
{

}

void AddParticipantDialog::CreateNewCaht()
{

}
