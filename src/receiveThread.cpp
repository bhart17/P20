#include "receiveThread.h"

void ReceiveThread::receive() {
    auto data = 0;
    for (auto i = 0; i < 22; ++i) {
        auto startTime = millis();
        while (!digitalRead(REC_CLOCK)) {
            if ((millis() - startTime) > 25) {
                qDebug().nospace().noquote()
                    << "Received: "
                    << QString::number(data, 2).rightJustified(22, '0') << "(#"
                    << count++ << ") ⚠️ Packet error: before data read";
                return;
            }
        }
        data = (digitalRead(REC_DATA) << i) | data;
        startTime = millis();
        while (digitalRead(REC_CLOCK) && i < 21) {
            if ((millis() - startTime) > 25) {
                qDebug().nospace().noquote()
                    << "Received: "
                    << QString::number(data, 2).rightJustified(22, '0') << "(#"
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
        if (!digitalRead(REC_CLOCK)) {
            receive();
        }
    }
    deleteLater();
}