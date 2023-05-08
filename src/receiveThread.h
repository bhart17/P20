#ifndef RECEIVETHREAD_H
#define RECEIVETHREAD_H

#include <QCoreApplication>

#include "thread.h"

class ReceiveThread : public Thread {
    Q_OBJECT

   public slots:
    void testRun();
    void receive(unsigned int data);

   signals:
    void startLineSig(QPointF start);
    void continueLineSig(QPointF next);
    void clearScreenSig();
    void run();

   private:
    // void receive(unsigned int data);
    void deserialise(unsigned int data);
};

#endif