#include "sendThread.h"

void SendThread::send(unsigned int data) {
    for (int i = 0; i < 22; ++i) {
        digitalWrite(SEND_DATA, (data >> i) & 1);
        digitalWrite(SEND_CLOCK, false);
        delayMicroseconds(SLEEP_MS * 500);
        digitalWrite(SEND_CLOCK, true);
        delayMicroseconds(SLEEP_MS * 500);
    }
    delayMicroseconds(SLEEP_MS * 1000);
    qDebug().nospace().noquote()
        << "Sent:     " << QString::number(data, 2).rightJustified(22, '0')
        << " (#" << count++ << ")";
}

unsigned int SendThread::serialise(type type, QPoint data) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)data.y(), 0, 1023) << 2) |
           (std::clamp((int)data.x(), 0, 1023) << 12);
}

unsigned int SendThread::serialise(type type) { return type; }

// void SendThread::sendStartLine(QPoint start) {
//     queue.enqueue(serialise(START, start));
// }
// void SendThread::sendContinueLine(QPoint next) {
//     queue.enqueue(serialise(CONTINUE, next));
// }
// void SendThread::sendClearScreen() { queue.enqueue(serialise(CLEAR)); }

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