#-------------------------------------------------
#
# Project created by QtCreator 2015-06-22T12:29:13
#
#-------------------------------------------------

QT       += core gui
QT       += serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlashLoader
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    hdlc.cpp \
    sleeper.cpp \
    flash_loader.cpp

HEADERS  += mainwindow.h \
    hdlc.h \
    sleeper.h \
    flash_loader.h


FORMS    += mainwindow.ui
