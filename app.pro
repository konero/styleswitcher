QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

SOURCES += main.cpp \
           theme.cpp

HEADERS += theme.h

RESOURCES += resource.qrc
