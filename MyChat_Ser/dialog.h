#pragma once
#include <QDialog>
#include <QApplication>
#include <QWidget>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

    public slots:
    void slotdebug(const QString &str);

private:
    Ui::Dialog *ui;
};

