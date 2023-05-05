#include "threads.h"

ReceiveThread::ReceiveThread(QObject *parent) : QObject(parent) {
    qDebug() << this << "Thread Started" << QThread::currentThread();
}

ReceiveThread::~ReceiveThread() {
    qDebug() << this << "Thread Ended" << QThread::currentThread();
}

void ReceiveThread::testRun() {
    qDebug() << "Cheers two prep work" << QThread::currentThread();
    for (int i = 0; i < 10; i++) {
        qDebug() << "Hardly Working" << QString::number(i)
                 << QThread::currentThread();
        QThread::currentThread()->msleep(500);
    }
    qDebug() << "Finished at 2am" << QThread::currentThread();
    this->deleteLater();  // This apparently deletes the otherwise unmanaged
                          // point created by: "ReceiveThread *recThread = new
                          // ReceiveThread()" in main.cpp
}

void ReceiveThread::run() {
    // insert actual Receiver code here
    this->deleteLater();  // This apparently deletes the otherwise unmanaged
                          // point created by: "ReceiveThread *recThread = new
                          // ReceiveThread()" in main.cpp
}

SendThread::SendThread(QObject *parent) : QObject(parent) {
    qDebug() << this << "Thread Started" << QThread::currentThread();
}

SendThread::~SendThread() {
    qDebug() << this << "Thread Ended" << QThread::currentThread();
}

void SendThread::testRun() {
    qDebug() << "I love trees" << QThread::currentThread();
    for (int i = 0; i < 10; i++) {
        qDebug() << "Me three" << QString::number(i)
                 << QThread::currentThread();
        QThread::currentThread()->msleep(500);
    }
    qDebug() << "Finished at 3am" << QThread::currentThread();
    this->deleteLater();  // This apparently deletes the otherwise unmanaged
                          // point created by: "ReceiveThread *recThread = new
                          // ReceiveThread()" in main.cpp
}

void SendThread::run() {
    // insert actual Receiver code here
    this->deleteLater();  // This apparently deletes the otherwise unmanaged
                          // point created by: "ReceiveThread *recThread = new
                          // ReceiveThread()" in main.cpp
}