#-------------------------------------------------
#
# Project created by QtCreator 2015-11-08T19:30:56
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = http_client
TEMPLATE = app


SOURCES += main.cpp\
        gui.cpp

HEADERS  += gui.hpp

FORMS    += gui.ui

CONFIG += c++11
