#include "receiveThread.h"

void ReceiveThread::receive() {
    unsigned int data = 0;
    for (auto i = 0; i < 22; ++i) {
        using namespace std::chrono;
        auto startTime = high_resolution_clock::now();
        while (!Thread::clock) {
            if (duration_cast<milliseconds>(high_resolution_clock::now() -
                                            startTime)
                    .count() > TIMEOUT_MS) {
                qDebug().nospace().noquote()
                    << "Received: "
                    << QString::number(data, 2).rightJustified(22, '0') << " (#"
                    << count++ << ") ⚠️ Packet error: before data read";
                return;
            }
        }
        data = (Thread::pin << i) | data;
        startTime = high_resolution_clock::now();
        while (Thread::clock && i < 21) {
            if (duration_cast<milliseconds>(high_resolution_clock::now() -
                                            startTime)
                    .count() > TIMEOUT_MS) {
                qDebug().nospace().noquote()
                    << "Received: "
                    << QString::number(data, 2).rightJustified(22, '0') << " (#"
                    << count++ << ") ⚠️ Packet error: after data read";
                return;
            }
        }
    }
    qDebug().nospace().noquote()
        << "Received: " << QString::number(data, 2).rightJustified(22, '0')
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