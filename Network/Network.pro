#-------------------------------------------------
#
# Project created by QtCreator 2019-01-11T20:22:20
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Network
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    weather.cpp

HEADERS  += mainwindow.h \
    weather.h

CONFIG += c++11
