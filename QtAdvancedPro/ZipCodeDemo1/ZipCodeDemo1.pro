#-------------------------------------------------
#
# Project created by QtCreator 2014-07-09T09:28:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ZipCodeDemo1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    proxymodel.cpp \
    standardtablemodel.cpp \
    uniqueproxymodel.cpp \
    itemdelegate.cpp \
    zipcodespinbox.cpp

HEADERS  += mainwindow.h \
    global.h \
    proxymodel.h \
    standardtablemodel.h \
    uniqueproxymodel.h \
    itemdelegate.h \
    zipcodespinbox.h
