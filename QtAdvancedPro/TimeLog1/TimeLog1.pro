#-------------------------------------------------
#
# Project created by QtCreator 2014-07-11T14:09:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TimeLog1
TEMPLATE = app

RESOURCES   += timelog.qrc


SOURCES += main.cpp\
        mainwindow.cpp \
    richtextdelegate.cpp \
    richtextlineedit.cpp \
    standarditem.cpp \
    standardtreemodel.cpp

HEADERS  += mainwindow.h \
    global.h \
    richtextdelegate.h \
    richtextlineedit.h \
    standarditem.h \
    standardtreemodel.h
