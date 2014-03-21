#-------------------------------------------------
#
# Project created by QtCreator 2014-03-21T10:32:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProcessBasedOnClass3_3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    context.cpp \
    processstrategy.cpp \
    strategycolordetector.cpp \
    colordetectcontroller.cpp

HEADERS  += mainwindow.h \
    context.h \
    processstrategy.h \
    strategycolordetector.h \
    colordetectcontroller.h

FORMS    += mainwindow.ui

#opencvlib
unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32 {

}
