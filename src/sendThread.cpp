#include "sendThread.h"

// Writes a packet of data to the GPIO and pulses the clock
void SendThread::send(unsigned int data) {
    for (auto i = 0; i < BITS; ++i) {
        digitalWrite(SEND_DATA, (data >> i) & 1);
        digitalWrite(SEND_CLOCK, false);
        delayMicroseconds(SLEEP_US / 2);
        digitalWrite(SEND_CLOCK, true);
        delayMicroseconds(SLEEP_US / 2);
    }
    delayMicroseconds(SLEEP_US);
    qDebug().nospace().noquote()
        << "Sent:     " << QString::number(data, 2).rightJustified(BITS, '0')
        << " (#" << count++ << ")";
}

// Serialisation converts commands and data into an unsigned int
unsigned int SendThread::serialise(type type, QPoint point) {
    auto data = type | (std::clamp((int)point.y(), 0, 1023) << 2) |
                (std::clamp((int)point.x(), 0, 1023) << 12);
    data |= __builtin_parity(data) << (BITS - 1);
    return data;
}

// Handles all signals sent to SendThread
void SendThread::sendHandler(int type_, QPoint point) {
    queue.enqueue(serialise((type)type_, point));
}

// Main event loop of SendThread
void SendThread::run() {
    while (!finished) {
        if (!queue.isEmpty()) {
            send(queue.dequeue());
        } else {
            QCoreApplication::processEvents();
        }
    }
    deleteLater();
}