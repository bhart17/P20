#include "sendThread.h"

void SendThread::send(unsigned int data) {
    for (int i = 0; i < BITS; ++i) {
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

unsigned int SendThread::serialise(type type, QPoint point) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 23: parity
    // 0b1010101001001100110001
    auto data = type | (std::clamp((int)point.y(), 0, 1023) << 2) |
           (std::clamp((int)point.x(), 0, 1023) << 12);
    data |= __builtin_parity(data) >> 22;
    return data;
}

void SendThread::sendHandler(int type_, QPoint point) {
    queue.enqueue(serialise((type)type_, point));
}

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