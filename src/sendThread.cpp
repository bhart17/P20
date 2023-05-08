#include "sendThread.h"

void SendThread::testRun() {
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

// void SendThread::send(unsigned int data) {
//     // real send code here
//     // receive(data);
// }

unsigned int SendThread::serialise(type type, QPointF data) {
    // bits:
    // 1-2: command (START, CONTINUE)
    // 3-12: y coord
    // 13-22: x coord
    // 0b1010101001001100110001
    return type | (std::clamp((int)data.y(), 0, 1024) << 2) |
           (std::clamp((int)data.x(), 0, 1024) << 12);
}

unsigned int SendThread::serialise(type type) {
    // only for CLEAR
    return type;
}

void SendThread::sendStartLine(QPointF start) {
    Thread::queue.enqueue(serialise(START, start));
}
void SendThread::sendContinueLine(QPointF next) {
    Thread::queue.enqueue(serialise(CONTINUE, next));
}
void SendThread::sendClearScreen() { Thread::queue.enqueue(serialise(CLEAR)); }

// void SendThread::run() {
//     while (true) {
//         QCoreApplication::processEvents();
//         if (!queue.isEmpty()) {
//             emit send(queue.dequeue());
//         }
//         QThread::currentThread()->usleep(500);
//     }
// }