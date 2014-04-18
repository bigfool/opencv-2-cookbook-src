#-------------------------------------------------
#
# Project created by QtCreator 2014-04-10T15:05:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = morphology
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processstrategy.cpp \
    controller.cpp \
    strategymorpholine.cpp \
    strategymorphcorner.cpp \
    strategywatershed.cpp

HEADERS  += mainwindow.h \
    processstrategy.h \
    controller.h \
    strategymorpholine.h \
    strategymorphcorner.h \
    strategywatershed.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32 {

}
