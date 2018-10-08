QT += core
QT -= gui

CONFIG += c++11

TARGET = JsonDocumentIO
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CJsonIO.cpp \
    CJsonIO2.cpp \
    CJsonIO3.cpp

HEADERS += \
    CJsonIO.h \
    CJsonIO2.h \
    CJsonIO3.h
