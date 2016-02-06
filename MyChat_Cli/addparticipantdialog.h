#pragma once
#include <QDialog>
#include <QVector>
#include <QString>

namespace Ui {
class AddParticipantDialog;
}

class AddParticipantDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddParticipantDialog(QWidget *parent = 0);
    ~AddParticipantDialog();
    void setFlagCreatingNewChat();
    void setFlagAddingParticipants();
   // bool isNewChat();

signals:

    void signalFindParticipants(const QString &tokenParticipant);

private slots:
    void on_findFriendEdit_textChanged(const QString &arg1);
    void slotFindParticipant(const QString &login);

    void on_listFriends_currentTextChanged(const QString &currentText);

    void on_addParticipantBut_clicked();

    void on_closeBut_clicked();

private:
    Ui::AddParticipantDialog *ui;
    QString m_currentItem;
    QVector<QString> m_currentParticipants;
    QVector<QString> m_newParticipants;
    bool m_flagCreatedNew;
    void AddNewParticipant();
    void CreateNewCaht();

    void f(const QString &str); // for debug
};
