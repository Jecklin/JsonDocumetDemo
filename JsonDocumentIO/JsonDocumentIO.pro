QT += core
QT -= gui

CONFIG += c++11

TARGET = JsonDocumentIO
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CJsonIO.cpp

HEADERS += \
    CJsonIO.h
