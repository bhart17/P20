#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QCoreApplication>
#include <atomic>

#include "thread.h"

class ReceiveThread : public Thread {
    Q_OBJECT

   public:
    std::atomic<bool> finished = false;

   public slots:
    void testRun();
    void run();
    void receive(unsigned int data);

   signals:
    void startLineSig(QPointF start);
    void continueLineSig(QPointF next);
    void clearScreenSig();

   private:
    // void receive(unsigned int data);
    void deserialise(unsigned int data);
};

#endif