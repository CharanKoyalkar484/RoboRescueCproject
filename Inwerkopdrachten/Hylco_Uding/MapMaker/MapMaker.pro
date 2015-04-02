#-------------------------------------------------
#
# Project created by QtCreator 2015-02-11T19:15:15
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapMaker
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        mapdisplay.cpp \
    editor.cpp \
    map.cpp \
    test.cpp

HEADERS  += mainwindow.h \
        mapdisplay.h \
    editor.h \
    map.h \
    test.h

FORMS    += mainwindow.ui \
        mapdisplay.ui \
    editor.ui

RESOURCES += \
    resource.qrc
