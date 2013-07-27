#-------------------------------------------------
#
# Project created by QtCreator 2012-12-09T03:56:29
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sqlbuild
TEMPLATE = app

INCLUDEPATH += /home/dainis/boost-trunk
SOURCES += main.cpp\
        mainwindow.cpp \
    cview.cpp \
    cscene.cpp \
    ctableitem.cpp

HEADERS  += mainwindow.h \
    cview.h \
    cscene.h \
    ctableitem.h

FORMS    += mainwindow.ui
