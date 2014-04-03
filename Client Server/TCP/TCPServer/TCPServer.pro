#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T12:45:32
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = TCPServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    user.cpp \
    threadFrame.cpp \
    mythread.cpp \
    myserver.cpp \
    main.cpp \
    frameData.cpp \
    data.cpp

HEADERS += \
    user.h \
    threadFrame.h \
    mythread.h \
    myserver.h \
    frameData.h \
    data.h
