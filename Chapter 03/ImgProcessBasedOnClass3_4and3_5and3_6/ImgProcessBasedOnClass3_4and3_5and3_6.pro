#-------------------------------------------------
#
# Project created by QtCreator 2014-03-21T16:17:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImgProcessBasedOnClass3_4and3_5and3_6
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    colordetectcontroller.cpp \
    context.cpp \
    strategycolordetector.cpp \
    processstrategy.cpp

HEADERS  += mainwindow.h \
    colordetectcontroller.h \
    context.h \
    strategycolordetector.h \
    processstrategy.h

FORMS    += mainwindow.ui

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv
}
win32 {

}
