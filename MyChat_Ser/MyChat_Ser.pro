QT += core
QT += network
//---
QT += gui
 QT += widgets
 TEMPLATE = app
//--
TARGET = MyChat_Ser
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp

INCLUDEPATH += "C:/MyChat/MyChat/MyChat_Lib"

LIBS += "C:/MyChat/MyChat/build-MyChat_Lib-Desktop_Qt_5_5_1_MSVC2013_64bit-Release/release/MyChat_Lib.lib"

HEADERS += \
    ../MyChat_Lib/user.h \
    ../MyChat_Lib/usersarray.h \
    server.h \
    ../MyChat_Lib/messagetypes.h \
    ../MyChat_Lib/returnvalues.h \
    ../MyChat_Lib/correspondence.h

FORMS +=
