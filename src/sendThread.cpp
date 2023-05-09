#include "sendThread.h"

#include <chrono>

void SendThread::send(unsigned int data) {
    Thread::pin = true;
    // digitalWrite(SEND_DATA, true);
    QThread::currentThread()->msleep(SLEEP_MS);
    for (int i = 0; i < 22; ++i) {
        Thread::pin = (data >> i) & 1;
        // digitalWrite(SEND_DATA, (data >> i) & 1);
        QThread::currentThread()->msleep(SLEEP_MS);

        // auto prevMillis = micros();
        // while (true) {
        //     auto currentMillis = micros();
        //     if (currentMillis - prevMillis > 500) {
        //         break;
        //     }
        // }
    }
    Thread::pin = false;
    QThread::currentThread()->msleep(SLEEP_MS);

    qDebug() << "Sent:    " << QString::number(data, 2).rightJustified(22, '0')
             << "(#" << count++ << ")";
}

unsigned int SendThread::serialise(type type, QPoint data) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)data.y(), 0, 1024) << 2) |
           (std::clamp((int)data.x(), 0, 1024) << 12);
}

unsigned int SendThread::serialise(type type) { return type; }

void SendThread::sendStartLine(QPoint start) {
    queue.enqueue(serialise(START, start));
}
void SendThread::sendContinueLine(QPoint next) {
    queue.enqueue(serialise(CONTINUE, next));
}
void SendThread::sendClearScreen() { queue.enqueue(serialise(CLEAR)); }

void SendThread::run() {
    while (!finished) {
        QCoreApplication::processEvents();
        if (!queue.isEmpty()) {
            send(queue.dequeue());
            // } else {
            // QThread::currentThread()->usleep(500);

            // auto prevMillis = micros();
            // while (true) {
            //     auto currentMillis = micros();
            //     if (currentMillis - prevMillis > 250) {
            //         break;
            //     }
            // }
        }
        QThread::currentThread()->usleep(500);

        // auto then = std::chrono::high_resolution_clock::now();
        // QThread::currentThread()->msleep(1);
        // auto now = std::chrono::high_resolution_clock::now();
        // auto difference = (now - then).count();
        // qDebug() << difference;
    }
    deleteLater();
}