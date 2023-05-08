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
        data = (digitalRead(REC_DATA) << i) | data;
        bool lastClock = digitalRead(REC_CLOCK);
        qDebug() << "Received: " << lastClock << digitalRead(REC_DATA);
        // auto prevMillis = micros();
        while (digitalRead(REC_CLOCK) == lastClock && i < 21) {
            auto prevMillis = micros();
            while (true) {
                auto currentMillis = micros();
                if (currentMillis - prevMillis > 250) {
                    break;
                }
            }
            // delayMicroseconds(250);
            // QThread::currentThread()->usleep(250);
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
                QPoint{(int)(data >> 12), (int)((data >> 2) & 1023)});
            break;
        case CONTINUE:
            emit continueLineSig(
                QPoint{(int)(data >> 12), (int)((data >> 2) & 1023)});
            break;
        case CLEAR:
            emit clearScreenSig();
            break;
        default:
            qDebug() << "fell through " << data;
            break;
    }
}

void ReceiveThread::run() {
    bool lastClock = digitalRead(REC_CLOCK);
    while (!finished) {
        // QCoreApplication::processEvents();
        if (digitalRead(REC_CLOCK) != lastClock) {
            receive();
        } else {
            lastClock = digitalRead(REC_CLOCK);
            auto prevMillis = micros();
            while (true) {
                auto currentMillis = micros();
                if (currentMillis - prevMillis > 250) {
                    break;
                }
            }
            // delayMicroseconds(250);
            // QThread::currentThread()->usleep(250);
        }
    }
    deleteLater();
}