#-------------------------------------------------
#
# Project created by QtCreator 2014-03-24T15:47:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UsingHistogram
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processstrategy.cpp \
    strategyhistogram1d.cpp \
    controller.cpp \
    strategycolorhistogram.cpp \
    strategylut.cpp

HEADERS  += mainwindow.h \
    processstrategy.h \
    strategyhistogram1d.h \
    controller.h \
    strategycolorhistogram.h \
    strategylut.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32 {

}
