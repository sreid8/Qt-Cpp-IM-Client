#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T13:21:32
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = TCPRegistrar
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    User.cpp \
    socketthread.cpp \
    server.cpp \
    main.cpp

HEADERS += \
    User.h \
    socketthread.h \
    server.h
