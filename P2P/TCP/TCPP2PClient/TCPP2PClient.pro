#-------------------------------------------------
#
# Project created by QtCreator 2013-04-29T13:24:34
#
#-------------------------------------------------

QT       += core gui
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TCPP2PClient
TEMPLATE = app


SOURCES += \
    User.cpp \
    startdialog.cpp \
    server.cpp \
    reghandle.cpp \
    newconnthread.cpp \
    manualthread.cpp \
    mainwindow.cpp \
    main.cpp \
    data.cpp

HEADERS  += \
    User.h \
    startdialog.h \
    server.h \
    reghandle.h \
    newconnthread.h \
    manualthread.h \
    mainwindow.h \
    data.h

FORMS += \
    startdialog.ui \
    mainwindow.ui
