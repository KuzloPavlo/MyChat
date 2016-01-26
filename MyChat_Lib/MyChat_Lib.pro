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
    usersarray.cpp

HEADERS += user.h \
    friends.h \
    participantschat.h \
    community.h \
    messagetypes.h \
    returnvalues.h \
    usersarray.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}
