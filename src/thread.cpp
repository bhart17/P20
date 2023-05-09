#include "thread.h"

Thread::Thread(QObject *parent) : QObject(parent) {
    qDebug() << this << "started, parent" << QThread::currentThread();
}

Thread::~Thread() {
    qDebug() << QThread::currentThread() << "ended";
}