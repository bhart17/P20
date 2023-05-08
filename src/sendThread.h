#ifndef SENDTHREAD_H
#define SENDTHREAD_H

#include "thread.h"

class SendThread : public Thread {
    Q_OBJECT

   public slots:
    void testRun();
    void sendStartLine(QPointF start);
    void sendContinueLine(QPointF next);
    void sendClearScreen();

   signals:
    void send(unsigned int data);

   private:
    // void send(unsigned int data);
    unsigned int serialise(type type, QPointF data);
    unsigned int serialise(type type);
};

#endif  // SENDTHREAD_H