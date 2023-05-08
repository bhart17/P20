#include "receiveThread.h"

void ReceiveThread::testRun() {
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

void ReceiveThread::receive() {
    // Thread::mutex.lock();
    unsigned int data = 0;
    // QThread::currentThread()->msleep(1);
    for (int i = 0; i < 22; ++i) {
        data = (Thread::pin << i) | data;
        //qDebug() << "Received: " << Thread::clock << (int)Thread::pin;
        bool lastClock = Thread::clock;
        while (Thread::clock == lastClock && i < 21) {
            QThread::currentThread()->usleep(100);
        }
        // QThread::currentThread()->msleep(1);
    }
    // QThread::currentThread()->msleep(1);
    qDebug() << "Received: " << QString::number(data, 2);
    // Thread::mutex.unlock();mamak
    deserialise(data);
}

void ReceiveThread::deserialise(unsigned int data) {
    switch (data & 3) {
        case START:
            emit startLineSig(
                QPointF{(qreal)(data >> 12), (qreal)((data >> 2) & 1023)});
            break;
        case CONTINUE:
            emit continueLineSig(
                QPointF{(qreal)(data >> 12), (qreal)((data >> 2) & 1023)});
            break;
        case CLEAR:
            emit clearScreenSig();
            break;
        default:
            qDebug() << "fell through";
            break;
    }
}

void ReceiveThread::run() {
    bool lastClock = Thread::clock;
    while (!finished) {
        // QCoreApplication::processEvents();
        if (Thread::clock != lastClock) {
            receive();
        } else {
            lastClock = Thread::clock;
            QThread::currentThread()->usleep(100);
        }
    }
    deleteLater();
}