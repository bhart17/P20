#include "thread.h"

//Both the construtor and destructor of the thread class have a qDebug() to print to the screen when the thread starts and ends
Thread::Thread(QObject *parent) : QObject(parent) {
    qDebug() << this << "started, parent" << QThread::currentThread();
}

Thread::~Thread() {
    qDebug() << QThread::currentThread() << "ended";
}