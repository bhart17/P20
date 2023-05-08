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

void SendThread::send(unsigned int data) {
    // Thread::mutex.lock();
    // Thread::pin = true;
    // Thread::clock = true;
    // qDebug() << "Sent: " << Thread::clock << (int)Thread::pin;
    // QThread::currentThread()->msleep(1);
    for (int i = 0; i < 22; ++i) {
        // Thread::pin = (data >> i) & 1;
        // Thread::clock = !Thread::clock;
        digitalWrite(SEND_DATA, (data >> i) & 1);
        clock = !clock;
        digitalWrite(SEND_CLOCK, clock);
        // qDebug() << "Sent: " << Thread::clock << (int)Thread::pin;
        auto prevMillis = millis();
        while (true) {
            auto currentMillis = millis();
            if (currentMillis - prevMillis > 2) {
                break;
            }
        }
        // qDebug() << "waited";
        // QThread::currentThread()->msleep(2);
    }
    // Thread::clock = !Thread::clock;
    // qDebug() << "Sent: " << Thread::clock << (int)Thread::pin;
    // QThread::currentThread()->msleep(1);
    // Thread::clock = false;
    // qDebug() << "Sent: " << Thread::clock << (int)Thread::pin;
    // Thread::pin = false;
    // QThread::currentThread()->msleep(1);
    // qDebug() << "Sent:     " << QString::number(data, 2);
    // Thread::mutex.unlock();
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

unsigned int SendThread::serialise(type type) {
    // only for CLEAR
    return type;
}

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
            // emit send(queue.dequeue());
        } else {
            auto prevMillis = micros();
            while (true) {
                auto currentMillis = micros();
                if (currentMillis - prevMillis > 250) {
                    break;
                }
            }
            // delayMicroseconds(250);
            // QThread::currentThread()->usleep(250);
        }
    }
    deleteLater();
}