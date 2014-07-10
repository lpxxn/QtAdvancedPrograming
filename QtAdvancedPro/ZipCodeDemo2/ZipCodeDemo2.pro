#-------------------------------------------------
#
# Project created by QtCreator 2014-07-10T13:48:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DEFINES += CUSTOM_MODEL

HEADERS	     += ../ZipCodeDemo1/global.h
HEADERS	     += ../ZipCodeDemo1/zipcodespinbox.h
SOURCES	     += ../ZipCodeDemo1/zipcodespinbox.cpp
HEADERS	     += ../ZipCodeDemo1/itemdelegate.h
SOURCES	     += ../ZipCodeDemo1/itemdelegate.cpp
HEADERS	     += ../ZipCodeDemo1/proxymodel.h
SOURCES	     += ../ZipCodeDemo1/proxymodel.cpp
HEADERS	     += ../ZipCodeDemo1/uniqueproxymodel.h
SOURCES	     += ../ZipCodeDemo1/uniqueproxymodel.cpp
HEADERS	     += ../ZipCodeDemo1/mainwindow.h
SOURCES      += ../ZipCodeDemo1/mainwindow.cpp
SOURCES      += ../ZipCodeDemo1/main.cpp
INCLUDEPATH  += ../ZipCodeDemo1

TARGET = ZipCodeDemo2
TEMPLATE = app

win32 { INCLUDEPATH += . }
SOURCES +=\
    tablemodel.cpp

HEADERS  += \
    tablemodel.h \
    zpcodeitem.h
