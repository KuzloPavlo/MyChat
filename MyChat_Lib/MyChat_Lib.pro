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
    friends.cpp \
    participantschat.cpp \
    community.cpp \
    usersarray.cpp \
    correspondence.cpp

HEADERS += user.h \
    friends.h \
    participantschat.h \
    community.h \
    messagetypes.h \
    returnvalues.h \
    usersarray.h \
    message.h \
    correspondence.h \
    interlocutor.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
