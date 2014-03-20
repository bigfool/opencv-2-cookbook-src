#-------------------------------------------------
#
# Project created by QtCreator 2014-03-20T20:44:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProcessBasedOnClass3_2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    processstrategy.cpp \
    strategycolordetector.cpp \
    context.cpp

HEADERS  += mainwindow.h \
    processstrategy.h \
    strategycolordetector.h \
    context.h

FORMS    += mainwindow.ui

#opencvlib
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32 {

}
