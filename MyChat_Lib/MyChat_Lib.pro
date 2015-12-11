#-------------------------------------------------
#
# Project created by QtCreator 2015-11-25T12:28:57
#
#-------------------------------------------------

QT       -= gui

TARGET = MyChat_Lib
TEMPLATE = lib
CONFIG += staticlib

SOURCES += user.cpp \
    friends.cpp \
    participantschat.cpp \
    community.cpp \
    arrayofusers.cpp

HEADERS += user.h \
    friends.h \
    participantschat.h \
    community.h \
    arrayofusers.h \
    magicnumber.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
