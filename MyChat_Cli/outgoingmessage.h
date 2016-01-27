#pragma once
#include "formmessage.h"

class OutgoingMessage : public FormMessage
{
public:
    OutgoingMessage( const QString &sender,
                     const QString &message,
                     const QString &time,
                     QWidget *parent = 0);
};
