#pragma once
#include "formmessage.h"

class ServerMessage :public FormMessage
{
    Q_OBJECT

public:
    ServerMessage( const QString &sender,
                   const QString &message,
                   const QString &time,
                   QWidget *parent = 0);
};
