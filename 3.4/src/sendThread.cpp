#include "sendThread.h"

void SendThread::send(unsigned int data) {
    for (auto i = 0; i < BITS; ++i) {
        Thread::data = (data >> i) & 1;
        Thread::clock = false;
        QThread::currentThread()->usleep(SLEEP_US / 2);
        Thread::clock = true;
        QThread::currentThread()->usleep(SLEEP_US / 2);
    }
    QThread::currentThread()->usleep(SLEEP_US);
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
    return type | (std::clamp((int)point.y(), 0, 1023) << 2) |
                (std::clamp((int)point.x(), 0, 1023) << 12);
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