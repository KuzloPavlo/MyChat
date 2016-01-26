#pragma once

#include <QString>
#include <QDateTime>

struct Message
{
QString mSender;
QString mRecipient;
QString mMessageText;
QDateTime mDataTime;
};
