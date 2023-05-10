#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QCoreApplication>
#include <atomic>
#include <chrono>

#include "thread.h"

class ReceiveThread : public Thread {
    Q_OBJECT

   public:
    std::atomic<bool> finished{false};

   public slots:
    void run();
    void receive();

   signals:
    void receiveSignal(int type, QPoint point);

   private:
    void deserialise(unsigned int data);
    int count{0};
};

#endif