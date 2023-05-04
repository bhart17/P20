#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app


SOURCES += main.cpp \
        window.cpp \
        drawArea.cpp \
        sendWindow.cpp \
        receiveWindow.cpp \
        drawAreaSend.cpp \
        threads.cpp \

HEADERS  += window.h \
        drawArea.h \
        sendWindow.h \
        receiveWindow.h \
        drawAreaSend.h \
        threads.h \

#LIBS += -L/usr/local/lib -lwiringPi -lpthread
LIBS += -L/usr/local/lib -lpthread
