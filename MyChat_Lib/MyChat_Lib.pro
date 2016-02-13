#-------------------------------------------------
#
# Project created by QtCreator 2015-11-25T12:28:57
#
#-------------------------------------------------

QT       -= gui
QT += network

TARGET = MyChat_Lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += user.cpp \
    correspondence.cpp \
    users.cpp

HEADERS += user.h \
    messagetypes.h \
    returnvalues.h \
    message.h \
    correspondence.h \
    users.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
