#-------------------------------------------------
#
# Project created by QtCreator 2015-02-04T13:43:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lab20
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++17

SOURCES += main.cpp \
        window.cpp \
        drawArea.cpp \
        sendWindow.cpp \
        receiveWindow.cpp \
        drawAreaSend.cpp \
        # serial.cpp \
        thread.cpp \
        sendThread.cpp \
        receiveThread.cpp

HEADERS  += window.h \
        drawArea.h \
        sendWindow.h \
        receiveWindow.h \
        drawAreaSend.h \
        # serial.h \
        thread.h \
        sendThread.h \
        receiveThread.h

LIBS += -L/usr/local/lib -lwiringPi
#LIBS += -L/usr/local/lib -lpthread
