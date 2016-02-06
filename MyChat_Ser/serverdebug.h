#pragma once
#include <QString>
#include <QObject>


namespace Ui {
class ServerDebug;
}

class ServerDebug
{
    Q_OBJECT

public:
    explicit ServerDebug();
    ~ServerDebug();
public slots:
    void slotdebug(const QString &str);


private:
    Ui::ServerDebug *ui;
};
