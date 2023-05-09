#include "receiveThread.h"

void ReceiveThread::receive() {
    auto data = 0;
    // QThread::currentThread()->msleep(1000*(1/BAUD));
    for (auto i = 0; i < 22; ++i) {
        // data = (digitalRead(REC_DATA) << i) | data;
        QThread::currentThread()->msleep(SLEEP_MS);
        data = (Thread::pin << i) | data;

        // auto prevMicros = micros();
        //     while (true) {
        //         auto currentMicros = micros();
        //         if (currentMicros - prevMicros > 10) {
        //             break;
        //         }
        //     }
    }
    QThread::currentThread()->msleep(SLEEP_MS);

    qDebug() << "Received:" << QString::number(data, 2).rightJustified(22, '0')
             << "(#" << count++ << ")";
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
            qDebug() << "Fell Through";
            break;
    }
}

void ReceiveThread::run() {
    while (!finished) {
        // if (digitalRead(REC_DATA) == true) {
        // if (Thread::pin == false) {
        //     receive();
        // } else {
        //     QThread::currentThread()->usleep(100);

        //     //     auto prevMillis = micros();
        //     //     while (true) {
        //     //         auto currentMillis = micros();
        //     //         if (currentMillis - prevMillis > 250) {
        //     //             break;
        //     //         }
        //     //     }
        // }

        while (!finished && Thread::pin == true) {
            receive();
        }
        QThread::currentThread()->usleep(500);
    }
    deleteLater();
}