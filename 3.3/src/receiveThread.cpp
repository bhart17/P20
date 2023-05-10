#include "receiveThread.h"

void ReceiveThread::receive(unsigned int data) {
    deserialise(data);
}

void ReceiveThread::deserialise(unsigned int data) {
    emit receiveSignal((type)(data & 3),
                       QPoint{(int)(data >> 12), (int)((data >> 2) & 1023)});
}

void ReceiveThread::run() {
    while (!finished) {
        if (!Thread::queue.isEmpty()) {
            receive(Thread::queue.dequeue());
        }
    }
    deleteLater();
}