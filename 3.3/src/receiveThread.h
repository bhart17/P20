#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QCoreApplication>
#include <atomic>

#include "thread.h"

class ReceiveThread : public Thread {
    Q_OBJECT

   public:
    std::atomic<bool> finished{false};

   public slots:
    void run();
    void receive(unsigned int data);

   signals:
    void receiveSignal(int type, QPoint point);

   private:
    void deserialise(unsigned int data);
};

#endif