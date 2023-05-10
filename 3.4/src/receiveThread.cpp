#include "receiveThread.h"

void ReceiveThread::receive() {
    unsigned int data = 0;
    for (auto i = 0; i < BITS; ++i) {
        // auto startTime = millis();
        while (!Thread::clock) {
            QThread::currentThread()->usleep(100);
            // if ((millis() - startTime) > TIMEOUT_MS) {
            //     qDebug().nospace().noquote()
            //         << "Received: "
            //         << QString::number(data, 2).rightJustified(BITS, '0')
            //         << " (#" << count++ << ") ⚠️ Packet error: before data
            //         read";
            //     return;
            // }
        }
        data = (Thread::data << i) | data;
        // startTime = millis();
        while (Thread::clock && i < (BITS - 1)) {
            QThread::currentThread()->usleep(100);
            // if ((millis() - startTime) > TIMEOUT_MS) {
            //     qDebug().nospace().noquote()
            //         << "Received: "
            //         << QString::number(data, 2).rightJustified(BITS, '0')
            //         << " (#" << count++ << ") ⚠️ Packet error: after data
            //         read";
            //     return;
            // }
        }
    }
    qDebug().nospace().noquote()
        << "Received: " << QString::number(data, 2).rightJustified(BITS, '0')
        << " (#" << count++ << ")";
    deserialise(data);
}

void ReceiveThread::deserialise(unsigned int data) {
    emit receiveSignal((type)(data & 3),
                       QPoint{(int)(data >> 12), (int)((data >> 2) & 1023)});
}

void ReceiveThread::run() {
    while (!finished) {
        if (!Thread::clock) {
            receive();
        }
    }
    deleteLater();
}