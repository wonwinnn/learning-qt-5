#-------------------------------------------------
#
# Project created by QtCreator 2019-01-09T20:06:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StringListM
TEMPLATE = app


SOURCES += main.cpp\
 
    mylistview.cpp \
    spinboxdelegate.cpp

HEADERS  += mylistview.h \
    spinboxdelegate.h

CONFIG   += c++11
