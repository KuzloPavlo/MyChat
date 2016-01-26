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
    serv_connect.cpp

HEADERS  += mainwindow.h \
    ../MyChat_Lib/community.h \
    ../MyChat_Lib/friends.h \
    ../MyChat_Lib/participantschat.h \
    ../MyChat_Lib/user.h \
    ../MyChat_Lib/usersarray.h \
    serv_connect.h \
    ../MyChat_Lib/messagetypes.h \
    ../MyChat_Lib/returnvalues.h

FORMS    += mainwindow.ui


INCLUDEPATH += "C:/MyChat/MyChat/MyChat_Lib"

LIBS += "C:/MyChat/MyChat/build-MyChat_Lib-Desktop_Qt_5_5_1_MSVC2013_64bit-Release/release/MyChat_Lib.lib"

RESOURCES += \
    mychat_cli_res.qrc
