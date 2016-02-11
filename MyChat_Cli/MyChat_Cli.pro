#-------------------------------------------------
#
# Project created by QtCreator 2015-11-25T17:41:32
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyChat_Cli
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    formmessage.cpp \
    incomingmessage.cpp \
    outgoingmessage.cpp \
    servermessage.cpp \
    addparticipantdialog.cpp \
    formchat.cpp \
    formfriend.cpp \
    formparticipant.cpp

HEADERS  += mainwindow.h \
    ../MyChat_Lib/user.h \
    ../MyChat_Lib/usersarray.h \
    ../MyChat_Lib/messagetypes.h \
     ../MyChat_Lib/message.h \
    ../MyChat_Lib/returnvalues.h \
    ../MyChat_Lib/correspondence.h \
    client.h \
    formmessage.h \
    incomingmessage.h \
    outgoingmessage.h \
    servermessage.h \
    addparticipantdialog.h \
    formchat.h \
    formfriend.h \
    formparticipant.h

FORMS    += mainwindow.ui \
    formmessage.ui \
    addparticipantdialog.ui \
    formchat.ui \
    formfriend.ui


INCLUDEPATH += "C:/MyChat/MyChat/MyChat_Lib"

LIBS += "C:/MyChat/MyChat/build-MyChat_Lib-Desktop_Qt_5_5_1_MSVC2013_64bit-Debug/debug/MyChat_Lib.lib"

RESOURCES += \
    mychat_cli_res.qrc
