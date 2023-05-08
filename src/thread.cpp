#include "thread.h"

Thread::Thread(QObject *parent) : QObject(parent) {
    qDebug() << this << "Thread Started" << QThread::currentThread();
}

Thread::~Thread() {
    qDebug() << this << "Thread Ended" << QThread::currentThread();
}

// void Thread::run() { this->deleteLater(); }