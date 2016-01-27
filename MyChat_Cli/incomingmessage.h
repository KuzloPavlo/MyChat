#pragma once
#include "formmessage.h"

class IncomingMessage : public FormMessage
{
    Q_OBJECT

public:
    IncomingMessage( const QString &sender,
                     const QString &message,
                     const QString &time,
                     QWidget *parent = 0);
};
