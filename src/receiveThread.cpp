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

void ReceiveThread::receive(unsigned int data) {
    // real recieve code here
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